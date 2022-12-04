#ifndef SETTINGS
#define SETTINGS

#include <vector>
#include "Scene.hpp"

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

private:
    std::vector<Scene> scenes;

public:
    const char* sceneNames[3]{"Utah Teapot", "Suzanne", "Textured Cube[???]"};
    int selectedScene = 0;

    const char* renderModeNames[3]{"Phong", "WireFrame[???]", "ZBuffer"};
    int selectedRenderMode = 0;

    const char* shadingTypeNames[3]{"Flat", "Gouraud[???]", "Phong[???]"};
    int selectedShadingType = 0;

    RenderMode getRenderMode();
    ShadingType getShadingType();
    Scene& getScene();    

    Settings();
};

#endif