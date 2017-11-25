//
// Created by Quentin on 11/16/2017.
//
#include <iostream>

#include "../../includes/Utils/Text.h"

using namespace Utils;

Text::Text(const std::string &p_filename) : m_font {nullptr}, m_text {nullptr}
{
    this->loadText(p_filename);

    std::cout << "Text created" << std::endl;
}

Text::~Text()
{
    if (this->m_text != nullptr)
        delete this->m_text;

    if (this->m_font != nullptr)
        delete this->m_font;

    std::cout << "Text destroyed" << std::endl;
}

sf::Text *Text::getText() const
{
    return this->m_text;
}

void Text::loadText(const std::string &p_filename)
{
    this->m_font = new sf::Font;

    if (this->m_font != nullptr)
    {
        this->m_font->loadFromFile(p_filename);
        this->m_text = new sf::Text;
        this->m_text->setFont(*this->m_font);
    }
}