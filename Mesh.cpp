#include "Mesh.hpp"

#include <iostream>
#include <fstream>

Mesh::Mesh(std::string filePath){
    
    std::string delimiter = " ";
    std::string tempLine;
    std::ifstream file(filePath);

    if(file.is_open()){
        while(getline(file, tempLine)){
            
            std::vector<std::string> lineParts;
            splitIntoArray(tempLine, delimiter, lineParts);

            if(lineParts.size() > 0){

                std::string& lineType = lineParts[0];

                if(lineType == "v"){

                    double x = std::stod(lineParts[1]);
                    double y = std::stod(lineParts[2]);
                    double z = std::stod(lineParts[3]);

                    vertices.push_back(glm::vec4 {x, y, z, 1.0});
                }
                else if(lineType == "f"){
                    
                    // indices starting at 1 (according to Wikipedia)
                    int v0Index = std::stoi(lineParts[1]) - 1;
                    int v1Index = std::stoi(lineParts[2]) - 1;
                    int v2Index = std::stoi(lineParts[3]) - 1;

                    Face face = {glm::uvec3{v0Index, v1Index, v2Index}};

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