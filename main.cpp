#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <chrono>
#include <iostream>

#include "constants.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "KeyHandler.hpp"
#include "FrameCounter.hpp"
#include "Rasterizer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Rasterizer by Damian H.");

    Mesh teapot("teapot.obj");
    teapot.K_a = {0.2f, 0.1f, 0.0f};
    teapot.K_d = {0.8, 0.4f, 0.0f};
    teapot.K_s = {1.0f, 1.0f, 1.0f};
    teapot.shininess = 3.0f;

    Light light(glm::vec4{4.0f, 4.0f, 2.0f, 1.0f});

    std::vector<Mesh> meshes;
    std::vector<Light> lights;

    meshes.push_back(teapot);
    lights.push_back(light);

    Rasterizer rasterizer;
    KeyHandler keyHandler;
    FrameCounter frameCounter;

    // speed in world units per second
    float cameraTranslationPerSecond = 1.0f;
    float cameraRotationPerSecond = 1.0f;

    while (window.isOpen())
    {
        float cameraTranslation = cameraRotationPerSecond * frameCounter.getDeltaTime();
        float cameraRotation = cameraRotationPerSecond * frameCounter.getDeltaTime();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            keyHandler.processEvent(event);
        }

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
        

        rasterizer.renderScene(meshes, lights);
        frameCounter.update();

        std::cout << "FPS: " << frameCounter.getFrameRate() << std::endl;

        window.clear();
        window.draw(rasterizer.getRenderedImage());
        window.display();
    }

    return 0;
}