#include "Utils.hpp"

glm::vec3 Utils::toVec3(glm::vec2 vector){
    return glm::vec3 {vector.x, vector.y, 0.0f};
}

glm::vec4 Utils::toVec4(glm::vec3 vector){
    return glm::vec4 {vector.x, vector.y, vector.z, 1.0f};
}

glm::vec3 Utils::getBarycentricCoordinates(glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C){

    glm::vec3 surfaceNormal = glm::cross(toVec3(B - A), toVec3(C - A));

    float totalAreaInv = 1.0f / glm::dot(surfaceNormal, surfaceNormal);
    float areaOppositeC = glm::dot(surfaceNormal, glm::cross(toVec3(B - A), toVec3(P - A)));
    float areaOppositeB = glm::dot(surfaceNormal, glm::cross(toVec3(P - A), toVec3(C - A)));
    float areaOppositeA = glm::dot(surfaceNormal, glm::cross(toVec3(B - P), toVec3(C - P)));

    return {areaOppositeA * totalAreaInv, areaOppositeB * totalAreaInv, areaOppositeC * totalAreaInv};
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

void Utils::splitIntoArray(std::string& string, std::string& delimiter, std::vector<std::string>& outArr){
    auto start = 0U;
    auto end = string.find(delimiter);

    while(end != std::string::npos){
        outArr.push_back(string.substr(start, end - start));
        start = end + delimiter.length();
        end = string.find(delimiter, start);
    }
    outArr.push_back(string.substr(start, end-start));
}

glm::vec3 Utils::clampColor(glm::vec3& color){
    return glm::clamp(color, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
}

void Utils::printVec3(glm::vec3& vector){
    std::cout << vector[0] << ", " << vector[1] << ", " << vector[2] << std::endl;
}

void Utils::printVec2(glm::vec2& vector){
    std::cout << vector[0] << ", " << vector[1] << std::endl;
}