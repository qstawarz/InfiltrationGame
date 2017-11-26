//
// Created by Quentin on 11/20/2017.
//
#include <iostream>

#include "../../includes/Actors/Enemy.h"
#include "../../includes/Managers/DisplayManager.h"

using namespace Actors;
using namespace Managers;

int Enemy::m_countId = 0;

Enemy::Enemy(sf::RenderWindow *p_window,
             sf::Time *p_deltaTime,
             Vector<float> *p_playerPos,
             const Vector<float> &p_pos,
             const float &p_angle) : m_window {p_window}, m_deltaTime {p_deltaTime}, m_playerPos {p_playerPos},
                                     m_sprite {nullptr}, m_lines {sf::VertexArray(sf::Lines, 4)},
                                     m_pos {p_pos}, m_initialForward {}, m_forward {}, m_line1 {}, m_line2 {},
                                     m_initialAngle {p_angle}, m_angle {360 - p_angle}, m_rotation {1.0f},
                                     m_scale {1.0f}, m_speed {10.0f}, m_clockWiseBack {},
                                     m_visionAngle {static_cast<float>(/*(rand()%30 + 10)*/10.0f * (M_PI / 180.0f))},
                                     m_visionLength {/*rand()%300 + 100*/250.0f}, m_isIn {false}, m_clockWise {true},
                                     m_id {++m_countId}
{
    std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
    if (this->m_sprite != nullptr)
        delete this->m_sprite;

    std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::Setup()
{   //Sprite
    this->m_sprite = new Sprite("../res/Assets/enemy.png");

    float xBound = this->m_sprite->getSprite()->getTextureRect().width / 2.0f;
    float yBound = this->m_sprite->getSprite()->getTextureRect().height / 2.0f;

    this->m_sprite->getSprite()->setOrigin(xBound, yBound);
    this->m_sprite->getSprite()->setPosition(this->m_pos.toSFML());
    this->m_sprite->getSprite()->scale(Vector<float>(this->m_scale, this->m_scale, true).toSFML());
    this->m_sprite->getSprite()->rotate(this->m_angle);
    //Vector forward
    this->m_forward = this->m_pos.translate(this->m_visionLength,
                                            static_cast<float>(0.0f + this->m_angle * (M_PI / 180.0f)));
    this->m_forward -= this->m_pos;
    this->m_initialForward = this->m_forward;
    //FOV
    this->m_line1 = this->m_pos.translate(this->m_visionLength,
                                              static_cast<float>(this->m_visionAngle + this->m_angle * (M_PI / 180.0f)));
    this->m_line2 = this->m_pos.translate(this->m_visionLength,
                                              static_cast<float>(-this->m_visionAngle + this->m_angle * (M_PI / 180.0f)));
    //Line 1
    this->m_lines[0].position = this->m_pos.toSFML();
    this->m_lines[0].color = sf::Color::Green;
    this->m_lines[1].position = this->m_line1.toSFML();
    this->m_lines[1].color = sf::Color::Green;
    //Line 2
    this->m_lines[2].position = this->m_pos.toSFML();
    this->m_lines[2].color = sf::Color::Green;
    this->m_lines[3].position = this->m_line2.toSFML();
    this->m_lines[3].color = sf::Color::Green;
}

void Enemy::Update()
{   //Pos
    this->m_pos.x() = this->m_sprite->getSprite()->getPosition().x;
    this->m_pos.y() = this->m_sprite->getSprite()->getPosition().y;
    //Vector forward
    this->m_forward = this->m_pos.translate(this->m_visionLength,
                                              static_cast<float>(0.0f + this->m_angle * (M_PI / 180.0f)));
    this->m_forward -= this->m_pos;
    //FOV
    this->m_line1 = this->m_pos.translate(this->m_visionLength,
                                              static_cast<float>(this->m_visionAngle + this->m_angle * (M_PI / 180.0f)));
    this->m_line2 = this->m_pos.translate(this->m_visionLength,
                                              static_cast<float>(-this->m_visionAngle + this->m_angle * (M_PI / 180.0f)));
    //Line 1
    this->m_lines[0].position = this->m_pos.toSFML();
    this->m_lines[1].position = this->m_line1.toSFML();
    //Line 2
    this->m_lines[2].position = this->m_pos.toSFML();
    this->m_lines[3].position = this->m_line2.toSFML();

    this->Move();
    this->Intersect();
}

void Enemy::Display()
{
    this->m_window->draw(this->m_lines);
    this->m_window->draw(*this->m_sprite->getSprite());
}

void Enemy::Move()
{
    float angle = this->m_forward.angle2D(this->m_initialForward);

    if (this->m_clockWise && angle < 45 - (this->m_visionAngle * (180 / M_PI)))
    {
        this->m_clockWiseBack = this->m_forward;

        this->m_sprite->getSprite()->rotate(this->m_rotation * this->m_speed * this->m_deltaTime->asSeconds());
        this->m_angle += this->m_rotation * this->m_speed * this->m_deltaTime->asSeconds();
    }
    else
    {
        angle = this->m_forward.angle2D(this->m_clockWiseBack);
        this->m_clockWise = false;

        this->m_sprite->getSprite()->rotate(-this->m_rotation * this->m_speed * this->m_deltaTime->asSeconds());
        this->m_angle += -this->m_rotation * this->m_speed * this->m_deltaTime->asSeconds();

        if (angle > 89 - (this->m_visionAngle * (180 / M_PI)) * 2)
            this->m_clockWise = true;
    }
}

void Enemy::Intersect()
{   //Vector between Player and Camera
    Vector<float> newPlayerPos = *this->m_playerPos - this->m_pos;

    float length = this->m_pos.length(*this->m_playerPos);
    float angle = this->m_forward.angle2D(newPlayerPos);
    //In / Out condition
    this->m_isIn = ((length < this->m_visionLength) && (angle < (this->m_visionAngle * (180 / M_PI))));
    if (this->m_isIn)
    {   //Line 1
        this->m_lines[0].color = sf::Color::Red;
        this->m_lines[1].color = sf::Color::Red;
        //Line 2
        this->m_lines[2].color = sf::Color::Red;
        this->m_lines[3].color = sf::Color::Red;
    }
    else
    {   //Line 1
        this->m_lines[0].color = sf::Color::Green;
        this->m_lines[1].color = sf::Color::Green;
        //Line 2
        this->m_lines[2].color = sf::Color::Green;
        this->m_lines[3].color = sf::Color::Green;
    }
}

bool Enemy::IsIn() const
{
    return this->m_isIn;
}