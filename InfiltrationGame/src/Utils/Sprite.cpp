//
// Created by Quentin on 11/14/2017.
//
#include <iostream>

#include "../../includes/Utils/Sprite.h"

using namespace Utils;

Sprite::Sprite(const std::string &p_filename) : m_texture {nullptr}, m_sprite {nullptr}
{
    this->loadSprite(p_filename);

    std::cout << "Sprite created" << std::endl;
}

Sprite::~Sprite()
{
    if (this->m_sprite != nullptr)
        delete this->m_sprite;

    if (this->m_texture != nullptr)
        delete this->m_texture;

    std::cout << "Sprite destroyed" << std::endl;
}

sf::Sprite *Sprite::getSprite() const
{
    return this->m_sprite;
}

void Sprite::loadSprite(const std::string &p_filename)
{
    this->m_texture = new sf::Texture;

    if (this->m_texture != nullptr)
    {
        this->m_texture->loadFromFile(p_filename);
        this->m_sprite = new sf::Sprite(*m_texture);
    }
}