//
// Created by Quentin on 11/14/2017.
//

#ifndef DOTPRODUCT_INPUTMANAGER_H
#define DOTPRODUCT_INPUTMANAGER_H

#include <SFML/Graphics.hpp>

#include "IManager.h"
#include "../Utils/Vector.h"

using namespace Utils;

namespace Managers
{
    class InputManager : public IManager
    {
    private:
        sf::RenderWindow *m_window;
        sf::Event *m_event;

        Vector<float> m_vertical;
        Vector<float> m_horizontal;
        Vector<float> m_dir;

    public:
        explicit InputManager(sf::RenderWindow *p_window);
        ~InputManager();

        void Setup() override;
        void Update() override;

        sf::Event *getEvent() const;
        Vector<float> *getDir();

        void checkInput();

    };
}

#endif //CATCH_ME_EVENTMANAGER_H