//
// Created by Quentin on 11/14/2017.
//
#include <iostream>

#include "../../includes/Managers/DisplayManager.h"

using namespace Managers;

DisplayManager::DisplayManager() : m_window {nullptr}, m_isStarted {false}
{
    std::cout << "DisplayManager created" << std::endl;
}

DisplayManager::~DisplayManager()
{
    if (this->m_window != nullptr)
        delete this->m_window;

    std::cout << "DisplayManager destroyed" << std::endl;
}

void DisplayManager::Setup()
{
    this->m_window = new sf::RenderWindow(sf::VideoMode(this->m_windowW, this->m_windowH), "Dot Product");

    if (this->m_window != nullptr)
        this->m_isStarted = true;

    this->m_window->setVerticalSyncEnabled(true);
    this->m_window->setFramerateLimit(60);
}

void DisplayManager::Update()
{
    this->m_window->clear();
}

sf::RenderWindow *DisplayManager::getWindow() const
{
    return this->m_window;
}

bool DisplayManager::IsRunning() const
{
    if (this->m_window == nullptr)
        return false;

    return this->m_window->isOpen();
}

bool DisplayManager::IsStarted() const
{
    return this->m_isStarted;
}