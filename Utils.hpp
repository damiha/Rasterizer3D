#ifndef UTILS
#define UTILS

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <iostream>

class Utils{

public:
    static glm::vec3 toVec3(glm::vec2 vector);
    static glm::vec3 getBarycentricCoordinates(glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C);
    static glm::vec3 getBarycentricCoordinates(glm::vec3& P, glm::vec3& A, glm::vec3& B, glm::vec3& C);

    static bool areBarycentricCoordinatesValid(glm::vec3& barycentricCoordinates);
    static void printBarycentricCoordinates(glm::vec3& barycentricCoordinates);
};

#endif
