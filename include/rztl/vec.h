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
			float dx = ((float)a.x()) - ((float)b.x());
			float dy = ((float)a.y()) - ((float)b.y());
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
			m_x = other.x(); m_y = other.y();
		}

		void translate(const Vec2<T>& other)
		{
			m_x += other.x();
			m_y += other.y();
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
			m_x += other.x();
			m_y += other.y();
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
			m_x *= v.x();
			m_y *= v.y();
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
			this->set(other.x(), other.y());
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
		os << "(" << v.x() << "," << v.y() << ")";
		return os;
	}

	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<size_t> Vec2sz;

	namespace allig {
		namespace math {

			template <typename T>
			T distance(const Vec2<T>& a, const Vec2<T>& b)
			{
				double dx = double(a.x()) - double(b.x());
				double dy = double(a.y()) - double(b.y());
				return sqrt(dx * dx + dy * dy);
			}

			template <typename T>
			T distancef(const Vec2<T>& a, const Vec2<T>& b)
			{
				float dx = float(a.x()) - float(b.x());
				float dy = float(a.y()) - float(b.y());
				return sqrtf(dx * dx + dy * dy);
			}

		}
	}

	template <typename T>
	Vec2<T> ortho_to_iso(const Vec2<T>& ortho)
	{
		int x, y;
		x = ortho.x();
		y = ortho.y();
		return Vec2i(x - y, (x + y) / 2);
	}

	template <typename T>
	Vec2<T> iso_to_ortho(const Vec2<T>& iso)
	{
		int x, y;
		x = iso.x();
		y = iso.y();
		return Vec2<T>(2 * y + x, 2 * y - x);
	}

	float lerp(float v0, float v1, float t);

	template <typename T>
	Vec2<T> lerp(const Vec2<T>& v0, const Vec2<T>& v1, float t)
	{
		return Vec2<T>(lerp(v0.x(), v1.x(), t), lerp(v0.y(), v1.y(), t));
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

