#ifndef RASTERIZER
#define RASTERIZER

#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Settings.hpp"

class Rasterizer{

    // debug options (later activate via some key or GUI)
    bool colorTrianglesRandomly = false;
    bool showZBuffer = false;

    // virtual camera
    float focalLength = 1.0f;
    float aspectRatio = (WINDOW_WIDTH * 1.0f) / (WINDOW_HEIGHT * 1.0f);
    float nearPlane = 1.0f;
    float farPlane = 20.0f;

public:
    float xAngle = 0.0f;
    float yAngle = 0.0f;
private:
    // split transformations into 2 matrices (first rotation, then translation)
    glm::mat4 translationMatrix = glm::mat4(1.0f);
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    glm::mat4 modelViewMatrix = glm::mat4(1.0f);

    // stored COLUMNWISE
    float projectionEntries[16] = {
        (focalLength / aspectRatio), 0, 0, 0,
        0, focalLength, 0, 0,
        0, 0, (nearPlane + farPlane) / (nearPlane - farPlane), -1.0f,
        0, 0, (2.0f * nearPlane * farPlane) / (nearPlane - farPlane), 0
    };

    glm::mat4 projectionMatrix = glm::make_mat4(projectionEntries);

    float imageEntries[16] = {
        WINDOW_WIDTH, 0, 0, 0,
        0, WINDOW_HEIGHT, 0, 0,
        0, 0, 1.0f, 0,
        (WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f), 0, 1
    };

    glm::mat4 imageMatrix = glm::make_mat4(imageEntries);
    
    // each pixel stores rgba
    sf::Uint8 pixelArray[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
    float zBuffer[WINDOW_WIDTH * WINDOW_HEIGHT];

    sf::Texture renderedTexture;
    sf::Sprite renderedImage;

    void setPixel(int x, int y, glm::vec3& color);
    void clearRenderedImage();
    void clearZBuffer();

    bool isVertexInFrustum(glm::vec4& vertex);
    glm::vec3 getZColor(float zValue);
    Settings& settings;

public:
    Rasterizer(Settings& settings);
    
    void renderScene();
    sf::Sprite& getRenderedImage();
    
    void moveForward(float amount);
    void translateScene(float dx, float dy, float dz);

    // dzRot would be: "Do a barrel roll"
    void rotateScene(float dxRot, float dyRot);
};

#endif