#pragma once
#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
namespace Engine{
class AssetMan {
private:
    // to store all fonts and textures
    std::map<int,std::unique_ptr<sf::Texture>> m_textures;
    std::map<int,std::unique_ptr<sf::Font>> m_fonts;
public:
    AssetMan();
    ~AssetMan();
    void AddTesture(int id,const std::string& filePath,bool isRepeated);
    // isRepeated : if the texture will be repeated to fill the mindow
    void AddFont(int id,const std::string& filePath);
    const sf::Texture &GetTexture(int id)const;
    const sf::Font &GetFont(int id)const;
};
}
