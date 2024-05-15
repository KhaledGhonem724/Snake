#include "GamePlay.hpp"
#include "GameOver.hpp"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include <PauseGame.hpp>
GamePlay::GamePlay(std::shared_ptr<Context>& context): m_context(context)
, m_snakeDirection({20.f,0.f}) ,m_elapseTime(sf::Time::Zero)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay() {

}
void GamePlay::Init() {
    m_context->m_assets->AddTexture(GRASS,"assets/textures/grass/grass0.png",true);
    m_context->m_assets->AddTexture(FOOD,"assets/textures/food/food0.png");
    m_context->m_assets->AddTexture(WALL,"assets/textures/wall/wall0.png",true);
    m_context->m_assets->AddTexture(SNAKE,"assets/textures/snake/snake0.png");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for (auto &wall  : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }
    // Rect (0,0,0,0)
    // the first two parameter are the coordinats x,y (left , top)
    // the last two are the width and the height
    m_walls[0].setTextureRect({0,0,m_context->m_window->getSize().x,20});
    m_walls[1].setTextureRect({0,0,m_context->m_window->getSize().x,20});
    m_walls[1].setPosition(0,m_context->m_window->getSize().y-20);
    m_walls[2].setTextureRect({0,0,20,m_context->m_window->getSize().y});
    m_walls[3].setTextureRect({0,0,20,m_context->m_window->getSize().y});
    m_walls[3].setPosition(m_context->m_window->getSize().x-20,0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x/2,m_context->m_window->getSize().y/2);
    
    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));
    
}
void GamePlay::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        // if the X clicked (mouse or keyboard)
        if (event.type == sf::Event::Closed) 
            m_context->m_window->close();
        /// if any button is pressed, other than Enter (keyboard)
        else if (event.type== sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection=m_snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up :// if the button is the upward arrow
            {
                newDirection={0.f,-20.f};
                break;
            }
            case sf::Keyboard::Down :// if the button is the downward arrow
            {
                newDirection={0.f,20.f};
                break;
            }
            case sf::Keyboard::Left :// if the button is the upward arrow
            {
                newDirection={-20.f,0.f};
                break;
            }
            case sf::Keyboard::Right :// if the button is the downward arrow
            {
                newDirection={20.f,0.f};
                break;
            }
            case sf::Keyboard::Escape :// if the button is the downward arrow
            {
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;
            }
            default:// else
            {
                break;
            }
            // if not the opposite dirtection
            }
            if (std::abs(m_snakeDirection.x)!=std::abs(newDirection.x)
            ||std::abs(m_snakeDirection.y)!=std::abs(newDirection.y))
            {
                m_snakeDirection=newDirection;
            }
        }

        
    }
}
void GamePlay::Update(sf::Time deltaTime ){
    m_elapseTime+=deltaTime;
    if (m_elapseTime.asSeconds()>0.1)
    {
        for (auto & wall : m_walls)
        {
            if (m_snake.IsOn(wall))
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context),true );
                break;
            }
            
        }
        
        if (m_snake.IsOn(m_food))
        {
            m_snake.Grow(m_snakeDirection);
            int x=0,y=0;
            x=std::clamp<int>(rand()%m_context->m_window->getSize().x,20,m_context->m_window->getSize().x-40);
            y=std::clamp<int>(rand()%m_context->m_window->getSize().y,20,m_context->m_window->getSize().y-40);
            m_food.setPosition(x,y);
        }
        else{
            m_snake.Move(m_snakeDirection);
        }
        
        m_elapseTime=sf::Time::Zero;
    }
    
}
void GamePlay::Draw(){
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);
    
    for (auto &wall  : m_walls)
    {
       m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    
    
    
    
    m_context->m_window->display();
}
void GamePlay::Pause(){

}
void GamePlay::Start(){

}