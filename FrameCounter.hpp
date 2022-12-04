
#ifndef FRAMECOUNTER
#define FRAMECOUNTER

#include <chrono>
#include <string>

class FrameCounter {
private:
    
    float deltaTime = 0.0f;
    int frameRate = 0;
    int frameCount = 0;
    int framesPerUpdate = 5;
    std::string frameRateString = "";

    std::chrono::_V2::system_clock::time_point timeStamp = std::chrono::high_resolution_clock::now();

public:
    void update();
    float getDeltaTime();
    int getFrameRate();
    const char* getFrameRateString();
};

#endif