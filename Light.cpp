#include "Light.hpp"

Light::Light(glm::vec4 position){
    // position gets copied
    this->position = position;
}