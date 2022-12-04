#include "FrameCounter.hpp"

void FrameCounter::update(){
    frameCount++;

    if(frameCount >= framesPerUpdate){

        auto newTimeStamp = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeToRenderFrames = newTimeStamp - timeStamp;

        frameRate = (int) (framesPerUpdate / timeToRenderFrames.count());
        deltaTime = 1.0 / frameRate;

        timeStamp = newTimeStamp;
        frameCount = 0;
    }
}

int FrameCounter::getFrameRate(){
    return frameRate;
}

float FrameCounter::getDeltaTime(){
    return deltaTime;
}

const char* FrameCounter::getFrameRateString(){
    frameRateString = std::string("FPS: ") + std::to_string(frameRate);
    return frameRateString.c_str();
}