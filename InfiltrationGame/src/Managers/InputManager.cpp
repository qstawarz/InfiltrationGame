//
// Created by Quentin on 11/14/2017.
//
#include <iostream>

#include "../../includes/Managers/InputManager.h"

using namespace Managers;

InputManager::InputManager(sf::RenderWindow *p_window) : m_window {p_window}, m_event {nullptr},
                                                         m_vertical {0.0f, 0.0f, true}, m_horizontal {0.0f, 0.0f, true},
                                                         m_dir {0.0f, 0.0f, true}
{
    std::cout << "InputManager created" << std::endl;
}

InputManager::~InputManager()
{
    if (this->m_event != nullptr)
        delete this->m_event;

    std::cout << "InputManager destroyed" << std::endl;
}

void InputManager::Setup()
{
    this->m_event = new sf::Event;
}

void InputManager::Update()
{
    this->checkInput();
}

sf::Event *InputManager::getEvent() const
{
    return this->m_event;
}

Vector<float> *InputManager::getDir()
{
    return &this->m_dir;
}

void InputManager::checkInput()
{
    while (this->m_window->pollEvent(*this->m_event))
    {
        if (this->m_event->type == sf::Event::Closed)
            this->m_window->close();

        if (this->m_event->key.code == sf::Keyboard::Escape)
            this->m_window->close();

        if(this->m_event->type == sf::Event::KeyPressed)
        {
            //Move Up
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                this->m_vertical.y() = -1.0f;
            //Move Down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                this->m_horizontal.y() = 1.0f;
            //Move Left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                this->m_vertical.x() = -1.0f;
            //Move Right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                this->m_horizontal.x() = 1.0f;
        }

        if(this->m_event->type == sf::Event::KeyReleased)
        {
            if (this->m_event->key.code == sf::Keyboard::W || this->m_event->key.code == sf::Keyboard::Up)
                this->m_vertical.y() = 0.0f;
            if (this->m_event->key.code == sf::Keyboard::S || this->m_event->key.code == sf::Keyboard::Down)
                this->m_horizontal.y() = 0.0f;
            if (this->m_event->key.code == sf::Keyboard::A || this->m_event->key.code == sf::Keyboard::Left)
                this->m_vertical.x() = 0.0f;
            if (this->m_event->key.code == sf::Keyboard::D || this->m_event->key.code == sf::Keyboard::Right)
                this->m_horizontal.x() = 0.0f;
        }
        this->m_dir = this->m_vertical + this->m_horizontal;
    }
}