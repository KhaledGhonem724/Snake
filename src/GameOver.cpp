#include "GameOver.hpp"
#include "GamePlay.hpp"
#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context>& context) : m_context(context)
{
    sf::Text temp; 
    gameOverButtons[2]=std::make_pair(std::make_pair("Retry",false),temp);
    gameOverButtons[5]=std::make_pair(std::make_pair("Exit",false),temp);
    selected=gameOverButtons.begin();
}

GameOver::~GameOver() {

}
void GameOver::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT,"assets/fonts/PermanentMarker-Regular.ttf");
    // design the Title of the game main menu
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setCharacterSize(60); // the defaulte is 30
    // set the origin point of the item (the title after design)
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width/2,m_gameOverTitle.getLocalBounds().height/2);
    // set the position of the item according to the windows coordinates, as the position is:
    // x axis: in the center ,
    // y axis: after 1/10 of the screen hight (from top to down)  
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x/2,m_context->m_window->getSize().y/10);

    // design the options of the main menu
    int cnt=1;
    std::map<int ,std::pair< std::pair<std::string,bool> ,sf::Text > >::iterator i=gameOverButtons.begin();
    while (i!=gameOverButtons.end())
    {
        i->second.second.setFont(m_context->m_assets->GetFont(MAIN_FONT));
        i->second.second.setString(i->second.first.first);
        i->second.second.setCharacterSize(40); // the defaulte is 30
        i->second.second.setOrigin(i->second.second.getLocalBounds().width/2,i->second.second.getLocalBounds().height/2);
        // set the position of the item, as the position is:
        // x axis: in the center ,
        // y axis: changes according to the option place in the menu
        // the formula  : theTitleArea + theOptionPlaceInMenu * theLeftLength / number of the options  
        // Equals       :    1/10      +        cnt           *     9/10      /         menuSize     
        i->second.second.setPosition(m_context->m_window->getSize().x/2,m_context->m_window->getSize().y/10+  (m_context->m_window->getSize().y*9/10/ (gameOverButtons.size()+1) )*cnt );
        ++cnt;
        i++;// go to next option (next element of the menu)
    }
    

}
void GameOver::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        // if the X clicked (mouse or keyboard)
        if (event.type == sf::Event::Closed) 
            m_context->m_window->close();
        /// if the Enter button is pressed (keyboard)
        else if (event.type== sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Return) 
        {
            // switch the boolean value in the selected menu option to true
            selected->second.first.second=true;
        }
        /// if any button is pressed, other than Enter (keyboard)
        else if (event.type== sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up :// if the button is the upward arrow
            {
                // go up in the list
                if (selected==gameOverButtons.begin())// if you are on the first option go to the last one
                {
                    selected=gameOverButtons.end();
                }
                selected--;
                break;
            }
            case sf::Keyboard::Down :// if the button is the downward arrow
            {
                // go down in the list
                selected++;
                if (selected==gameOverButtons.end())// if you are on the last option go back to the first one
                {
                    selected=gameOverButtons.begin();
                }
                break;
            }
            default:// else
            {
                break;
            }
            }
        }

        
    }
}
void GameOver::Update(sf::Time deltaTime )
{
    std::map<int ,std::pair< std::pair<std::string,bool> ,sf::Text > >::iterator i=gameOverButtons.begin();
    // iterate over the map to and color all options with White
    while (i!=gameOverButtons.end())
    {
        i->second.second.setFillColor(sf::Color::White);
        i++;
    }
    // icolor the selected option with Yellow
    selected->second.second.setFillColor(sf::Color::Yellow);
    // if the selected option was pressed
    if (selected->second.first.second)
    {
        // se it as not pressed
        selected->second.first.second=false;
        /************************************************************************/
        /**************** Step 3 : add your if condition here *******************/
        /************************************************************************/
        /*
            check if the string of the selected option is the same as your page's name
            if so, use this line:  
            m_context->m_states->Add(std::make_unique<#YourClass#>(m_context),#replace#);
            #YourClass# : the class you have included in step 1
            #replace#   : boolean value :: 
                true : replace the current state (screen) 
                false: keep the current state (screen) and push your state in the stack 
            OR 
            you can add your own response
        */
        /************************************************************************/

        // fetch the right screen (state) according to the selected option
        if (selected->second.first.first=="Retry")// the first option ( the game itself)
        {
            m_context->m_states->Add(std::make_unique<GamePlay>(m_context),true);
        }
        else if (selected->second.first.first=="Exit")// the third option (close the game)
        {
            m_context->m_window->close();
        }
    }

}
void GameOver::Draw()
{
    // clear / remove every thing
    m_context->m_window->clear(sf::Color(50,50,50));
    // display the menu title
    m_context->m_window->draw(m_gameOverTitle);


    std::map<int ,std::pair< std::pair<std::string,bool> ,sf::Text > >::iterator i=gameOverButtons.begin();
    // iterate over the map to and display  all options 
    while (i!=gameOverButtons.end())
    {
        m_context->m_window->draw(i->second.second);
        i++;
    }
    m_context->m_window->display();
}