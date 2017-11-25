//
// Created by Quentin on 11/20/2017.
//
#include <iostream>

#include "../../includes/Actors/Enemy.h"
#include "../../includes/Managers/DisplayManager.h"

using namespace Actors;
using namespace Managers;

Enemy::Enemy(sf::RenderWindow *p_window,
             sf::Time *p_deltaTime,
             Vector<float> *p_playerPos,
             const Vector<float> &p_pos,
             const float &p_angle) : m_window {p_window}, m_deltaTime {p_deltaTime}, m_playerPos {p_playerPos},
                                     m_sprite {nullptr}, m_triangles {sf::VertexArray(sf::Triangles, 6)},
                                     m_pos {p_pos}, m_angle {p_angle}, m_scale {1.0f}, m_speed {10.0f},
                                     m_visionAngle {static_cast<float>(10.0f * (M_PI / 180.0f))},
                                     m_visionLength {250.0f}, m_playerIsIn {false}
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
    //FOV Triangle
    Vector<float> pt1 = this->m_pos.translate(this->m_visionLength, this->m_visionAngle);
    Vector<float> pt2 = this->m_pos.translate(this->m_visionLength, 0.0f);
    Vector<float> pt3 = this->m_pos.translate(this->m_visionLength, -this->m_visionAngle);
    //Triangle 1
    this->m_triangles[0].position = this->m_pos.toSFML();
    this->m_triangles[0].color = sf::Color::Green;
    this->m_triangles[1].position = pt1.toSFML();
    this->m_triangles[1].color = sf::Color::Green;
    this->m_triangles[2].position = pt2.toSFML();
    this->m_triangles[2].color = sf::Color::Green;
    //Triangle 2
    this->m_triangles[3].position = this->m_pos.toSFML();
    this->m_triangles[3].color = sf::Color::Green;
    this->m_triangles[4].position = pt2.toSFML();
    this->m_triangles[4].color = sf::Color::Green;
    this->m_triangles[5].position = pt3.toSFML();
    this->m_triangles[5].color = sf::Color::Green;
}

void Enemy::Update()
{
    this->m_pos.x() = this->m_sprite->getSprite()->getPosition().x;
    this->m_pos.y() = this->m_sprite->getSprite()->getPosition().y;

    if (this->m_playerIsIn)
    {   //Triangle 1
        this->m_triangles[0].color = sf::Color::Red;
        this->m_triangles[1].color = sf::Color::Red;
        this->m_triangles[2].color = sf::Color::Red;
        //Triangle 2
        this->m_triangles[3].color = sf::Color::Red;
        this->m_triangles[4].color = sf::Color::Red;
        this->m_triangles[5].color = sf::Color::Red;
    }
    else
    {   //Triangle 1
        this->m_triangles[0].color = sf::Color::Green;
        this->m_triangles[1].color = sf::Color::Green;
        this->m_triangles[2].color = sf::Color::Green;
        //Triangle 2
        this->m_triangles[3].color = sf::Color::Green;
        this->m_triangles[4].color = sf::Color::Green;
        this->m_triangles[5].color = sf::Color::Green;
    }

    this->Move();
    this->Intersect();
}

void Enemy::Display()
{
    this->m_window->draw(this->m_triangles);
    this->m_window->draw(*this->m_sprite->getSprite());
}

void Enemy::Move()
{
//    auto angle = static_cast<float>(90.0f * (M_PI / 180.0f));
//    this->m_sprite->getSprite()->rotate(angle * this->m_speed * this->m_deltaTime->asSeconds());

    //TODO Recalculate pos of FOV for the enemy rotate
}

void Enemy::Intersect()
{
    float length = this->m_pos.length(*this->m_playerPos);
    float angle = this->m_pos.atan2BetweenVectors(*this->m_playerPos);
    angle -= 180;

    this->m_playerIsIn = ((length < this->m_visionLength) &&
                          (abs(static_cast<int>(angle)) < (this->m_visionAngle) * 180 / M_PI)) ||
                         ((length < this->m_visionLength) &&
                          (abs(static_cast<int>(angle)) > 360.0f - ((this->m_visionAngle) * 180 / M_PI)));
}