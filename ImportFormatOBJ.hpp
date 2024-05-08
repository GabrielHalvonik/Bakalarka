#pragma once

#include "ImportFormat.hpp"

class ImportFormatOBJ : public ImportFormat {
public:
    ImportFormatOBJ();

protected:
    void importPositionData() override;
    void importTextureCoordsData() override;
    void importNormalsData() override;
    void importFacesData() override;
};

