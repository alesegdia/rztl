#pragma once

#include <iostream>
#include <math.h>

namespace rztl {

    template <typename T>
    class Vec2 {
    public:
        Vec2() : m_x(0), m_y(0) {}
        Vec2(T x, T y) : m_x(x), m_y(y) {}
        Vec2(const Vec2<T>& other) : Vec2(other.m_x, other.m_y) {}

        static float EuclideanDistance(const Vec2<T>& a, const Vec2<T>& b)
        {
            float dx = ((float)a.GetX()) - ((float)b.GetX());
            float dy = ((float)a.GetY()) - ((float)b.GetY());
            return sqrtf(dx * dx + dy * dy);
        }

        static float ManhattanDistance(const Vec2<T>& a, const Vec2<T>& b)
        {
            return abs(a.GetX() - b.GetX()) + abs(a.GetY() - b.GetY());
        }

        void SetX(T newx)
        {
            m_x = newx;
        }

        void SetY(T newy)
        {
            m_y = newy;
        }

        T GetX() const
        {
            return m_x;
        }

        T GetY() const
        {
            return m_y;
        }

        void Set(T x, T y)
        {
            m_x = x; m_y = y;
        }

        void Set(const Vec2<T>& other)
        {
            m_x = other.GetX(); m_y = other.GetY();
        }

        void Translate(const Vec2<T>& other)
        {
            m_x += other.GetX();
            m_y += other.GetY();
        }

        Vec2<T> operator+(const Vec2<T>& other) const
        {
            return Vec2<T>(m_x + other.m_x, m_y + other.m_y);
        }

        Vec2<T> operator-(const Vec2<T>& other) const
        {
            return Vec2<T>(m_x - other.m_x, m_y - other.m_y);
        }

        Vec2<T> operator/(T other) const
        {
            return Vec2<T>(m_x / other, m_y / other);
        }

        Vec2& operator+= (const Vec2<T>& other)
        {
            m_x += other.GetX();
            m_y += other.GetY();
            return *this;
        }

        bool operator== (const Vec2<T>& other) const
        {
            return other.m_x == m_x && other.m_y == m_y;
        }

        bool operator != (const Vec2<T>& other) const
        {
            return !(other == *this);
        }

        Vec2& operator*= (float p)
        {
            m_x *= p;
            m_y *= p;
            return *this;
        }

        Vec2& operator*= (int p)
        {
            m_x *= p;
            m_y *= p;
            return *this;
        }

        Vec2& operator*= (uint64_t p)
        {
            m_x *= p;
            m_y *= p;
            return *this;
        }

        Vec2& operator*= (const Vec2& v)
        {
            m_x *= v.GetX();
            m_y *= v.GetY();
            return *this;
        }

        Vec2 operator* (float p) const
        {
            Vec2 ret = (*this);
            ret *= p;
            return ret;
        }

        Vec2 operator* (int p) const
        {
            Vec2 ret = (*this);
            ret *= p;
            return ret;
        }

        Vec2 operator* (uint64_t p) const
        {
            Vec2 ret = (*this);
            ret *= p;
            return ret;
        }

        Vec2 operator* (const Vec2& other) const
        {
            Vec2 ret = (*this);
            ret *= other;
            return ret;
        }

        Vec2& operator= (const Vec2& other)
        {
            this->Set(other.GetX(), other.GetY());
            return *this;
        }

        template <typename U>
        Vec2<U> Cast() const
        {
            Vec2<U> casted;
            casted.Set(U(m_x), U(m_y));
            return casted;
        }

        static Vec2<T> ZeroVec()
        {
            return Vec2<T>(T(0), T(0));
        }

        T SquaredModulus()
        {
            return abs(m_x) + abs(m_y);
        }

    private:
        T m_x, m_y;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
    {
        os << "(" << v.GetX() << "," << v.GetY() << ")";
        return os;
    }

    typedef Vec2<int> Vec2i;
    typedef Vec2<float> Vec2f;
    typedef Vec2<size_t> Vec2sz;


    template <typename T>
    T distance(const Vec2<T>& a, const Vec2<T>& b)
    {
        return sqrt(distanceSquared(a, b));
    }

    template <typename T>
    T distanceSquared(const Vec2<T>& a, const Vec2<T>& b)
    {
        double dx = double(a.GetX()) - double(b.GetX());
        double dy = double(a.GetY()) - double(b.GetY());
        return dx * dx + dy * dy;
    }

    template <typename T>
    T distancef(const Vec2<T>& a, const Vec2<T>& b)
    {
        float dx = float(a.GetX()) - float(b.GetX());
        float dy = float(a.GetY()) - float(b.GetY());
        return sqrtf(dx * dx + dy * dy);
    }

    template <typename T>
    T manhattan_distance(const Vec2<T>& a, const Vec2<T>& b)
    {
        auto diff = b - a;
        auto dx = abs(diff.GetX());
        auto dy = abs(diff.GetY());
        return dx + dy;
    }

    template <typename T>
    Vec2<T> ortho_to_iso(const Vec2<T>& ortho)
    {
        int x, y;
        x = ortho.GetX();
        y = ortho.GetY();
        return Vec2i(x - y, (x + y) / 2);
    }

    template <typename T>
    Vec2<T> iso_to_ortho(const Vec2<T>& iso)
    {
        int x, y;
        x = iso.GetX();
        y = iso.GetY();
        return Vec2<T>(2 * y + x, 2 * y - x);
    }

    float lerp(float a, float b, float t);

    template <typename T>
    Vec2<T> lerp(const Vec2<T>& v0, const Vec2<T>& v1, float t)
    {
        return Vec2<T>(lerp(v0.GetX(), v1.GetX(), t), lerp(v0.GetY(), v1.GetY(), t));
    }

    template <typename T>
    class Range : public Vec2<T>
    {
    public:
        T GetMin()
        {
            return Vec2<T>::GetX();
        }

        T GetMax()
        {
            return Vec2<T>::GetY();
        }

        void SetMin(T new_min)
        {
            SetX(new_min);
        }

        void GetMax(T new_max)
        {
            SetY(new_max);
        }

    };

    template <typename T> int sign(T val) {
        return (T(0) < val) - (val < T(0));
    }

}

