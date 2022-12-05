#include "Shading.hpp"

glm::vec3 Shading::computeVertexColor(
    glm::mat4& modelViewMatrix,
    std::vector<Light>& lights,
    Mesh& mesh,
    glm::vec3& vertex,
    glm::vec3& vertexNormal
    ){

    glm::vec3 vertexColor {0.0f, 0.0f, 0.0f};

    for(Light& light : lights){
        
        glm::vec3 lightPosition = glm::vec3(modelViewMatrix * light.position);

        vertexColor += (light.I_a * mesh.K_a);
        glm::vec3 toLight = (glm::normalize(lightPosition - vertex));

        float diffuseCoefficient = glm::dot(toLight, vertexNormal);
        vertexColor += (light.I_d * mesh.K_d * diffuseCoefficient);

        // camera position = (0, 0, 0)
        glm::vec3 toCamera = -glm::normalize(vertex);
        glm::vec3 reflectiveRay = 2.0f * glm::dot(toLight, vertexNormal) * vertexNormal -toLight;
        
        if(glm::dot(reflectiveRay, vertexNormal) > 0.0f){
            float specularCoefficient = std::clamp(glm::dot(reflectiveRay, toCamera), 0.0f, 1.0f);
            specularCoefficient = glm::pow(specularCoefficient, mesh.shininess);
            vertexColor +=  (light.I_s * mesh.K_s * specularCoefficient);
        }           
    }
    return glm::clamp(vertexColor, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f});
}