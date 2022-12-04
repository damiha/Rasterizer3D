#include "KeyHandler.hpp"

void KeyHandler::processEvent(const sf::Event& event){

    if(event.type == sf::Event::KeyPressed){
        updateMovement(event, true);
    }
    else if(event.type == sf::Event::KeyReleased){
        updateMovement(event, false);
    }
}

void KeyHandler::updateMovement(const sf::Event& event, bool value){
    switch(event.key.code){

        case sf::Keyboard::W:
            isMovingForward = value;
            break;
        case sf::Keyboard::S:
            isMovingBackward = value;
            break;
        case sf::Keyboard::A:
            isMovingLeft = value;
            break;
        case sf::Keyboard::D:
            isMovingRight = value;
            break;
        case sf::Keyboard::Space:
            isMovingUp = value;
            break;
        case sf::Keyboard::Y:
            isMovingDown = value;
            break;
        case sf::Keyboard::Up:
            isTurningUp = value;
            break;
        case sf::Keyboard::Down:
            isTurningDown = value;
            break;
        case sf::Keyboard::Left:
            isTurningLeft = value;
            break;
        case sf::Keyboard::Right:
            isTurningRight = value;
            break;
    }
}