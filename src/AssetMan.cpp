#include "AssetMan.hpp"

Engine::AssetMan::AssetMan() {

}

Engine::AssetMan::~AssetMan() {

}
void Engine::AssetMan::AddTexture(int id,const std::string& filePath,bool isRepeated){
    auto texture = std::make_unique<sf::Texture>();
    if (texture->loadFromFile(filePath))// if loading is done succussfully 
    {
        texture->setRepeated(isRepeated);// function from the SFML library itself
        m_textures[id]=std::move(texture);//  store the texture into our map
    }
    
}
void Engine::AssetMan::AddFont(int id,const std::string& filePath){
    auto font = std::make_unique<sf::Font>();
    if (font->loadFromFile(filePath))// if loading is done succussfully 
    {
        m_fonts[id]=std::move(font);//  store the font into our map
    }
}
const sf::Texture &Engine::AssetMan::GetTexture(int id)const{
    return *m_textures.at(id).get();
}
const sf::Font &Engine::AssetMan::GetFont(int id)const{
    return *m_fonts.at(id).get();
}