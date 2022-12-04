
#ifndef KEYHANDLER
#define KEYHANDLER

#include <SFML/Graphics.hpp>

class KeyHandler{
public:
    
    bool isMovingForward = false;
    bool isMovingBackward = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isMovingUp = false;
    bool isMovingDown = false;

    bool isTurningLeft = false;
    bool isTurningRight = false;
    bool isTurningUp = false;
    bool isTurningDown = false;

    void processEvent(const sf::Event& event);

private:
    void updateMovement(const sf::Event& event, bool value);
};

#endif