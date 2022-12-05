#include "Utils.hpp"

glm::vec3 Utils::toVec3(glm::vec2 vector){
    return glm::vec3 {vector.x, vector.y, 0.0f};
}

glm::vec3 Utils::getBarycentricCoordinates(glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C){

    glm::vec3 surfaceNormal = glm::cross(toVec3(B - A), toVec3(C - A));

    float totalAreaInv = 1.0f / glm::dot(surfaceNormal, surfaceNormal);
    float areaOppositeC = glm::dot(surfaceNormal, glm::cross(toVec3(B - A), toVec3(P - A)));
    float areaOppositeB = glm::dot(surfaceNormal, glm::cross(toVec3(P - A), toVec3(C - A)));
    float areaOppositeA = glm::dot(surfaceNormal, glm::cross(toVec3(B - P), toVec3(C - P)));

    return {areaOppositeA * totalAreaInv, areaOppositeB * totalAreaInv, areaOppositeC * totalAreaInv};
}

glm::vec3 Utils::getBarycentricCoordinates(glm::vec3& P, glm::vec3& A, glm::vec3& B, glm::vec3& C){

    glm::dvec3 AB = B - A;
    glm::dvec3 AC = C - A;
    glm::dvec3 AP = P - A;
    glm::dvec3 PB = B - P;
    glm::dvec3 PC = P - C;
    glm::dvec3 surfaceNormal = glm::cross(AB, AC);

    double totalAreaInv = 1.0 / glm::dot(surfaceNormal, surfaceNormal);
    double areaOppositeC = glm::dot(surfaceNormal, glm::cross(AB, AP));
    double areaOppositeB = glm::dot(surfaceNormal, glm::cross(AP, AC));
    double areaOppositeA = glm::dot(surfaceNormal, glm::cross(PB, PC));

    return {(float) (areaOppositeA * totalAreaInv), (float) (areaOppositeB * totalAreaInv), (float) (areaOppositeC * totalAreaInv)};
}

bool Utils::areBarycentricCoordinatesValid(glm::vec3& barycentricCoordinates){
    float alpha = barycentricCoordinates[0];
    float beta = barycentricCoordinates[1];
    float gamma = barycentricCoordinates[2];

    return 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1;
}

void Utils::printBarycentricCoordinates(glm::vec3& barycentricCoordinates){
    std::cout << "alpha: " << barycentricCoordinates[0] << ", beta: " << barycentricCoordinates[1]
    << ", gamma: " << barycentricCoordinates[2] << std::endl;
}