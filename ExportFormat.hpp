#pragma once

#include <QString>
#include <QUrl>
#include <Qt3DRender/QGeometry>

struct vec2 {
    float x {};
    float y {};
};

struct vec3 {
    float x {};
    float y {};
    float z {};
};

using Qt3DRender::QGeometry;

class ExportFormat {
public:
    ExportFormat();
    virtual ~ExportFormat() = default;

    void loadFormatScheme(const std::string&);

    virtual void defineLocationToFillVertices() = 0;
    virtual void defineLocationToFillTextureCoords() = 0;
    virtual void defineLocationToFillNormals() = 0;
    virtual void defineLocationToFillFaces() = 0;
    virtual void defineInnerSeparatorForVertices();
    virtual void defineInnerSeparatorForTextureCoords();
    virtual void defineInnerSeparatorForNormals();
    virtual void defineInnerSeparatorForIndices();
    virtual void defineOuterSeparatorForVertices();
    virtual void defineOuterSeparatorForTextureCoords();
    virtual void defineOuterSeparatorForNormals();
    virtual void defineOuterSeparatorForIndices();
    virtual void defineOuterOuterSeparatorForIndices();

    void fillExportFormat(QGeometry*);

protected:
    std::vector<vec3> vertices;
    std::vector<vec2> textures;
    std::vector<vec3> normals;
    std::vector<unsigned short> indices;
    std::vector<unsigned short> faces;

    QString verticesFillLocation;
    QString textureCoordsFillLocation;
    QString normalsFillLocation;
    QString indicesFillLocation;

    QString innerSeparatorForVertices;
    QString innerSeparatorForTextureCoords;
    QString innerSeparatorForNormals;
    QString innerSeparatorForIndices;

    QString outerSeparatorForVertices;
    QString outerSeparatorForTextureCoords;
    QString outerSeparatorForNormals;
    QString outerSeparatorForIndices;
    QString outerOuterSeparatorForIndices;

    QString formatScheme;
};

