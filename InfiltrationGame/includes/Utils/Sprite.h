//
// Created by Quentin on 11/14/2017.
//

#ifndef DOTPRODUCT_SPRITE_H
#define DOTPRODUCT_SPRITE_H

#include <SFML/Graphics.hpp>

namespace Utils
{
    class Sprite
    {
    private:
        sf::Texture *m_texture;
        sf::Sprite *m_sprite;

    public:
        explicit Sprite(const std::string &p_filename);
        ~Sprite();

        sf::Sprite *getSprite() const;

        void loadSprite(const std::string &p_filename);

    };
}

#endif //CATCH_ME_SPRITE_H