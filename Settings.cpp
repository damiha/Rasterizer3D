#include "Settings.hpp"

Settings::Settings(){

    Texture woodTexture("meshes/wood.ppm");
    textures.push_back(woodTexture);

    Mesh teapot("meshes/teapot.obj");
    teapot.K_a = {0.2f, 0.1f, 0.0f};
    teapot.K_d = {0.8, 0.4f, 0.0f};
    teapot.K_s = {1.0f, 1.0f, 1.0f};
    teapot.shininess = 20.0f;

    Mesh suzanne("meshes/suzanne.obj");
    suzanne.K_a = {0.2f, 0.1f, 0.0f};
    suzanne.K_d = {0.8, 0.4f, 0.0f};
    suzanne.K_s = {1.0f, 1.0f, 1.0f};
    suzanne.shininess = 3.0f;

    Mesh texturedCube("meshes/cube.obj");
    texturedCube.K_a = {0.1f, 0.1f, 0.1f};
    texturedCube.K_d = {0.8f, 0.8f, 0.8f};
    texturedCube.K_s = {0.0f, 0.0f, 0.0f};
    texturedCube.shininess = 5.0f;
    // poins to wood texture
    texturedCube.textureIndex = 0;

    Light light(glm::vec4{0.0f, 4.0f, 10.0f, 1.0f});

    Scene teapotScene;
    teapotScene.meshes.push_back(teapot);
    teapotScene.lights.push_back(light);
    Scene suzanneScene;
    suzanneScene.meshes.push_back(suzanne);
    suzanneScene.lights.push_back(light);
    Scene texturedCubeScene;
    texturedCubeScene.meshes.push_back(texturedCube);
    texturedCubeScene.lights.push_back(light);

    scenes.push_back(teapotScene);
    scenes.push_back(suzanneScene);
    scenes.push_back(texturedCubeScene);
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