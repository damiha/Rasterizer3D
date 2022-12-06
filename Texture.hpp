#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "Utils.hpp"

class Texture{

public:
    int width;
    int height;
    int nColorValues;

    std::vector<int> pixels;

    // currently only supports PPM P3 (no compression, human readable)
    // because it is by far the easiest image format to parse
    Texture(std::string filePath);

    // parameters are texture coordinates
    glm::vec3 getColorValue(glm::vec2& textureCoordinate);
};

#endif