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

        Text *m_text;

    public:
        explicit UIManager(sf::RenderWindow *p_window);
        ~UIManager();

        void Setup() override;
        void Update() override;

        void Display();

        void Score();
        void GameOver();

    };
}

#endif //CATCH_ME_UIMANAGER_H