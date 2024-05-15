#include "Snake.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    m_head=--m_body.end();
    m_tail=m_body.begin();
}

Snake::~Snake() {

}
void Snake::Init(const sf::Texture& texture){
    float x=20.f;
    for (auto & piece : m_body)
    {
        piece.setTexture(texture);
        piece.setPosition({x,20.f});
        x+=20.f;
    }
    
}
void Snake::Move(const sf::Vector2f& direction){
    m_tail->setPosition(m_head->getPosition()+direction);
    m_head=m_tail;
    m_tail++;
    if (m_tail==m_body.end())
    {
        m_tail=m_body.begin();
    }
    
}
bool Snake::IsOn(const sf::Sprite& other)const
{
    // intersects compair between the GlobalBounds of it's oblect and the parameter object
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}
void Snake::Grow(const sf::Vector2f& direction){
    sf::Sprite newPiese;
    newPiese.setTexture(*(m_body.begin()->getTexture()));
    newPiese.setPosition(m_head->getPosition()+direction);
    m_head=m_body.insert(++m_head,newPiese);
    
}

void Snake::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
    for (auto & piece : m_body)
    {
        target.draw(piece);
    }
}