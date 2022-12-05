#include "Settings.hpp"

Settings::Settings(){

    Mesh teapot("teapot.obj");
    teapot.K_a = {0.2f, 0.1f, 0.0f};
    teapot.K_d = {0.8, 0.4f, 0.0f};
    teapot.K_s = {1.0f, 1.0f, 1.0f};
    teapot.shininess = 3.0f;

    Mesh suzanne("suzanne.obj");
    suzanne.K_a = {0.2f, 0.1f, 0.0f};
    suzanne.K_d = {0.8, 0.4f, 0.0f};
    suzanne.K_s = {1.0f, 1.0f, 1.0f};
    suzanne.shininess = 3.0f;

    Light light(glm::vec4{0.0f, 0.0f, 5.0f, 1.0f});

    Scene teapotScene;
    teapotScene.meshes.push_back(teapot);
    teapotScene.lights.push_back(light);
    Scene suzanneScene;
    suzanneScene.meshes.push_back(suzanne);
    suzanneScene.lights.push_back(light);

    scenes.push_back(teapotScene);
    scenes.push_back(suzanneScene);
}

RenderMode Settings::getRenderMode(){
    return (RenderMode) selectedRenderMode;
}

ShadingType Settings::getShadingType(){
    return (ShadingType) selectedShadingType;
}

Scene& Settings::getScene(){
    return scenes[selectedScene];
}