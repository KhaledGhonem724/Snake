#include "Game.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics/CircleShape.hpp>

Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(1280, 720), "SFML works!",sf::Style::Close);
    // we used Close style so the game can't be maximized 
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
    //todo :
    // add first state to m_states
}

Game::~Game() {

}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
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