#ifndef SCENE
#define SCENE

#include <vector>
#include "Mesh.hpp"
#include "Light.hpp"

class Scene{
public:
    std::vector<Mesh> meshes;
    std::vector<Light> lights;
};

#endif