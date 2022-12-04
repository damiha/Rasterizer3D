#ifndef LIGHT
#define LIGHT

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

class Light{

public:

    glm::vec4 position;
    // phong illumination model
    glm::vec3 I_a {1.0f, 1.0f, 1.0f};
    glm::vec3 I_d {1.0f, 1.0f, 1.0f};
    glm::vec3 I_s {1.0f, 1.0f, 1.0f};

    // creates a white light
    Light(glm::vec4 position);
};

#endif