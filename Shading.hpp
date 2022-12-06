#ifndef SHADING
#define SHADING

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <algorithm>
#include <vector>

#include "Light.hpp"
#include "Mesh.hpp"

class Shading{

public:
    
    // can be used for Flat Shading or Goraud Shading (call 3 times and interpolate in 3d space)
    static glm::vec3 computeVertexColor(
        glm::mat4& modelViewMatrix,
        glm::mat4& normalMatrix,
        std::vector<Light>& lights,
        Mesh& mesh, glm::vec3& vertex,
        glm::vec3& vertexNormal
    );

};

#endif