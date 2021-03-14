/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: TODO
Creation date: TODO
-----------------------------------------------------------------*/

namespace math
{
	[[nodiscard]] constexpr vec2 operator+(const vec2 left, const vec2 right) noexcept
	{
		vec2 v;
		v.x = left.x + right.x;
		v.y = left.y + right.y;
		return v;
	}

	constexpr vec2& vec2::operator+=(const vec2 right) noexcept
	{
		*this = *this + right;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator-(vec2 left, vec2 right) noexcept
	{
		const double new_x = left.x - right.x;
		const double new_y = left.y - right.y;
		return vec2{ new_x,new_y };
	}

	constexpr vec2& vec2::operator-=(vec2 right) noexcept
	{
		*this = *this - right;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator-(vec2 right) noexcept
	{
		return vec2{ -right.x,-right.y };
	}

	[[nodiscard]] constexpr vec2 operator*(double scale, vec2 right) noexcept
	{
		const double new_x = scale * right.x;
		const double new_y = scale * right.y;
		return vec2{ new_x,new_y };
	}

	[[nodiscard]] constexpr vec2 operator*(vec2 left, double scale) noexcept
	{
		const double new_x = scale * left.x;
		const double new_y = scale * left.y;
		return vec2{ new_x,new_y };
	}

	constexpr vec2& vec2::operator*=(double scale) noexcept
	{
		*this = *this * scale;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator/(vec2 left, double scale) noexcept
	{
		const double new_x = left.x / scale;
		const double new_y = left.y / scale;
		return vec2{ new_x,new_y };
	}

	constexpr vec2& vec2::operator/=(double scale) noexcept
	{
		*this = *this / scale;
		return *this;
	}

	[[nodiscard]] constexpr bool operator==(vec2 left, vec2 right) noexcept
	{
		if (is_equal(left.x, right.x) && is_equal(left.y, right.y))
			return true;

		return false;
	}

	[[nodiscard]] constexpr bool operator!=(vec2 left, vec2 right) noexcept
	{
		if (is_equal(left.x, right.x) && is_equal(left.y, right.y))
			return false;

		return true;
	}

	[[nodiscard]] constexpr double vec2::LengthSquared() noexcept
	{
		return x * x + y * y;
	}

	[[nodiscard]]inline vec2& vec2::Normalize() noexcept
	{
		double len = sqrt(x * x + y * y);
		*this = *this / len;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	[[nodiscard]] constexpr ivec2 operator+(ivec2 left, ivec2 right) noexcept
	{
		const int new_x = left.x + right.x;
		const int new_y = left.y + right.y;
		return ivec2{ new_x,new_y };
	}

	constexpr ivec2& ivec2::operator+=(ivec2 right) noexcept
	{
		*this = *this + right;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator-(ivec2 left, ivec2 right) noexcept
	{
		const int new_x = left.x - right.x;
		const int new_y = left.y - right.y;
		return ivec2{ new_x,new_y };
	}

	constexpr ivec2& ivec2::operator-=(ivec2 right) noexcept
	{
		*this = *this - right;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator-(ivec2 right) noexcept
	{
		return ivec2{ -right.x,-right.y };
	}

	[[nodiscard]] constexpr ivec2 operator*(int scale, ivec2 right) noexcept
	{
		const int new_x = scale * right.x;
		const int new_y = scale * right.y;
		return ivec2{ new_x,new_y };
	}

	[[nodiscard]] constexpr ivec2 operator*(ivec2 left, int scale) noexcept
	{
		const int new_x = scale * left.x;
		const int new_y = scale * left.y;
		return ivec2{ new_x,new_y };
	}

	constexpr ivec2& ivec2::operator*=(int scale) noexcept
	{
		*this = *this * scale;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator/(ivec2 left, int scale) noexcept
	{
		const int new_x = left.x / scale;
		const int new_y = left.y / scale;
		return ivec2{ new_x,new_y };
	}

	constexpr ivec2& ivec2::operator/=(int scale) noexcept
	{
		*this = *this / scale;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator*(double scale, ivec2 right) noexcept
	{
		const double new_x = scale * right.x;
		const double new_y = scale * right.y;
		return vec2{ new_x,new_y };
	}
	[[nodiscard]] constexpr vec2 operator*(ivec2 left, double scale) noexcept
	{
		const double new_x = scale * left.x;
		const double new_y = scale * left.y;
		return vec2{ new_x,new_y };
	}
	[[nodiscard]] constexpr vec2 operator/(ivec2 left, double scale) noexcept
	{
		const double new_x = left.x / scale;
		const double new_y = left.y / scale;
		return vec2{ new_x,new_y };
	}

	[[nodiscard]] constexpr bool operator==(ivec2 left, ivec2 right) noexcept
	{
		if (is_equal(left.x, right.x) && is_equal(left.y, right.y))
			return true;

		return false;
	}

	[[nodiscard]] constexpr bool operator!=(ivec2 left, ivec2 right) noexcept
	{
		if (is_equal(left.x, right.x) && is_equal(left.y, right.y))
			return false;

		return true;
	}

	[[nodiscard]] constexpr ivec2::operator vec2() noexcept
	{
		return vec2{ static_cast<double>(this->x),static_cast<double>(this->y) };
	}
}
