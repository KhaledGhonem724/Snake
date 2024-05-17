#pragma once

#include <memory>
#include <array>


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"
class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    // three drawable items
    sf::Sprite m_grass;
    sf::Sprite m_food;
    std::array<sf::Sprite,4> m_walls;

    // the snake and it's direction 
    Snake m_snake;
    sf::Vector2f m_snakeDirection;

    // the time between each two updates
    sf::Time m_elapseTime;
    
    // the player score (the current snake size - the default snake size)
    sf::Text m_score;

    
public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay()override;
     void Init() override;
     void ProcessInput()override;
     void Update(sf::Time deltaTime )override;
     void Draw()override;
};