#include "ExportFormatOBJ.hpp"
#include <QUrl>

ExportFormatOBJ::ExportFormatOBJ() : ExportFormat() {
    ExportFormat::loadFormatScheme(":/exports/assets/exports/export_scheme.obj");
}

void ExportFormatOBJ::defineLocationToFillVertices() {
    ExportFormat::verticesFillLocation = "<fill_vertices_here>";
}

void ExportFormatOBJ::defineLocationToFillTextureCoords() {
    ExportFormat::verticesFillLocation = "<fill_texcoords_here>";
}

void ExportFormatOBJ::defineLocationToFillNormals() {
    ExportFormat::verticesFillLocation = "<fill_normals_here>";
}

void ExportFormatOBJ::defineLocationToFillFaces() {
    ExportFormat::verticesFillLocation = "<fill_faces_here>";
}

void ExportFormatOBJ::defineInnerSeparatorForIndices() {
    ExportFormatOBJ::innerSeparatorForIndices = "/";
}

void ExportFormatOBJ::defineOuterSeparatorForIndices() {
    ExportFormatOBJ::outerSeparatorForIndices = " ";
}

void ExportFormatOBJ::defineOuterOuterSeparatorForIndices() {
    ExportFormatOBJ::outerOuterSeparatorForIndices = "\n";
}
