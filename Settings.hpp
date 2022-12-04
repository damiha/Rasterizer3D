#ifndef SETTINGS
#define SETTINGS

enum ShadingType {
    FlatShading = 0,
    GouraudShading = 1,
    PhongShading = 2
};

enum RenderMode {
    Phong = 0,
    WireFrame = 1,
    ZBuffer = 2
};

class Settings{

public:
    const char* sceneNames[3]{"Utah Teapot", "Textured Cube", "Suzanne"};
    int selectedScene = 0;

    const char* renderModeNames[3]{"Phong", "WireFrame", "ZBuffer"};
    int selectedRenderMode = 0;

    const char* shadingTypeNames[3]{"Flat", "Gouraud", "Phong"};
    int selectedShadingType = 0;

    RenderMode getRenderMode();
    ShadingType getShadingType();
};

#endif