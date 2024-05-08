#pragma once

#include <QRegularExpression>
#include <QVector2D>
#include <QVector3D>
#include <vector>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QAttribute>

using Qt3DRender::QAttribute;
using Qt3DCore::QEntity;

class ImportFormat {
public:
    ImportFormat();
    virtual ~ImportFormat();

    void fillBuffers();

    void loadFile(const std::string&);

    void addGeometryToModel(QEntity*);

protected:
    virtual void importPositionData() = 0;
    virtual void importTextureCoordsData() = 0;
    virtual void importNormalsData() = 0;
    virtual void importFacesData() = 0;

protected:
    QRegularExpression positionRegex;
    QString positionRegexMatchGroup;
    QRegularExpression texCoordsRegex;
    QString texCoordsRegexMatchGroup;
    QRegularExpression normalRegex;
    QString normalRegexMatchGroup;
    QRegularExpression facesRegex;
    QString facesRegexMatchGroup;

    QString dataFromFile;
    std::vector<QVector3D> vertices;
    std::vector<QVector2D> textures;
    std::vector<QVector3D> normals;
    std::vector<unsigned short> faces;
    std::vector<unsigned short> indices;

    uint8_t vertexSize {0};
    uint8_t textureSize {0};
    uint8_t normalSize {0};
};

