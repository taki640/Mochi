#pragma once

#include <cstdint>
#include <cassert>

#define MOCHI_ASSERT(cond, message) assert((cond) && message)

namespace Mochi
{
	template<typename Type>
	struct Vector2
	{
		Type X;
		Type Y;

		inline constexpr Vector2() : X(static_cast<Type>(0.0)), Y(static_cast<Type>(0.0)) {}
		inline constexpr Vector2(Type scalar) : X(scalar), Y(scalar) {}
		inline constexpr Vector2(Type x, Type y) : X(x), Y(y) {}
		inline constexpr Vector2(const Vector2& v) : X(v.X), Y(v.Y) {}

		inline constexpr Type& operator[](uint16_t i)
		{
			switch (i)
			{
				case 0: return X;
				case 1: return Y;
				default: MOCHI_ASSERT(false, "Index is out of range"); return X;	// "return X" to suppress warning
			}
		}

		inline constexpr const Type& operator[](uint16_t i) const
		{
			switch (i)
			{
				case 0: return X;
				case 1: return Y;
				default: MOCHI_ASSERT(false, "Index is out of range"); return X;	// "return X" to suppress warning
			}
		}

		inline constexpr Vector2& operator+=(const Vector2& v)
		{
			X += v.X;
			Y += v.Y;
			return *this;
		}

		inline constexpr Vector2& operator-=(const Vector2& v)
		{
			X -= v.X;
			Y -= v.Y;
			return *this;
		}

		inline constexpr Vector2& operator*=(const Vector2& v)
		{
			X *= v.X;
			Y *= v.Y;
			return *this;
		}
		
		inline constexpr Vector2& operator*=(const Type& scalar)
		{
			X *= scalar;
			Y *= scalar;
			return *this;
		}

		inline constexpr Vector2& operator/=(const Vector2& v)
		{
			X /= v.X;
			Y /= v.Y;
			return *this;
		}

		inline constexpr Vector2& operator/=(const Type& scalar)
		{
			X /= scalar;
			Y /= scalar;
			return *this;
		}

		inline constexpr Vector2& operator++()
		{
			X++;
			Y++;
			return *this;
		}

		inline constexpr Vector2& operator--()
		{
			X--;
			Y--;
			return *this;
		}

		inline constexpr Vector2 operator++(int)
		{
			++*this;
			return *this;
		}

		inline constexpr Vector2 operator--(int)
		{
			--*this;
			return *this;
		}
	};

	template<typename Type>
	inline constexpr Vector2<Type> operator+(const Vector2<Type>& v1, const Vector2<Type>& v2)
	{
		return { v1.X + v2.X, v1.Y + v2.Y };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator-(const Vector2<Type>& v1, const Vector2<Type>& v2)
	{
		return { v1.X - v2.X, v1.Y - v2.Y };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator*(const Vector2<Type>& v1, const Vector2<Type>& v2)
	{
		return { v1.X * v2.X, v1.Y * v2.Y };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator*(const Vector2<Type>& v, const Type& scalar)
	{
		return { v.X * scalar, v.Y * scalar };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator*(const Type& scalar, const Vector2<Type>& v)
	{
		return { v.X * scalar, v.Y * scalar };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator/(const Vector2<Type>& v1, const Vector2<Type>& v2)
	{
		return { v1.X / v2.X, v1.Y / v2.Y };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator/(const Vector2<Type>& v, const Type& scalar)
	{
		return { v.X / scalar, v.Y / scalar };
	}

	template<typename Type>
	inline constexpr Vector2<Type> operator/(const Type& scalar, const Vector2<Type>& v)
	{
		return { scalar / v.X, scalar / v.Y };
	}

	template<typename Type>
	inline constexpr bool operator==(const Vector2<Type>& v1, const Vector2<Type>& v2)
	{
		return v1.X == v2.X && v1.Y == v2.Y;
	}

	template<typename Type>
	inline constexpr bool operator!=(const Vector2<Type>& v1, const Vector2<Type>& v2)
	{
		return v1.X != v2.X || v1.Y != v2.Y;
	}
}
