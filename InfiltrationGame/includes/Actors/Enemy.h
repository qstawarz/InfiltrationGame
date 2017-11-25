//
// Created by Quentin on 11/20/2017.
//

#ifndef DOTPRODUCT_ENEMY_H
#define DOTPRODUCT_ENEMY_H

#include <SFML/Graphics.hpp>

#include "IActor.h"
#include "../Utils/Vector.h"
#include "../Utils/Sprite.h"

using namespace Utils;

namespace Actors
{
    class Enemy : public IActor
    {
    private:
        sf::RenderWindow *m_window;
        sf::Time *m_deltaTime;
        sf::VertexArray m_lines;

        Sprite *m_sprite;

        Vector<float> m_pos;
        Vector<float> m_forward;
        Vector<float> m_line1;
        Vector<float> m_line2;
        Vector<float> *m_playerPos;

        float m_scale;
        float m_speed;
        float m_angle;
        float m_rotation;
        float m_visionAngle; //Between ]0,45]
        float m_visionLength; //Between [100, 700]

        bool m_playerIsIn;

    public:
        explicit Enemy(sf::RenderWindow *p_window, sf::Time *p_deltaTime, Vector<float> *p_playerPos,
                       const Vector<float> &p_pos, const float &p_angle);
        ~Enemy();

        void Setup() override;
        void Update() override;
        void Display() override;
        void Move() override;

        void Intersect();

    };
}

#endif //SFMLQUICKSTART_ENEMY_H