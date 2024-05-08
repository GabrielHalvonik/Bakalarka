#include "ImportFormatOBJ.hpp"

ImportFormatOBJ::ImportFormatOBJ() {

}

void ImportFormatOBJ::importPositionData() {
    ImportFormat::positionRegex.setPattern("v\\s(?<pos_coords>([+-]?[0-9]*[.]?[0-9]+\\s){3})");
    ImportFormat::positionRegexMatchGroup = "pos_coords";
}

void ImportFormatOBJ::importTextureCoordsData() {
    ImportFormat::texCoordsRegex.setPattern("vt\\s(?<tex_coords>([+-]?[0-9]*[.]?[0-9]+\\s){2})");
    ImportFormat::texCoordsRegexMatchGroup = "tex_coords";
}

void ImportFormatOBJ::importNormalsData() {
    ImportFormat::normalRegex.setPattern("vn\\s(?<norm_coords>([+-]?[0-9]*[.]?[0-9]+\\s){3})");
    ImportFormat::normalRegexMatchGroup = "norm_coords";
}

void ImportFormatOBJ::importFacesData() {
    ImportFormat::facesRegex.setPattern("f\\s(?<faces>((\\d+\\/?){1,}\\s?){3,})");
    ImportFormat::facesRegexMatchGroup = "faces";
}
