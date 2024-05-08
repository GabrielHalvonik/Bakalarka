#include "ExportFormat.hpp"

#include <QVector>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <QDebug>

using Qt3DRender::QAttribute;
using Qt3DRender::QBuffer;

ExportFormat::ExportFormat() {
}

void ExportFormat::loadFormatScheme(const std::string& name) {

    QFile file(QString(name.c_str()));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    this->formatScheme = in.readAll();
}

void ExportFormat::defineInnerSeparatorForVertices() {
    this->innerSeparatorForVertices = " ";
}

void ExportFormat::defineInnerSeparatorForTextureCoords() {
    this->innerSeparatorForTextureCoords = " ";
}

void ExportFormat::defineInnerSeparatorForNormals() {
    this->innerSeparatorForNormals = " ";
}

void ExportFormat::defineInnerSeparatorForIndices() {
    this->innerSeparatorForIndices = " ";
}

void ExportFormat::defineOuterSeparatorForVertices() {
    this->outerSeparatorForVertices = "\n";
}

void ExportFormat::defineOuterSeparatorForTextureCoords() {
    this->outerSeparatorForTextureCoords = "\n";
}

void ExportFormat::defineOuterSeparatorForNormals() {
    this->outerSeparatorForNormals = "\n";
}

void ExportFormat::defineOuterSeparatorForIndices() {
    this->outerSeparatorForIndices = "\n";
}

void ExportFormat::defineOuterOuterSeparatorForIndices() {
    this->outerOuterSeparatorForIndices = "";
}

void ExportFormat::fillExportFormat(Qt3DRender::QGeometry* geometry) {
    for (QAttribute* temp : geometry->attributes()) {
        qInfo() << temp->buffer()->data().size();
        if (temp->name() == QAttribute::defaultPositionAttributeName()) {
            uint8_t size = temp->vertexSize();
            uint8_t offset = temp->byteOffset();
            uint8_t stride = temp->byteStride();

            for (int i = offset; i < temp->buffer()->data().size() + size; i += stride) {
                vertices.push_back(*reinterpret_cast<vec3*>(temp->buffer()->data().data()));
            }
        } else if (temp->name() == QAttribute::defaultTextureCoordinateAttributeName()) {
            uint8_t size = temp->vertexSize();

            uint8_t offset = temp->byteOffset();
            uint8_t stride = temp->byteStride();

            for (int i = offset; i < temp->buffer()->data().size() + size ; i += stride) {
                textures.push_back(*reinterpret_cast<vec2*>(temp->buffer()->data().data()));
            }
        } else if (temp->name() == QAttribute::defaultNormalAttributeName()) {
            uint8_t size = temp->vertexSize();

            uint8_t offset = temp->byteOffset();
            uint8_t stride = temp->byteStride();

            for (int i = offset; i < temp->buffer()->data().size() + size; i += stride) {
                normals.push_back(*reinterpret_cast<vec3*>(temp->buffer()->data().data()));
            }
        } else if (temp == geometry->attributes().last()) {
            for (int i = 0; i < static_cast<int>(temp->buffer()->data().size() / sizeof(unsigned short)); i += sizeof(unsigned short)) {
                indices.push_back(*reinterpret_cast<unsigned short*>(temp->buffer()->data().data()));
            }
        }
    }

    for (const vec3& temp : vertices) {
        QTextStream str {};
        str << temp.x << this->innerSeparatorForVertices << temp.y << this->innerSeparatorForVertices << temp.z;
        str << this->outerSeparatorForVertices;
    }

    for (const vec2& temp : textures) {
        QTextStream str {};
        str << temp.x << this->innerSeparatorForTextureCoords << temp.y << this->innerSeparatorForTextureCoords;
        str << this->outerSeparatorForTextureCoords;
    }

    for (const vec3& temp : normals) {
        QTextStream str {};
        str << temp.x << this->innerSeparatorForNormals << temp.y << this->innerSeparatorForNormals << temp.z;
        str << this->outerSeparatorForNormals;
    }

    uint8_t step {1};
    step += (textures.size()) > 0 ? 1 : 0;
    step += (normals.size()) > 0 ? 1 : 0;

    for (size_t i = 0; i < indices.size(); i += step * 3) {
        QTextStream str {};

        for (int j = 0; j < 3; ++j) {
            str << indices[i] << this->innerSeparatorForIndices;
            if (step == 2) {
                str << indices[i + 1] << this->innerSeparatorForIndices;
            } else if (step == 3) {
                str << indices[i + 1] << this->innerSeparatorForIndices;
                str << indices[i + 2] << this->innerSeparatorForIndices;
            }
            str << this->outerSeparatorForIndices;
        }
        str << this->outerOuterSeparatorForIndices;
    }

}
