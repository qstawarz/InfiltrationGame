//
// Created by Quentin on 11/14/2017.
//
#include <iostream>

#include "../../includes/Managers/Game.h"

using namespace Managers;

Game::Game() : m_displayManager {nullptr}, m_inputManager {nullptr}, m_uiManager {nullptr},
               m_player {nullptr}, m_enemy1 {nullptr}, m_enemy2 {nullptr}, m_enemy3 {nullptr}, m_enemy4 {nullptr},
               m_clock {}, m_time {}, m_deltaTime {}, m_isGameOver {false}
{
    std::cout << "Game created" << std::endl;
}

Game::~Game()
{
    if (this->m_enemy4 != nullptr)
        delete this->m_enemy4;

    if (this->m_enemy3 != nullptr)
        delete this->m_enemy3;

    if (this->m_enemy2 != nullptr)
        delete this->m_enemy2;

    if (this->m_enemy1 != nullptr)
        delete this->m_enemy1;

    if (this->m_player != nullptr)
        delete this->m_player;

    if (this->m_uiManager != nullptr)
        delete this->m_uiManager;

    if (this->m_inputManager != nullptr)
        delete this->m_inputManager;

    if (this->m_displayManager != nullptr)
        delete this->m_displayManager;

    std::cout << "Game destroyed" << std::endl;
}

void Game::Setup()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    //DisplayManager
    this->m_displayManager = new DisplayManager;
    if (this->m_displayManager != nullptr)
        this->m_displayManager->Setup();
    //InputManager
    if (this->m_displayManager->IsStarted());
        this->m_inputManager = new InputManager(this->m_displayManager->getWindow());
    if (this->m_inputManager != nullptr)
        this->m_inputManager->Setup();
    //UIManager
    if (this->m_displayManager->IsStarted());
    this->m_uiManager = new UIManager(this->m_displayManager->getWindow(), &this->m_time);
    if (this->m_uiManager != nullptr)
        this->m_uiManager->Setup();
    //Player
    if (this->m_displayManager->IsStarted())
        this->m_player = new Player(this->m_displayManager->getWindow(), &this->m_deltaTime, this->m_inputManager->getDir());
    if (this->m_player != nullptr)
        this->m_player->Setup();
    //Enemy 1 TopLeft
    if (this->m_displayManager->IsStarted())
        this->m_enemy1 = new Enemy(this->m_displayManager->getWindow(), &this->m_deltaTime, this->m_player->getPos(),
                                   Vector<float>(0.0f, 0.0f, true), 315.0f);
    if (this->m_enemy1 != nullptr)
        this->m_enemy1->Setup();
    //Enemy 2 TopRight
    if (this->m_displayManager->IsStarted())
        this->m_enemy2 = new Enemy(this->m_displayManager->getWindow(), &this->m_deltaTime, this->m_player->getPos(),
                                   Vector<float>(DisplayManager::m_windowW, 0.0f, true), 225.0f);
    if (this->m_enemy2 != nullptr)
        this->m_enemy2->Setup();
    //Enemy 3 BotRight
    if (this->m_displayManager->IsStarted())
        this->m_enemy3 = new Enemy(this->m_displayManager->getWindow(), &this->m_deltaTime, this->m_player->getPos(),
                                   Vector<float>(DisplayManager::m_windowW, DisplayManager::m_windowH, true), 135.0f);
    if (this->m_enemy3 != nullptr)
        this->m_enemy3->Setup();
    //Enemy 4 BotLeft
    if (this->m_displayManager->IsStarted())
        this->m_enemy4 = new Enemy(this->m_displayManager->getWindow(), &this->m_deltaTime, this->m_player->getPos(),
                                   Vector<float>(0.0f, DisplayManager::m_windowH, true), 45.0f);
    if (this->m_enemy4 != nullptr)
        this->m_enemy4->Setup();
}

void Game::Update()
{
    this->m_displayManager->Update();

    this->m_inputManager->Update();

    if (!this->m_isGameOver)
        this->m_uiManager->Update();

    if (!this->m_isGameOver)
        this->m_player->Update();

    if (!this->m_enemy1->IsIn())
        this->m_enemy1->Update();
    if (!this->m_enemy2->IsIn())
        this->m_enemy2->Update();
    if (!this->m_enemy3->IsIn())
        this->m_enemy3->Update();
    if (!this->m_enemy4->IsIn())
        this->m_enemy4->Update();
}

void Game::Display()
{
    this->m_enemy4->Display();
    this->m_enemy3->Display();
    this->m_enemy2->Display();
    this->m_enemy1->Display();

    this->m_player->Display();

    if (!this->m_isGameOver)
    {
        this->m_uiManager->Display();
        this->m_uiManager->Time();
    }
    if (this->m_isGameOver || this->m_enemy1->IsIn() || this->m_enemy2->IsIn() || this->m_enemy3->IsIn() || this->m_enemy4->IsIn())
    {
        this->m_uiManager->GameOver();
        this->m_uiManager->Score();
        this->m_isGameOver = true;
    }

    this->m_displayManager->getWindow()->display();
}

void Game::Run()
{
    while (this->m_displayManager->IsRunning())
    {
        this->Update();

        this->Display();

        this->m_deltaTime = this->m_clock.restart();
        this->m_time += this->m_deltaTime;
    }
}