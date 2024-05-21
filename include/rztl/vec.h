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

		static float Distance(const Vec2<T>& a, const Vec2<T>& b)
		{
			float dx = ((float)a.GetX()) - ((float)b.GetX());
			float dy = ((float)a.GetY()) - ((float)b.GetY());
			return sqrtf(dx * dx + dy * dy);
		}

		void x(T newx)
		{
			m_x = newx;
		}

		void y(T newy)
		{
			m_y = newy;
		}

		T x() const
		{
			return m_x;
		}

		T y() const
		{
			return m_y;
		}

		void set(T x, T y)
		{
			m_x = x; m_y = y;
		}

		void set(const Vec2<T>& other)
		{
			m_x = other.GetX(); m_y = other.GetY();
		}

		void translate(const Vec2<T>& other)
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

		Vec2& operator*= (const Vec2& v)
		{
			m_x *= v.GetX();
			m_y *= v.GetY();
			return *this;
		}

		Vec2 operator* (float p)
		{
			Vec2 ret = (*this);
			ret *= p;
			return ret;
		}

		Vec2 operator* (const Vec2& other)
		{
			Vec2 ret = (*this);
			ret *= other;
			return ret;
		}

		Vec2& operator= (const Vec2& other)
		{
			this->set(other.GetX(), other.GetY());
			return *this;
		}

		template <typename U>
		Vec2<U> cast() const
		{
			Vec2<U> casted;
			casted.set(U(m_x), U(m_y));
			return casted;
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
		double dx = double(a.GetX()) - double(b.GetX());
		double dy = double(a.GetY()) - double(b.GetY());
		return sqrt(dx * dx + dy * dy);
	}

	template <typename T>
	T distancef(const Vec2<T>& a, const Vec2<T>& b)
	{
		float dx = float(a.GetX()) - float(b.GetX());
		float dy = float(a.GetY()) - float(b.GetY());
		return sqrtf(dx * dx + dy * dy);
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

	float lerp(float v0, float v1, float t);

	template <typename T>
	Vec2<T> lerp(const Vec2<T>& v0, const Vec2<T>& v1, float t)
	{
		return Vec2<T>(lerp(v0.GetX(), v1.GetX(), t), lerp(v0.GetY(), v1.GetY(), t));
	}

	template <typename T>
	class Range : public Vec2<T>
	{
	public:
		T min()
		{
			return Vec2<T>::x();
		}

		T max()
		{
			return Vec2<T>::y();
		}

		void min(T new_min)
		{
			x(new_min);
		}

		void max(T new_max)
		{
			y(new_max);
		}

	};

}

