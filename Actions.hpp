#pragma once

enum class Actions : int {
    ImportedAssetAction,
    ExportedAssetAction,
    ViewPrimitiveChangedAction,
    MeshBeginTranslateAction,
    MeshEndTranslateAction,
    MeshBeginEditAction,
    MeshEndEditAction,
    EffectChangedAction,
    CameraMovedAction,
};
