//
// Created by Quentin on 11/14/2017.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <cmath>
#include <SFML/System/Vector3.hpp>

namespace Utils
{
    template <typename T>
    class Vector
    {
    private:
        T m_x;
        T m_y;
        T m_z;

        sf::Vector2<T> m_SFMLVector2D;

    public:
        Vector() : m_x {0}, m_y {0}, m_z {0} {}
        explicit Vector(T p_x, T p_y, T p_z) : m_x {p_x}, m_y {p_y}, m_z {p_z} {}
        explicit Vector(T p_xOrLength, T p_yOrAngle, bool isCoordinate)
        {
            if (isCoordinate)
            {
                this->m_x = p_xOrLength;
                this->m_y = p_yOrAngle;
                this->m_z = 0;
            }
            else
            {
                this->m_x = p_xOrLength * cos(p_yOrAngle);
                this->m_y = p_xOrLength * sin(p_yOrAngle);
                this->m_z = 0;
            }

//            std::cout << "Vector created" << std::endl;
        }
        ~Vector()
        {
//            std::cout << "Vector destroyed" << std::endl;
        }
        Vector(const Vector<T> &p_other) : m_x {p_other.m_x}, m_y {p_other.m_y}, m_z {p_other.m_z} {}
        explicit Vector(const T &p_f) : m_x {p_f}, m_y {p_f}, m_z {p_f} {}
        Vector &operator=(const Vector<T> &p_other)
        {
            this->m_x = p_other.m_x;
            this->m_y = p_other.m_y;
            this->m_z = p_other.m_z;

            return *this;
        }

        T x() const { return this->m_x; }
        T y() const { return this->m_y; }
        T z() const { return this->m_z; }

        T &x() { return this->m_x; }
        T &y() { return this->m_y; }
        T &z() { return this->m_z; }

//    static Vector one = Vector(1.0f, 1.0f, 1.0f);
//    static Vector zero = Vector();
//    static Vector right = Vector(1.0f, 0.0f, 0.0f);     //x
//    static Vector left = Vector(-1.0f, 0.0f, 0.0f);     //x
//    static Vector up = Vector(0.0f, 1.0f, 0.0f);        //y
//    static Vector down = Vector(0.0f, -1.0f, 0.0f);     //y
//    static Vector forward = Vector(0.0f, 0.0f, 1.0f);   //z
//    static Vector back = Vector(0.0f, 0.0f, -1.0f);     //z

        T &operator[](const int &p_i)
        {
            if (p_i == 0 || p_i == 'x')
            {
                return this->m_x;
            }
            else if (p_i == 1 || p_i == 'y')
            {
                return this->m_y;
            }
            else if (p_i == 2 || p_i == 'z')
            {
                return this->m_z;
            }
        }

        T &operator[](const std::string &p_s)
        {
            if (p_s == "x")
            {
                return this->m_x;
            }
            else if (p_s == "y")
            {
                return this->m_y;
            }
            else if (p_s == "z")
            {
                return this->m_z;
            }
        }

        Vector add(const Vector &p_other) const
        {
            Vector add;

            add.m_x = (this->m_x + p_other.m_x);
            add.m_y = (this->m_y + p_other.m_y);
            add.m_z = (this->m_z + p_other.m_z);

            return add;
        }

        Vector add(const Vector &p_other)
        {
            this->m_x += p_other.m_x;
            this->m_y += p_other.m_y;
            this->m_z += p_other.m_z;
        }

        Vector subtract(const Vector &p_other) const
        {
            Vector<T> subtract;

            subtract.m_x = (this->m_x - p_other.m_x);
            subtract.m_y = (this->m_y - p_other.m_y);
            subtract.m_z = (this->m_z - p_other.m_z);

            return subtract;
        }

        Vector subtract(const Vector &p_other)
        {
            this->m_x -= p_other.m_x;
            this->m_y -= p_other.m_y;
            this->m_z -= p_other.m_z;
        }

        Vector scale(const T &p_f) const
        {
            Vector<T> scale;

            scale.m_x = (this->m_x * p_f);
            scale.m_y = (this->m_y * p_f);
            scale.m_z = (this->m_z * p_f);

            return scale;
        }

        Vector scale(const T &p_f)
        {
            this->m_x *= p_f;
            this->m_y *= p_f;
            this->m_z *= p_f;
        }

        Vector divide(const T &p_f) const
        {
            Vector<T> divide;

            divide.m_x = (this->m_x / p_f);
            divide.m_y = (this->m_y / p_f);
            divide.m_z = (this->m_z / p_f);

            return divide;
        }

        Vector divide(const T &p_f)
        {
            this->m_x /= p_f;
            this->m_y /= p_f;
            this->m_z /= p_f;
        }

        T magnitude() const
        {
            T magnitude = 0;

            magnitude = sqrt(pow(this->m_x, 2) +
                             pow(this->m_y, 2) +
                             pow(this->m_z, 2));

            return magnitude;
        }

        T dotProduct(const Vector &p_other) const
        {
            T dotProduct = 0;

            dotProduct = this->m_x * p_other.m_x +
                         this->m_y * p_other.m_y +
                         this->m_z * p_other.m_z;

            return dotProduct;
        }

        Vector crossProduct3D(const Vector &p_other) const
        {
            Vector<T> crossProduct;

            crossProduct.m_x = (this->m_y * p_other.m_z - p_other.m_y * this->m_z);
            crossProduct.m_y = -(this->m_x * p_other.m_z - p_other.m_x * this->m_z);
            crossProduct.m_z = (this->m_x * p_other.m_y - p_other.m_x * this->m_y);

            return crossProduct;
        }

        T crossProduct2D(const Vector &p_other) const
        {
            T crossProduct;

            crossProduct = (this->m_x * p_other.m_y - this->m_y* p_other.m_y);

            return crossProduct;
        }

        Vector normalize() const
        {
            Vector<T> normalize;
            T length = this->magnitude();

            normalize.m_x = this->m_x / length;
            normalize.m_y = this->m_y / length;
            normalize.m_z = this->m_z / length;

            return normalize;
        }

        Vector normalize()
        {
            T length = this->magnitude();

            this->m_x /= length;
            this->m_y /= length;
            this->m_z /= length;
        }


        T angle2D(const Vector &p_other) const
        {
            T angle = 0;

            angle = acos(this->dotProduct(p_other) / (this->magnitude() * p_other.magnitude()));
            angle *= (180 / M_PI);

            return angle;
        }

        T atan2BetweenVectors(const Vector &p_other) const
        {
            T angle = 0;

            angle = atan2(this->m_y - p_other.m_y, this->m_x - p_other.m_x);
            angle *= (180 / M_PI);

            return angle;
        }

        T atant2() const
        {
            T angle = 0;

            angle = atan2(this->m_y, this->m_x);
            angle *= (180 / M_PI);

            return angle;
        }

        T length(const Vector &p_other) const
        {
            T length = 0;

            length = sqrt(pow(this->m_x - p_other.m_x, 2) +
                          pow(this->m_y - p_other.m_y, 2) +
                          pow(this->m_z - p_other.m_z, 2));

            return length;
        }

        Vector translate(T &p_length, T p_angle) const
        {
            Vector<T> newVector;

            newVector.x() = p_length * cos(p_angle) + this->m_x;
            newVector.y() = p_length * sin(p_angle) + this->m_y;

            return newVector;
        }

        Vector mirror(const Vector &p_other) const
        {
            Vector<T> newVector;

            newVector.x() = p_other.m_x + this->m_x;
            newVector.y() = p_other.m_y + this->m_y;

            return newVector;
        }

        Vector operator+(const Vector &p_other) const { return this->add(p_other); }
        Vector operator+=(const Vector &p_other) { return this->add(p_other); }
        Vector operator-(const Vector &p_other) const { return this->subtract(p_other); }
        Vector operator-=(const Vector &p_other) { return this->subtract(p_other); }
        Vector operator*(const T &p_f) const { return this->scale(p_f); }
        Vector operator*=(const T &p_f) { return this->scale(p_f); }
        Vector operator/(const T &p_f) const { return this->divide(p_f); }
        Vector operator/=(const T &p_f) { return this->divide(p_f); }

        bool operator==(const Vector &p_other)const { return this->magnitude() == p_other.magnitude(); }
        bool operator!=(const Vector &p_other)const { return this->magnitude() != p_other.magnitude(); }
        bool operator<(const Vector &p_other)const { return this->magnitude() < p_other.magnitude(); }
        bool operator<=(const Vector &p_other)const { return this->magnitude() <= p_other.magnitude(); }
        bool operator>(const Vector &p_other)const { return this->magnitude() > p_other.magnitude(); }
        bool operator>=(const Vector &p_other)const { return this->magnitude() >= p_other.magnitude(); }

        bool IsParallel(const Vector &p_other) { return this->crossProduct2D(p_other) == 0; }
        bool IsOpposed(const Vector &p_other) { return *this == (p_other * -1); }
        bool IsPerpendicular(const Vector &p_other) { return this->dotProduct(p_other) == 0; }
        bool IsNull() const { return this->m_x == 0 && this->m_y == 0 && this->m_z == 0; }
        bool IsNormalized() const { return this->magnitude() == 1; }

        sf::Vector2<T> &toSFML()
        {
            this->m_SFMLVector2D.x = this->m_x;
            this->m_SFMLVector2D.y = this->m_y;

            return this->m_SFMLVector2D;
        }
    };
}

template <typename T>
std::ostream &operator<<(std::ostream &p_os, Utils::Vector<T> &p_other)
{
    p_os << "(" << p_other.x() << ", " << p_other.y() << ", " << p_other.z() << ")";
    return p_os;
}

#endif //VECTOR_VECTOR_H