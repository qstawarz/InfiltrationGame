//
// Created by Quentin on 11/17/2017.
//
#include <iostream>

#include "../../includes/Managers/UIManager.h"
#include "../../includes/Managers/DisplayManager.h"

using namespace Managers;

UIManager::UIManager(sf::RenderWindow *p_window, sf::Time *p_time) : m_window {p_window}, m_time {p_time},
                                                                     m_text {nullptr}, m_lastTime {}
{
    std::cout << "UIManager created" << std::endl;
}

UIManager::~UIManager()
{
    if (this->m_text != nullptr)
        delete this->m_text;

    std::cout << "UIManager destroyed" << std::endl;
}

void UIManager::Setup()
{
    this->m_text = new Text("../res/Fonts/Arial.ttf");
    this->m_text->getText()->setFillColor(sf::Color::White);
}

void UIManager::Update()
{
   this->m_lastTime = *this->m_time;
}

void UIManager::Display()
{
    //TODO Try to Display Time or GameOver
}

void UIManager::Time()
{
    float xBound = this->m_text->getText()->getFont()->getTexture(24u).getSize().x / 2.0f;

    this->m_text->getText()->setCharacterSize(24u);
    this->m_text->getText()->setPosition(DisplayManager::m_windowW / 2.0f - xBound, 0.0f);
    this->m_text->getText()->setString("TIME : " + std::to_string(this->m_time->asSeconds()));

    this->m_window->draw(*this->m_text->getText());
}

void UIManager::Score()
{
    float xBound = this->m_text->getText()->getFont()->getTexture(24u).getSize().x / 2.0f;

    this->m_text->getText()->setCharacterSize(24u);
    this->m_text->getText()->setPosition(DisplayManager::m_windowW / 2.0f - xBound,
                                         DisplayManager::m_windowH / 2.0f);
    this->m_text->getText()->setString("Score : " + std::to_string(this->m_lastTime.asSeconds()));

    this->m_window->draw(*this->m_text->getText());
}

void UIManager::GameOver()
{
    float xBound = this->m_text->getText()->getFont()->getTexture(50u).getSize().x / 2.0f;
    float yBound = this->m_text->getText()->getFont()->getTexture(50u).getSize().y / 2.0f;

    this->m_text->getText()->setCharacterSize(50u);
    this->m_text->getText()->setPosition(DisplayManager::m_windowW / 2.0f - xBound,
                                         DisplayManager::m_windowH / 2.0f - yBound);
    this->m_text->getText()->setString("GAME OVER");

    this->m_window->draw(*this->m_text->getText());
}