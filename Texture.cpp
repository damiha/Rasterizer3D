#include "Texture.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>

Texture::Texture(std::string filePath){

    std::ifstream file(filePath);
    std::string tempLine;

    int lineCount = 0;

    std::string space = " ";

    if(file.is_open()){
        while(getline(file, tempLine)){
            
            if(lineCount == 0 && tempLine != "P3"){
                std::cout << "ERROR: P3 PPM REQUIRED" << std::endl;
                break;
            }

            else if(lineCount == 1){
                std::vector<std::string> lineParts;
                Utils::splitIntoArray(tempLine, space, lineParts);
                width = std::stoi(lineParts[0]);
                height = std::stoi(lineParts[1]);
                pixels.reserve(width * height * 3);
            }

            else if(lineCount == 2){
                nColorValues = std::stoi(tempLine);
            }
            // logic for loading into memory
            else if(lineCount > 2){
                
                std::vector<std::string> lineParts;
                Utils::splitIntoArray(tempLine, space, lineParts);

                for(std::string& linePart : lineParts){
                    if(linePart != "" && linePart != " "){
                        pixels.push_back(std::stoi(linePart));
                    }
                }
            }
            lineCount++;
        }
    }

    /*
    std::cout << lineCount << std::endl;
    std::cout << width << ", " << height << ", " << nColorValues << std::endl;
    std::cout << pixels[0] << ", " << pixels[1] << ", " << pixels[2] << std::endl;
    */
}

glm::vec3 Texture::getColorValue(glm::vec2& textureCoordinate){

    float u = textureCoordinate[0];
    float v = textureCoordinate[1];

    // (0,0) is bottom left
    int texelX = std::clamp((int) (u * width), 0, width - 1);
    int texelY = std::clamp(height - (int) (v * height), 0, height - 1);

    int linearIndex = (texelY * width + texelX) * 3;
    glm::vec3 res {pixels[linearIndex], pixels[linearIndex + 1], pixels[linearIndex + 2]};

    res /= nColorValues;
    return res;
}