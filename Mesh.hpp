#ifndef MESH
#define MESH

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <vector>
#include <string>

struct Face {
    glm::uvec3 vertexIndices;
    glm::uvec3 vertexNormalIndices;
    glm::uvec3 textureCoordinateIndecies;

    // for light calculation
    glm::vec3 faceNormal;
    glm::vec3 center;
};

class Mesh {
public:
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> vertexNormals;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<Face> faces;

    // material properties
    // TODO: outsource this later
    glm::vec3 K_a;
    glm::vec3 K_d;
    glm::vec3 K_s;
    int shininess = 1.0f;

    Mesh(std::string filePath);

    void splitIntoArray(std::string& string, std::string& delimiter, std::vector<std::string>& outArr);
};

#endif