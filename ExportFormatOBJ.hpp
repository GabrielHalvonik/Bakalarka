#pragma once

#include "ExportFormat.hpp"

class ExportFormatOBJ : public ExportFormat {
public:
    ExportFormatOBJ();
    virtual ~ExportFormatOBJ() = default;

    void defineLocationToFillVertices() override;
    void defineLocationToFillTextureCoords() override;
    void defineLocationToFillNormals() override;
    void defineLocationToFillFaces() override;

    void defineInnerSeparatorForIndices() override;
    void defineOuterSeparatorForIndices() override;
    void defineOuterOuterSeparatorForIndices() override;
};

