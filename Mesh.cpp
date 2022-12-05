#include "Mesh.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

// NOTE: MESH LOADER ASSUMES THAT A SURFACE IS DEFINED BY A TRIANGLE, NOT A QUAD
// meshes possibly have to be triangulated

Mesh::Mesh(std::string filePath){
    
    std::string space = " ";
    std::string singleSlash = "/";
    std::string doubleSlash = "//";
    std::string tempLine;
    std::ifstream file(filePath);

    if(file.is_open()){
        while(getline(file, tempLine)){
            
            std::vector<std::string> lineParts;
            splitIntoArray(tempLine, space, lineParts);

            if(lineParts.size() > 0){

                std::string& lineType = lineParts[0];

                if(lineType == "v"){

                    double x = std::stod(lineParts[1]);
                    double y = std::stod(lineParts[2]);
                    double z = std::stod(lineParts[3]);

                    vertices.push_back(glm::vec4 {x, y, z, 1.0});
                }
                else if(lineType == "vn"){
                    double x = std::stod(lineParts[1]);
                    double y = std::stod(lineParts[2]);
                    double z = std::stod(lineParts[3]);

                    vertexNormals.push_back(glm::normalize(glm::vec3 {x, y, z}));
                }
                else if(lineType == "vt"){
                    double x = std::stod(lineParts[1]);
                    double y = std::stod(lineParts[2]);
                    textureCoordinates.push_back(glm::vec2 {x, y});
                }
                else if(lineType == "f"){

                    bool containsSingleSlashes = lineParts[1].find("/") != std::string::npos;
                    bool containsDoubleSlashes = lineParts[1].find("//") != std::string::npos;
                    
                    // all indices starting at 1 (according to Wikipedia)
                    int v0Index = -1;
                    int v1Index = -1;
                    int v2Index = -1;

                    Face face;

                    if(!containsSingleSlashes && !containsDoubleSlashes){
                        v0Index = std::stoi(lineParts[1]) - 1;
                        v1Index = std::stoi(lineParts[2]) - 1;
                        v2Index = std::stoi(lineParts[3]) - 1;
                    }
                    else if(containsSingleSlashes && !containsDoubleSlashes){

                        for(int i = 1; i <= 3; i++){
                            std::vector<std::string> vertexParts;
                            splitIntoArray(lineParts[i], singleSlash, vertexParts);

                            if(i == 1) v0Index = std::stoi(vertexParts[0]) - 1;
                            if(i == 2) v1Index = std::stoi(vertexParts[0]) - 1;
                            if(i == 3) v2Index = std::stoi(vertexParts[0]) - 1;

                            face.textureCoordinateIndecies[i - 1] = std::stoi(vertexParts[1]) - 1;
                            face.vertexNormalIndices[i - 1] = std::stoi(vertexParts[2]) - 1;
                        }
                    }
                    else if(containsSingleSlashes && containsDoubleSlashes){

                        for(int i = 1; i <= 3; i++){
                            std::vector<std::string> vertexParts;
                            splitIntoArray(lineParts[i], doubleSlash, vertexParts);

                            if(i == 1) v0Index = std::stoi(vertexParts[0]) - 1;
                            if(i == 2) v1Index = std::stoi(vertexParts[0]) - 1;
                            if(i == 3) v2Index = std::stoi(vertexParts[0]) - 1;

                            face.vertexNormalIndices[i - 1] = std::stoi(vertexParts[1]) - 1;
                        }
                    }

                    face.vertexIndices = glm::uvec3{v0Index, v1Index, v2Index};

                    glm::vec3 v03D = glm::vec3(vertices[v0Index]);
                    glm::vec3 v13D = glm::vec3(vertices[v1Index]);
                    glm::vec3 v23D = glm::vec3(vertices[v2Index]);

                    face.faceNormal = glm::normalize(glm::cross(v13D - v03D, v23D - v03D));

                    face.center = (v03D + v13D + v23D) / 3.0f;
                    faces.push_back(face);
                }
            }
        }
    } 
    else {
        std::cout << "ERROR: couldn't open file" << std::endl;
    }
}

void Mesh::splitIntoArray(std::string& string, std::string& delimiter, std::vector<std::string>& outArr){
    auto start = 0U;
    auto end = string.find(delimiter);

    while(end != std::string::npos){
        outArr.push_back(string.substr(start, end - start));
        start = end + delimiter.length();
        end = string.find(delimiter, start);
    }
    outArr.push_back(string.substr(start, end-start));
}