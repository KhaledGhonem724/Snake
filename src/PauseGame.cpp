#include "PauseGame.hpp"
#include "GamePlay.hpp"
#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Context>& context) : m_context(context)
{
}

PauseGame::~PauseGame() {

}
void PauseGame::Init()
{
    // design the Title of the game main menu
    m_pauseGameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_pauseGameTitle.setString("Paused");
    m_pauseGameTitle.setCharacterSize(100); // the defaulte is 30
    // set the origin point of the item (the title after design)
    m_pauseGameTitle.setOrigin(m_pauseGameTitle.getLocalBounds().width/2,m_pauseGameTitle.getLocalBounds().height/2);
    // set the position of the item according to the windows coordinates, as the position is:
    // x axis: in the center ,
    // y axis: after 1/10 of the screen hight (from top to down)  
    m_pauseGameTitle.setPosition(m_context->m_window->getSize().x/2,m_context->m_window->getSize().y/2);
}
void PauseGame::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        // if the X clicked (mouse or keyboard)
        if (event.type == sf::Event::Closed) 
            m_context->m_window->close();        
        /// if any button is pressed, other than Enter (keyboard)
        else if (event.type== sf::Event::KeyPressed)
        {
            if (event.key.code==sf::Keyboard::Escape||event.key.code==sf::Keyboard::Return||event.key.code==sf::Keyboard::Space)
            {
                m_context->m_states->PopCurrent();

            }
        }

        
    }
}
void PauseGame::Update(sf::Time deltaTime )
{
   

}
void PauseGame::Draw()
{
    // display the menu title
    m_context->m_window->draw(m_pauseGameTitle);
    m_context->m_window->display();
}