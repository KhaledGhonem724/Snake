#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>

#include <map>
//#include <pair>


#include "State.hpp"
#include "Game.hpp"
class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle; 

    std::map<int ,std::pair< std::string ,sf::Text > >mainMenuButtons;
    std::map<int ,std::pair< std::string ,sf::Text > >::iterator selected;

public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();
    // overide keyword is just a good practice (optional) 
    void Init()override;
    void ProcessInput()override;
    void Update(sf::Time deltaTime )override;
    void Draw()override;
};