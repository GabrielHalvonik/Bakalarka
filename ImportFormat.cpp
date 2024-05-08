#include "ImportFormat.hpp"

#include <QString>
#include <fstream>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QGeometryRenderer>

using Qt3DRender::QGeometry;
using Qt3DRender::QGeometryRenderer;
using Qt3DRender::QAttribute;

ImportFormat::ImportFormat() {

}

ImportFormat::~ImportFormat() {

}

void ImportFormat::fillBuffers() {
    this->importPositionData();
    this->importTextureCoordsData();
    this->importNormalsData();
    this->importFacesData();

    this->vertexSize = this->positionRegex.match(dataFromFile).captured(this->positionRegexMatchGroup).split(" ").size();
    this->textureSize = this->texCoordsRegex.match(dataFromFile).captured(this->texCoordsRegexMatchGroup).split(" ").size();
    this->normalSize = this->normalRegex.match(dataFromFile).captured(this->normalRegexMatchGroup).split(" ").size();

    QRegularExpressionMatchIterator iterator = this->positionRegex.globalMatch(dataFromFile);
    while (iterator.hasNext()) {
        auto match = iterator.next();
        QVector3D vec;
        size_t i = 0;
        for (QString temp : match.captured(this->positionRegexMatchGroup).split(" ")) {
            vec[i++] = temp.toFloat();
        }
        vertices.push_back(vec);
    }

    if (this->textureSize) {
        QRegularExpressionMatchIterator iterator2 = this->texCoordsRegex.globalMatch(dataFromFile);
        while (iterator2.hasNext()) {
            auto match = iterator2.next();
            QVector2D vec;
            size_t i = 0;
            for (QString temp : match.captured(this->texCoordsRegexMatchGroup).split(" ")) {
                vec[i++] = temp.toFloat();
            }
            textures.push_back(vec);
        }
    }

    if (this->normalSize) {
        QRegularExpressionMatchIterator iterator3 = this->normalRegex.globalMatch(dataFromFile);
        while (iterator3.hasNext()) {
            auto match = iterator3.next();
            QVector3D vec;
            size_t i = 0;
            for (QString temp : match.captured(this->normalRegexMatchGroup).split(" ")) {
                vec[i++] = temp.toFloat();
            }
            normals.push_back(vec);
        }
    }

    QRegularExpressionMatchIterator iterator4 = this->facesRegex.globalMatch(dataFromFile);
    while (iterator4.hasNext()) {
        auto match = iterator4.next();
        auto splitted = match.captured(this->facesRegexMatchGroup).split(" ");
        for (int size = 1; size <= splitted.size() - 2; ++size) {
            if (indices.size() == 0) {
                indices.push_back(0);
            } else {
                if (size > 1) {
                    indices.push_back(indices[indices.size() - 3]);
                } else {
                    indices.push_back(indices[indices.size() - 1] + 1);
                }
            }
            indices.push_back(indices[indices.size() - 1] + size);
            indices.push_back(indices[indices.size() - 1] + 1);
        }
        for (QString temp : splitted) {
            for (auto temp2 : temp.split("/")) {
                unsigned short vec = temp2.toUShort();
                faces.push_back(vec);
            }
        }
    }
}

void ImportFormat::loadFile(const std::string& name) {
    std::ifstream fin(name, std::ios_base::ate | std::ios_base::binary);
    size_t size = fin.tellg();
    fin.seekg(0);
    char arr[size];
    fin.get(arr, size, fin.eof());

    this->dataFromFile = QString(arr);
    this->fillBuffers();
}

void ImportFormat::addGeometryToModel(QEntity* entity) {
    QGeometryRenderer* renderer = new QGeometryRenderer(entity);
    QGeometry* geom = new QGeometry(renderer);

    Qt3DRender::QBuffer* vertBuffer = new Qt3DRender::QBuffer(geom);
    QByteArray bytes;

    size_t bufferSize = ((faces.size() / 3 * this->vertexSize) + (faces.size() / 3 * this->textureSize) + (faces.size() / 3 * this->normalSize)) * sizeof(float);
    bytes.resize(bufferSize);
    float* rawVertData = reinterpret_cast<float*>(bytes.data());
    size_t i = 0, j = 0;
    while (j < bufferSize && i < faces.size()) {
        QVector3D first = vertices[faces[i++] - 1];
        rawVertData[j++] = first.x();
        rawVertData[j++] = first.y();
        rawVertData[j++] = first.z();

        QVector2D second = textures[faces[i++] - 1];
        rawVertData[j++] = second.x();
        rawVertData[j++] = second.y();

        QVector3D third = normals[faces[i++] - 1];
        rawVertData[j++] = third.x();
        rawVertData[j++] = third.y();
        rawVertData[j++] = third.z();
    }

    vertBuffer->setData(bytes);
    QAttribute* vertex = new QAttribute(geom);
    QAttribute* tex = new QAttribute(geom);
    QAttribute* normal = new QAttribute(geom);
    QAttribute* index = new QAttribute(geom);

    {
        vertex->setAttributeType(QAttribute::AttributeType::VertexAttribute);
        vertex->setVertexBaseType(QAttribute::VertexBaseType::Float);
        vertex->setVertexSize(this->vertexSize);
        vertex->setByteStride((this->vertexSize + this->textureSize + this->normalSize) * sizeof(float));
        vertex->setByteOffset(0);
        vertex->setName(QAttribute::defaultPositionAttributeName());
        vertex->setBuffer(vertBuffer);
    }

    if (this->textureSize) {
        tex->setAttributeType(QAttribute::AttributeType::VertexAttribute);
        tex->setVertexBaseType(QAttribute::VertexBaseType::Float);
        tex->setVertexSize(this->textureSize);
        tex->setByteStride((this->vertexSize + this->textureSize + this->normalSize) * sizeof(float));
        tex->setByteOffset(this->vertexSize * sizeof(float));
        tex->setName(QAttribute::defaultTextureCoordinateAttributeName());
        tex->setBuffer(vertBuffer);
    }


    if (this->normalSize) {
        normal->setAttributeType(QAttribute::AttributeType::VertexAttribute);
        normal->setVertexBaseType(QAttribute::VertexBaseType::Float);
        normal->setVertexSize(this->normalSize);
        normal->setByteStride((this->vertexSize + this->textureSize + this->normalSize) * sizeof(float));
        normal->setByteOffset((this->vertexSize + this->textureSize) * sizeof(float));
        normal->setName(QAttribute::defaultNormalAttributeName());
        normal->setBuffer(vertBuffer);
    }

    {
        index->setAttributeType(QAttribute::AttributeType::IndexAttribute);
        index->setVertexBaseType(QAttribute::VertexBaseType::UnsignedShort);
        index->setVertexSize(1);
        index->setByteOffset(0);
        index->setByteStride(0);
        index->setCount(indices.size());

        QByteArray* buff = new QByteArray;
        buff->setRawData(reinterpret_cast<char*>(indices.data()), indices.size() * sizeof(unsigned short));

        Qt3DRender::QBuffer* buffer = new Qt3DRender::QBuffer;
        buffer->setData(*buff);
        index->setBuffer(buffer);
    }

    geom->addAttribute(vertex);
    if (this->textureSize)
        geom->addAttribute(tex);
    if (this->normalSize)
        geom->addAttribute(normal);
    geom->addAttribute(index);

    renderer->setGeometry(geom);

    entity->addComponent(renderer);
}
