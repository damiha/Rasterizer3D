#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <chrono>
#include <iostream>
#include <string>

#include "constants.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "KeyHandler.hpp"
#include "FrameCounter.hpp"
#include "Rasterizer.hpp"
#include "Settings.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Rasterizer by Damian H.");
    bool isInitialized = ImGui::SFML::Init(window);

    Settings settings;
    Rasterizer rasterizer(settings);
    KeyHandler keyHandler;
    FrameCounter frameCounter;

    // speed in world units per second
    float cameraTranslationPerSecond = 1.0f;
    float cameraRotationPerSecond = 1.0f;

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        float cameraTranslation = cameraRotationPerSecond * frameCounter.getDeltaTime();
        float cameraRotation = cameraRotationPerSecond * frameCounter.getDeltaTime();

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            keyHandler.processEvent(event);
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if(keyHandler.isMovingForward)
            rasterizer.translateScene(0.0f, 0.0f, cameraTranslation);
        else if(keyHandler.isMovingBackward)
            rasterizer.translateScene(0.0f, 0.0f, -cameraTranslation);
        else if(keyHandler.isMovingLeft)
            rasterizer.translateScene(+cameraTranslation, 0.0f, 0.0f);
        else if(keyHandler.isMovingRight)
            rasterizer.translateScene(-cameraTranslation, 0.0f, 0.0f);
        else if(keyHandler.isMovingUp)
            rasterizer.translateScene(0.0f, -cameraTranslation, 0.0f);
        else if(keyHandler.isMovingDown)
            rasterizer.translateScene(0.0f, +cameraTranslation, 0.0f);

        else if(keyHandler.isTurningUp)
            rasterizer.rotateScene(-cameraRotation, 0.0f);
        else if(keyHandler.isTurningDown)
            rasterizer.rotateScene(+cameraRotation, 0.0f);
        else if(keyHandler.isTurningRight)
            rasterizer.rotateScene(0.0f, cameraRotation);
        else if(keyHandler.isTurningLeft)
            rasterizer.rotateScene(0.0f, -cameraRotation);
        

        rasterizer.renderScene();
        frameCounter.update();

        ImGui::Begin("Settings");
        ImGui::Combo("Scene", &settings.selectedScene, settings.sceneNames, 4);
        ImGui::Combo("Render Mode", &settings.selectedRenderMode, settings.renderModeNames, 3);
        ImGui::Combo("Shading Type", &settings.selectedShadingType, settings.shadingTypeNames, 3);

        ImGui::Text("Statistics:");
        ImGui::Text(frameCounter.getFrameRateString());
        ImGui::End();

        window.clear();
        window.draw(rasterizer.getRenderedImage());
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}