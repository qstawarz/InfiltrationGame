//
// Created by Quentin on 11/20/2017.
//
#include <iostream>

#include "../../includes/Actors/Player.h"
#include "../../includes/Managers/DisplayManager.h"

using namespace Actors;
using namespace Managers;

Player::Player(sf::RenderWindow *p_window,
               sf::Time *p_deltaTime,
               Vector<float> *p_dir) : m_window {p_window}, m_dir {p_dir}, m_deltaTime {p_deltaTime},
                                       m_sprite {nullptr},
                                       m_pos {DisplayManager::m_windowW / 2, DisplayManager::m_windowH / 2, true},
                                       m_scale {0.2f}, m_speed {250.0f}
{
    std::cout << "Player created" << std::endl;
}

Player::~Player()
{
    if (this->m_sprite != nullptr)
        delete this->m_sprite;

    std::cout << "Player destroyed" << std::endl;
}

void Player::Setup()
{   //Sprite
    this->m_sprite = new Sprite("../res/Assets/Player.png");

    float xBound = this->m_sprite->getSprite()->getTextureRect().width / 2.0f;
    float yBound = this->m_sprite->getSprite()->getTextureRect().height / 2.0f;

    this->m_sprite->getSprite()->setOrigin(xBound, yBound);
    this->m_sprite->getSprite()->setPosition(this->m_pos.toSFML());
    this->m_sprite->getSprite()->scale(Vector<float>(this->m_scale, this->m_scale, true).toSFML());
}

void Player::Update()
{
    this->m_pos.x() = this->m_sprite->getSprite()->getPosition().x;
    this->m_pos.y() = this->m_sprite->getSprite()->getPosition().y;

    this->Move();
}

void Player::Display()
{
    this->m_window->draw(*this->m_sprite->getSprite());
}

void Player::Move()
{
    this->m_sprite->getSprite()->move(this->m_dir->toSFML() * this->m_speed * this->m_deltaTime->asSeconds());
}

Vector<float> *Player::getPos()
{
    return &this->m_pos;
}