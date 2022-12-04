#include "Settings.hpp"

RenderMode Settings::getRenderMode(){
    return (RenderMode) selectedRenderMode;
}

ShadingType Settings::getShadingType(){
    return (ShadingType) selectedShadingType;
}