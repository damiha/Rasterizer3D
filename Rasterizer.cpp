#include <iostream>
#include <random>
#include <algorithm>

#include "Rasterizer.hpp"
#include "Utils.hpp"

Rasterizer::Rasterizer(Settings& settings) : settings(settings){

    renderedTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    renderedImage.setTexture(renderedTexture);

    clearRenderedImage();

    // translate to move away from camera
    translateScene(0.0f, 0.0f, -5.0f);
}
void Rasterizer::renderScene(){
    
    clearRenderedImage();
    clearZBuffer();

    modelViewMatrix = rotationMatrix * translationMatrix;

    // Rasterization logic
    for(Mesh& mesh : settings.getScene().meshes){

        std::vector<glm::vec4>&  vertices = mesh.vertices;

        for(Face& face : mesh.faces){

            glm::vec4 v0 = vertices[face.vertexIndices[0]];
            glm::vec4 v1 = vertices[face.vertexIndices[1]];
            glm::vec4 v2 = vertices[face.vertexIndices[2]];

            v0 = projectionMatrix * modelViewMatrix * v0;
            v1 = projectionMatrix * modelViewMatrix * v1;
            v2 = projectionMatrix * modelViewMatrix * v2;

            // vertices are supposes to be in a cube with each side length being in [-W_clip, W_clip]
            // TODO: clipping algorithm (only when hard shadows are implemented)
            if(!isVertexInFrustum(v0) || !isVertexInFrustum(v1) || !isVertexInFrustum(v2))
                break;
            // perspective division (divide by W_clip)
            v0 /= v0[3];
            v1 /= v1[3];
            v2 /= v2[3];

            v0 = imageMatrix * v0;
            v1 = imageMatrix * v1;
            v2 = imageMatrix * v2;
            
            // to see if inside the triangle only check pixels in AABB around the triangle
            int minX = (int) std::min({v0[0], v1[0], v2[0]});
            int maxX = (int) std::max({v0[0], v1[0], v2[0]});
            int minY = (int) std::min({v0[1], v1[1], v2[1]});
            int maxY = (int) std::max({v0[1], v1[1], v2[1]});

            minX = std::clamp(minX, 0, WINDOW_WIDTH - 1);
            maxX = std::clamp(maxX, 0, WINDOW_WIDTH - 1);
            minY = std::clamp(minY, 0, WINDOW_HEIGHT - 1);
            maxY = std::clamp(maxY, 0, WINDOW_HEIGHT - 1);

            glm::vec3 faceColor {0.0f, 0.0f, 0.0f};

            if(settings.getRenderMode() == Phong && settings.getShadingType() == FlatShading){
                for(Light& light : settings.getScene().lights){

                    faceColor += (light.I_a * mesh.K_a);
                    glm::vec3 toLight = (glm::normalize(glm::vec3(light.position) - face.center));

                    float diffuseCoefficient = glm::dot(toLight, face.faceNormal);
                    faceColor += (light.I_d * mesh.K_d * diffuseCoefficient);

                    // camera position = (0, 0, 0)
                    glm::vec3 toCamera = glm::normalize(face.center);
                    glm::vec3 reflectiveRay = 2.0f * glm::dot(toLight, face.faceNormal) * face.faceNormal -toLight;
                    
                    
                    if(glm::dot(reflectiveRay, face.faceNormal) > 0.0f){
                        float specularCoefficient = std::clamp(glm::dot(reflectiveRay, toCamera), 0.0f, 1.0f);
                        specularCoefficient = glm::pow(specularCoefficient, mesh.shininess);
                        faceColor +=  (light.I_s * mesh.K_s * specularCoefficient);
                    }
                    
                }
                faceColor = glm::clamp(faceColor, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f});
            }

            for(int y = minY; y <= maxY; y++){
                for(int x = minX; x <= maxX; x++){
                    
                    glm::vec2 P {x, y};
                    glm::vec2 A = glm::vec2(v0);
                    glm::vec2 B = glm::vec2(v1);
                    glm::vec2 C = glm::vec2(v2);

                    glm::vec3 barycentricCoordinates = Utils::getBarycentricCoordinates(P, A, B, C);

                    float z_inv =   (barycentricCoordinates[0] / v0[2]) +
                                    (barycentricCoordinates[1] / v1[2]) + 
                                    (barycentricCoordinates[2] / v2[2]);
                    float z = 1.0f / z_inv;

                    if(Utils::areBarycentricCoordinatesValid(barycentricCoordinates)){
                        
                        int indexPixelX = x;
                        int indexPixelY = WINDOW_HEIGHT - y;
                        int linearIndex = (indexPixelY * WINDOW_WIDTH) + indexPixelX;

                        if(0 <= linearIndex && linearIndex < WINDOW_WIDTH * WINDOW_HEIGHT 
                        && z < zBuffer[linearIndex]){
                            // Goroud and phong have to be computed in here

                            if(settings.getRenderMode() == Phong){
                                setPixel(indexPixelX, indexPixelY, faceColor);
                            }
                            else if(settings.getRenderMode() == ZBuffer){
                                glm::vec3 zColor = getZColor(z);
                                setPixel(indexPixelX, indexPixelY, zColor);
                            }
                            zBuffer[linearIndex] = z;
                        }
                    }
                }
            }
        }
    }

    renderedTexture.update(pixelArray, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
}

sf::Sprite& Rasterizer::getRenderedImage(){
    return renderedImage;
}

void Rasterizer::setPixel(int x, int y, glm::vec3& color){

    if(x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    
    int linearPos = (y * WINDOW_WIDTH + x) * 4;
    pixelArray[linearPos] = (int) (color[0] * 255.0f);
    pixelArray[linearPos + 1] = (int) (color[1] * 255.0f);
    pixelArray[linearPos + 2] = (int) (color[2] * 255.0f);
    pixelArray[linearPos + 3] = 255;
}

void Rasterizer::translateScene(float dx, float dy, float dz){
    float translateEntries[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        dx, dy, dz, 1.0f
    };

    translationMatrix = glm::make_mat4(translateEntries) * translationMatrix;
}

void Rasterizer::moveForward(float amount){

    float pi = glm::pi<float>();
    // camera points in which direction
    float x = glm::cos(yAngle +  pi / 2);
    float z = glm::sin(yAngle + pi / 2);

    float y = glm::sin(xAngle);

    translateScene(x * amount, y * amount, z * amount);
}

void Rasterizer::rotateScene(float dxRot, float dyRot){

    xAngle += dxRot;
    yAngle += dyRot;

    float sinXRot = glm::sin(dxRot);
    float cosXRot = glm::cos(dxRot);

    float rotationXEntries[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosXRot, sinXRot, 0.0f,
        0.0f, -sinXRot, cosXRot, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    float sinYRot = glm::sin(dyRot);
    float cosYRot = glm::cos(dyRot);

    float rotationYEntries[16] = {
        cosYRot, 0.0f, -sinYRot, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sinYRot, 0.0f, cosYRot, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    rotationMatrix = glm::make_mat4(rotationYEntries) * glm::make_mat4(rotationXEntries) * rotationMatrix;
}

void Rasterizer::clearRenderedImage(){

    glm::vec3 black {0.0f, 0.0f, 0.0f};

    for(int y = 0; y < WINDOW_HEIGHT; y++){
        for(int x = 0; x < WINDOW_WIDTH; x++){
            setPixel(x, y, black);
        }
    }
    renderedTexture.update(pixelArray, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
}

bool Rasterizer::isVertexInFrustum(glm::vec4& vertex){

    float W_clip = vertex[3];

    return  -W_clip <= vertex[0] <= W_clip &&
            -W_clip <= vertex[1] <= W_clip && -W_clip <= vertex[2] <= W_clip;
}

void Rasterizer::clearZBuffer(){
    for(int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
        zBuffer[i] = 1.0;
}

glm::vec3 Rasterizer::getZColor(float zValue){
    float zPercentage = 1.0f - ((zValue + 1.0f) / 2.0f);
    return glm::vec3 {zPercentage, zPercentage, zPercentage};
}