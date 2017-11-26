//
// Created by Quentin on 11/17/2017.
//

#ifndef DOTPRODUCT_UIMANAGER_H
#define DOTPRODUCT_UIMANAGER_H

#include <SFML/Graphics.hpp>

#include "IManager.h"
#include "../Utils/Text.h"

using namespace Utils;

namespace Managers
{
    class UIManager : public IManager
    {
    private:
        sf::RenderWindow *m_window;
        sf::Time *m_time;

        sf::Time m_lastTime;

        Text *m_text;

    public:
        explicit UIManager(sf::RenderWindow *p_window, sf::Time *p_time);
        ~UIManager();

        void Setup() override;
        void Update() override;

        void Display();

        void Time();
        void Score();
        void GameOver();

    };
}

#endif //CATCH_ME_UIMANAGER_H