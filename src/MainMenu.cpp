#include "MainMenu.hpp"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context) : m_context(context)
{
    sf::Text temp; 
    mainMenuButtons[2]=std::make_pair("Play",temp);
    mainMenuButtons[5]=std::make_pair("Exit",temp);
    selected=mainMenuButtons.begin();
}

MainMenu::~MainMenu() {

}
void MainMenu::Init()
{
    // todo : prepare Documentation  
    m_context->m_assets->AddFont(MAIN_FONT,"assets/fonts/PermanentMarker-Regular.ttf");
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake Game");
    m_gameTitle.setCharacterSize(60); // the defaulte is 30
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width/2,m_gameTitle.getLocalBounds().height/2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x/2,m_context->m_window->getSize().y/10);

    int cnt=1;
    std::map<int ,std::pair< std::string ,sf::Text > >::iterator i=mainMenuButtons.begin();
    while (i!=mainMenuButtons.end())
    {
        i->second.second.setFont(m_context->m_assets->GetFont(MAIN_FONT));
        i->second.second.setString(i->second.first);
        i->second.second.setCharacterSize(40); // the defaulte is 30
        i->second.second.setOrigin(i->second.second.getLocalBounds().width/2,i->second.second.getLocalBounds().height/2);
        i->second.second.setPosition(m_context->m_window->getSize().x/2,m_context->m_window->getSize().y/10+  (m_context->m_window->getSize().y*9/10/ (mainMenuButtons.size()+1) )*cnt );
        ++cnt;
        i++;
    }
    

}
void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type== sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Return)
        {
            /* code */
        }
        else if (event.type== sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up :
            {
                if (selected==mainMenuButtons.begin())
                {
                    selected=mainMenuButtons.end();
                }
                selected--;
                break;
            }
            case sf::Keyboard::Down :
            {
                selected++;
                if (selected==mainMenuButtons.end())
                {
                    selected=mainMenuButtons.begin();
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }

        
    }
}
void MainMenu::Update(sf::Time deltaTime )
{
    std::map<int ,std::pair< std::string ,sf::Text > >::iterator i=mainMenuButtons.begin();
    while (i!=mainMenuButtons.end())
    {
        i->second.second.setFillColor(sf::Color::White);
        i++;
    }
    selected->second.second.setFillColor(sf::Color::Yellow);
    // todo: 
    // handle pressed 
}
void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color(50,50,50));
    m_context->m_window->draw(m_gameTitle);

    // todo : documentation + Edit documentation
    //m_context->m_window->draw(mainMenuButtons.begin()->second.first);
    //m_context->m_window->draw(mainMenuButtons["Play"].first);
    //m_context->m_window->draw(mainMenuButtons["Exit"].first);
    std::map<int ,std::pair< std::string ,sf::Text > >::iterator i=mainMenuButtons.begin();
    while (i!=mainMenuButtons.end())
    {
        m_context->m_window->draw(i->second.second);
        i++;
    }
    m_context->m_window->display();
}