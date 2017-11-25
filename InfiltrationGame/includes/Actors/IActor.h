//
// Created by Quentin on 11/20/2017.
//

#ifndef DOTPRODUCT_IACTOR_H
#define DOTPRODUCT_IACTOR_H

namespace Actors
{
    class IActor
    {
    public:
        virtual ~IActor() = default;

        virtual void Setup() = 0;
        virtual void Update() = 0;
        virtual void Display() = 0;
        virtual void Move() = 0;

    };
}

#endif //SFMLQUICKSTART_IACTOR_H