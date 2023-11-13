#pragma once
#include <initializer_list>
#include <cmath>
#include "kos_engine/defs.hpp"

#include "cos_graphics/graphics.h"
#include "cos_graphics/log.h"

template<unsigned int N>
class KEVector
{
public:
    static constexpr unsigned int SIZE = N;
    static constexpr unsigned int DIM = N;

    union{
        float data[SIZE];
        struct{
            float x, y;
        };
    };

public:

    KEVector() noexcept
    {}

    KEVector(const float* data, unsigned int size)
    {
        if (size != SIZE)
            throw std::invalid_argument("Size of the data is not equal to the size of the matrix");
        for (unsigned int i = 0; i < size; ++i)
        {
            this->data[i] = data[i];
        }
    }

    KEVector(const std::initializer_list<float>& list)
    {
        if (list.size() != SIZE)
            throw std::invalid_argument("Size of the data is not equal to the size of the matrix");
        unsigned int i = 0;
        for (auto iter = list.begin(); iter != list.end(); ++iter)
        {
            data[i] = *iter;
            ++i;
        }
    }

    KEVector(float p_x, float p_y)
        : x(p_x), y(p_y)
    {}
    
    explicit KE_FORCE_INLINE operator float*() noexcept
    {
        return data;
    }

    explicit KE_FORCE_INLINE operator const float*() const noexcept
    {
        return data;
    }

    KE_FORCE_INLINE float& operator[](int i) noexcept
    {
        return data[i];
    }

    KE_FORCE_INLINE float operator[](int i) const noexcept
    {
        return data[i];
    }

    KE_FORCE_INLINE float Length() const noexcept
    {
        float result = 0;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result += data[i] * data[i];
        }
        return sqrt(result);
    }

    KE_FORCE_INLINE KEVector<2> Normalized() const noexcept
    {
        float length = Length();
        if (length == 0)
            return *this;
        return *this / length;
    }

    KE_FORCE_INLINE operator CGVector2() const noexcept
    {
        return CGConstructVector2(x, y);
    }

    KE_FORCE_INLINE KEVector<N> operator+(const KEVector<N>& p_other) const noexcept
    {
        KEVector<N> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result[i] = data[i] + p_other[i];
        }
        return result;
    }

    KE_FORCE_INLINE KEVector<N>& operator +=(const KEVector<N>& p_other) noexcept
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            data[i] += p_other[i];
        }
        return *this;
    }

    KE_FORCE_INLINE KEVector<N> operator-(const KEVector<N>& p_other) const noexcept
    {
        KEVector<N> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result[i] = data[i] - p_other[i];
        }
        return result;
    }

    KE_FORCE_INLINE KEVector<N>& operator -=(const KEVector<N>& p_other) noexcept
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            data[i] -= p_other[i];
        }
        return *this;
    }

    KE_FORCE_INLINE KEVector<N> operator*(float p_scaler) const noexcept
    {
        KEVector<N> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result[i] = data[i] * p_scaler;
        }
        return result;
    }

    KE_FORCE_INLINE KEVector<N>& operator*=(float p_scaler) noexcept
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            data[i] *= p_scaler;
        }
        return *this;
    }

    KE_FORCE_INLINE bool operator ==(KEVector<N> other) noexcept
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            if (data[i] != other[i])
                return false;
        }
        return true;
    }

    KE_FORCE_INLINE bool operator !=(KEVector<N> other) noexcept
    {
        return !(*this == other);
    }

    KE_FORCE_INLINE operator KEString() const noexcept
    {
        KEString result = CGSTR("KEVector<");
        result += KE_TO_STRING(SIZE);
        result += CGSTR(">(");
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result += KE_TO_STRING(data[i]);
            if (i != SIZE - 1)
                result += CGSTR(", ");
        }
        result += CGSTR(")");
        return result;
    }
};

using KEVector2 = KEVector<2>;

template<unsigned int N>
KE_FORCE_INLINE float KEDot(const KEVector<N>& vec_1, const KEVector<N>& vec_2) noexcept
{
    float result = 0;
    for (unsigned int i = 0; i < N; ++i)
    {
        result += vec_1[i] * vec_2[i];
    }
    return result;
}

KE_FORCE_INLINE float KECross(const KEVector2& vec_1, const KEVector2& vec_2) noexcept
{
    return vec_1[1] * vec_2[0] - vec_1[0] * vec_2[1];
}

KE_FORCE_INLINE KEVector<3> KECross(const KEVector<3>& vec_1, const KEVector<3>& vec_2) noexcept
{
    return KEVector<3>({
        vec_1[2] * vec_2[1] - vec_1[1] * vec_2[2],
        vec_1[0] * vec_2[2] - vec_1[2] * vec_2[0],
        vec_1[1] * vec_2[0] - vec_1[0] * vec_2[1]
    });
}