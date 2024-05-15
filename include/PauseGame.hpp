#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include <map>
//#include <pair>


#include "State.hpp"
#include "Game.hpp"
class PauseGame : public Engine::State
{
private:
    // to do : documant the context
    std::shared_ptr<Context> m_context;
    // the main menu title : it's stored in Text object
    // this Text object store the properties of a text 
    // to be displayed: color, font, size
    sf::Text m_pauseGameTitle; 

public:
    //note : `overide` keyword is just a good practice (optional) 
    PauseGame(std::shared_ptr<Context>& context);
    ~PauseGame();
    // these functions are necessary for any screen (state)
    // set the defaulte values of the screen (state)
    void Init()override;
    // receive the inpu from the user 
    void ProcessInput()override;
    // update the values of the screen according to the input
    void Update(sf::Time deltaTime )override;
    // draw the new screen 
    void Draw()override;
};
