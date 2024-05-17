#include "StateMan.hpp"

Engine::StateMan::StateMan() : m_add(false),m_replace(false),m_remove(false){

}

Engine::StateMan::~StateMan() {

}
void Engine::StateMan::Add(std::unique_ptr<State> toAdd,bool replace){
    m_add=true;
    m_newState=std::move(toAdd);
    m_replace=replace;

}
void Engine::StateMan::PopCurrent(){
    m_remove=true;
}
void Engine::StateMan::ProcessStateChange(){
    if ( m_remove && !m_stateStack.empty() )
    {
        m_stateStack.pop();
        m_remove=false;
    }
    if ( m_add )
    {
        if ( m_replace && !m_stateStack.empty() )
        {
            m_stateStack.pop();
            m_replace=false;
        }
        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->Init();
        m_add=false;
    }
    
}
std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent(){
    return m_stateStack.top();
}
