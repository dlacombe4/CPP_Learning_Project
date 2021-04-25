#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template<size_t size, typename t>
struct Point
{
    std::array<t, size> values {};

    template<typename... other_ts>
    Point(const t& first, const other_ts&... others)
        :   values {first, static_cast<t>(others)...}
    {}

    t& x() { return values[0]; }
    t x() const { return values[0]; }

    t& y() {
        static_assert(size >= 2);
        return values[1];
    }

    t y() const {
        static_assert(size >= 2);
        return values[1];
    }

    t& z() {
        static_assert(size >= 3);
        return values[2];
    }

    t z() const {
        static_assert(size >= 3);
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                std::plus<t>());
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                std::minus<t>());

        return *this;
    }

    Point& operator*=(const t scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                [scalar](t f){ return f*scalar; } );
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                std::multiplies<>{});
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const t scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator-() const {
        Point result = *this;
        std::transform(result.values.begin(), result.values.end(), result.values.begin(),
                [](const t& value){ return -value; });
        return result;
    }

    t length() const
    {
        return std::sqrt(std::reduce(
                values.begin(),
                values.end(),
                0.f,
                [](t f1, t f2){ return f1+f2*f2;}));
    }

    float distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

using Point2D = Point<2,float>;
using Point3D = Point<3,float>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}