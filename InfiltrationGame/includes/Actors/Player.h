//
// Created by Quentin on 11/20/2017.
//

#ifndef DOTPRODUCT_PLAYER_H
#define DOTPRODUCT_PLAYER_H

#include <SFML/Graphics.hpp>

#include "IActor.h"
#include "../Utils/Vector.h"
#include "../Utils/Sprite.h"

using namespace Utils;

namespace Actors
{
    class Player : public IActor
    {
    private:
        sf::RenderWindow *m_window;
        sf::Time *m_deltaTime;

        Sprite *m_sprite;

        Vector<float> m_pos;
        Vector<float> *m_dir;

        float m_scale;
        float m_speed;

    public:
        explicit Player(sf::RenderWindow *p_window, sf::Time *p_deltaTime, Vector<float> *p_dir);
        ~Player();

        void Setup() override;
        void Update() override;
        void Display() override;
        void Move() override;

        Vector<float> *getPos();

    };
}

#endif //SFMLQUICKSTART_PLAYER_H