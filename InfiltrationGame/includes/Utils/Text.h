//
// Created by Quentin on 11/16/2017.
//

#ifndef DOTPRODUCT_TEXT_H
#define DOTPRODUCT_TEXT_H

#include <SFML/Graphics.hpp>

namespace Utils
{
    class Text
    {
    private:
        sf::Font *m_font;
        sf::Text *m_text;

    public:
        explicit Text(const std::string &p_filename);
        ~Text();

        sf::Text *getText() const;

        void loadText(const std::string &p_filename);

    };
}

#endif //CATCH_ME_TEXT_H