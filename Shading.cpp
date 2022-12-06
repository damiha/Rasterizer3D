#include "Shading.hpp"
#include "Utils.hpp"

#include <iostream>

// vertex, vertex normal and light are not transformed yet
glm::vec3 Shading::computeVertexColor(
    glm::mat4& modelViewMatrix,
    glm::mat4& normalMatrix,
    std::vector<Light>& lights,
    Mesh& mesh,
    glm::vec3& vertex,
    glm::vec3& vertexNormal
    ){

    glm::vec3 vertexColor {0.0f, 0.0f, 0.0f};

    glm::vec3 vertexTransformed = glm::vec3(modelViewMatrix * Utils::toVec4(vertex));
    glm::vec3 normalTransformed = glm::vec3(normalMatrix * Utils::toVec4(vertexNormal));

    for(Light& light : lights){
        
        glm::vec3 lightTransformed = glm::vec3(modelViewMatrix * light.position);

        vertexColor += (light.I_a * mesh.K_a);
        glm::vec3 toLight = (glm::normalize(lightTransformed - vertexTransformed));

        float diffuseCoefficient = 
        std::clamp(glm::dot(toLight, normalTransformed), 0.0f, 1.0f);

        vertexColor += (light.I_d * mesh.K_d * diffuseCoefficient);

        // camera position = (0, 0, 0)
        glm::vec3 toCamera = -glm::normalize(vertexTransformed);
        glm::vec3 reflectiveRay = 2.0f * glm::dot(toLight, normalTransformed) * normalTransformed - toLight;
        
        if(glm::dot(reflectiveRay, normalTransformed) > 0.0f){
            float specularCoefficient = 
            std::clamp(glm::dot(reflectiveRay, toCamera), 0.0f, 1.0f);
            specularCoefficient = glm::pow(specularCoefficient, mesh.shininess);
            vertexColor +=  (light.I_s * mesh.K_s * specularCoefficient);
        }           
    }
    return glm::clamp(vertexColor, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f});
}