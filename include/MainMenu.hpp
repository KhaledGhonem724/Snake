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
    // to do : documant the context
    std::shared_ptr<Context> m_context;
    // the main menu title : it's stored in Text object
    // this Text object store the properties of a text 
    // to be displayed: color, font, size
    sf::Text m_gameTitle; 
    // this map is woking as a container of our menu options
    // each element is cosest of :
    // Integer -> (String       , Boolean       , Text )
    //   ID    -> (OptionName   , IsPressed     , textObjSFML )
    // ID           :   determine the options order
    // OptionName   :   what words to be displayed
    // IsPressed    :   what words to be displayed
    // textObjSFML  :   how will the OptionName be displayed 

    // the used data structure is the hashmap 
    // the key is integer , the value is a pair
    // this parent-pair cosists of two elements : child-pair and Text Obj. .
    // the child-pair is consist of two elements : string , boolean 
    // Integer -> ( [String       , Boolean]    , Text )
    std::map<int ,std::pair< std::pair<std::string,bool> ,sf::Text > >mainMenuButtons;
    std::map<int ,std::pair< std::pair<std::string,bool> ,sf::Text > >::iterator selected;

public:
    //note : `overide` keyword is just a good practice (optional) 
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();
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