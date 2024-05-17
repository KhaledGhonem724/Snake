// this is the main class of the game in which the main loop occures
#include "Game.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics/CircleShape.hpp>

Game::Game() : m_context(std::make_shared<Context>())
{
    // make a window 
    // we used Close style so the game can't be maximized 
    m_context->m_window->create(sf::VideoMode(1280, 720), "Snake Game",sf::Style::Close);
    // add the main menu as the first state (screen)
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game() {

}

void Game::Run()
{
    sf::Clock clock;// the clock start here 
    
    sf::Time timeSinceLastFrame=sf::Time::Zero;
    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame+=clock.restart();
        while (timeSinceLastFrame > TIME_PER_FRAME)// update only after 1/60 sec (to make the game 60 frame per second)
        {
            timeSinceLastFrame-=TIME_PER_FRAME;// reset the clock 
            // our main steps 
            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }        

    }
}