#ifndef UTILS
#define UTILS

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <vector>
#include <string>

class Utils{

public:
    static glm::vec3 clampColor(glm::vec3& color);
    static glm::vec3 toVec3(glm::vec2 vector);
    static glm::vec4 toVec4(glm::vec3 vector);
    static glm::vec3 getBarycentricCoordinates(glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C);

    static bool areBarycentricCoordinatesValid(glm::vec3& barycentricCoordinates);
    static void printBarycentricCoordinates(glm::vec3& barycentricCoordinates);

    static void splitIntoArray(std::string& string, std::string& delimiter, std::vector<std::string>& outArr);

    static void printVec2(glm::vec2& vector);
    static void printVec3(glm::vec3& vector);
};

#endif
