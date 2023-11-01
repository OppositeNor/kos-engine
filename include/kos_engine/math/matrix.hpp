#pragma once
#include "cos_graphics/graphics.h"
#include "cos_graphics/log.h"
#include "kos_engine/math/vector.hpp"
#include <cmath>
#include <initializer_list>

template<unsigned int N>
class KEMatrix{

public:
    static constexpr int SIZE = N * N;
    static constexpr int DIM = N;


private:
    union {
        float data[SIZE];
        float data_m[N][N];
    };
    static float matrix_buffer[SIZE];
    inline static bool is_identity_initialized = false;

public:
    /**
     * @brief Construct a new KEMatrix object
     */
    KEMatrix() noexcept
    {}

    /**
     * @brief Construct a new KEMatrix object
     * 
     * @param data The data of the KEMatrix (row-major order)
     * @param size The size of the data
     */
    KEMatrix(const float* data, int size)
    {
        if (size != SIZE)
            throw std::invalid_argument("Size of the data is not equal to the size of the matrix");
        for (int i = 0; i < size; ++i)
        {
            this->data[i] = data[i];
        }
    }

    /**
     * @brief Constructor
     * @param list The list of values in the KEMatrix (row-major order)
     */
    KEMatrix(const std::initializer_list<float>& list)
    {
        if (list.size() != SIZE)
            throw std::invalid_argument("Size of the data is not equal to the size of the matrix");
        int i = 0;
        for (auto iter = list.begin(); iter != list.end(); ++iter)
        {
            data[i] = *iter;
            ++i;
        }
    }

    /**
     * @brief Constructor
     * @param list The list of values in the KEMatrix (row-major order)
     */
    KEMatrix(const std::initializer_list<std::initializer_list<float>>& list)
    {
        if (list.size() != N)
            throw std::invalid_argument("The size of the initializer list is not equal to the size of the KEMatrix");
        int i = 0;
        int j = 0;
        for (auto iter = list.begin(); iter != list.end(); ++iter)
        {
            if (iter->size() != N)
                throw std::invalid_argument("The size of the initializer list is not equal to the size of the KEMatrix");
            j = 0;
            for (auto iter2 = iter->begin(); iter2 != iter->end(); ++iter2)
            {
                data_m[i][j] = *iter2;
                ++j;
            }
            ++i;
        }
    }

    /**
     * @brief Constructor
     * @param list The list of values in the KEMatrix (row-major order)
     */
    constexpr float* operator[](int i) noexcept
    {
        return data_m[i];
    }

    /**
     * @brief Constructor
     * @param list The list of values in the KEMatrix (row-major order)
     */
    constexpr const float* operator[](int i) const noexcept
    {
        return data_m[i];
    }

    /**
     * @brief Get the array of this KEMatrix in column-major order
     * 
     * @return float* The KEMatrix in column-major order
     */
    inline const float* GetCColumnMajorMatrix() const noexcept
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                matrix_buffer[i * N + j] = data_m[j][i];
            }
        }
        return matrix_buffer;
    }

    inline const float* GetCMatrix() const noexcept
    {
        for (int i = 0; i < SIZE; ++i)
        {
            matrix_buffer[i] = data[i];
        }
        return matrix_buffer;
    }

    inline KEMatrix<N> operator*(const KEMatrix<N>& p_other) const noexcept
    {
        KEMatrix<N> result;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                result[i][j] = 0;
                for (int k = 0; k < N; ++k)
                {
                    result[i][j] += data_m[i][k] * p_other[k][j];
                }
            }
        }
        return result;
    }

    inline KEMatrix<N> operator*(float p_scalar) const noexcept
    {
        KEMatrix<N> result;
        for (int i = 0; i < SIZE; ++i)
        {
            result.data[i] = data[i] * p_scalar;
        }
        return result;
    }

    inline KEMatrix<N>& operator*=(float p_scalar) noexcept
    {
        for (int i = 0; i < SIZE; ++i)
        {
            data[i] *= p_scalar;
        }
        return *this;
    }

    inline KEMatrix<N>& operator*=(const KEMatrix<N>& p_other) noexcept
    {
        *this = *this * p_other;
        return *this;
    }

    inline KEMatrix<N> operator+(const KEMatrix<N>& p_other) noexcept
    {
        KEMatrix<N> result;
        for (int i = 0; i < SIZE; ++i)
        {
            result.data[i] = data[i] + p_other.data[i];
        }
        return result;
    }

    inline KEMatrix<N>& operator+=(const KEMatrix<N>& p_other) noexcept
    {
        for (int i = 0; i < SIZE; ++i)
        {
            data[i] += p_other.data[i];
        }
        return *this;
    }

    inline KEVector<N> operator* (const KEVector<N>& p_vector) const noexcept
    {
        KEVector<N> result;
        for (int i = 0; i < N; ++i)
        {
            result[i] = 0;
            for (int j = 0; j < N; ++j)
            {
                result[i] += data_m[i][j] * p_vector[j];
            }
        }
        return result;
    }

    inline KEVector<N-1> operator* (const KEVector<N-1>& p_vector) const noexcept
    {
        constexpr int result_dim = N - 1;
        KEVector<result_dim> result;
        for (int i = 0; i < result_dim; ++i)
        {
            result[i] = data_m[i][N-1];
            for (int j = 0; j < result_dim; ++j)
            {
                result[i] += data_m[i][j] * p_vector[j];
            }
        }
        return result;
    }

    inline bool operator== (const KEMatrix<N> p_mat)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (data[i] != p_mat.data[i])
                return false;
        }
        return true;
    }

    inline operator KEString()
    {
        KEString result = CGSTR("KEMatrix<");
        result += KE_TO_STRING(DIM);
        result += CGSTR(">(");
        for (unsigned int i = 0; i < DIM; ++i)
        {
            result += CGSTR("{");
            for (unsigned int j = 0; j < DIM; ++j)
            {
                result += KE_TO_STRING(data_m[i][j]);
                if (i < DIM - 1 || j < DIM - 1)
                    result += CGSTR(", ");
            }
            result += CGSTR("}");
        }
        result += CGSTR(")");
        return result;
    }
};


namespace KEMat3
{
    using KEMat3 = KEMatrix<3>;

    /**
     * @brief Get the position matrix
     * 
     * @param position The position to get the matrix out from
     * @return KEMat3 The position matrix
     */
    KEMat3 GetPositionMatrix(const KEVector2& p_position) noexcept;

    /**
     * @brief Get the rotation matrix
     * 
     * @param rotation The rotation to get the matrix out from
     * @return KEMat3 The rotation matrix
     */
    KEMat3 GetRotationMatrix(float p_rotation) noexcept;

    /**
     * @brief Get the inverse rotation matrix
     * 
     * @param p_rotation The rotation to get the matrix out from
     * @return KEMat3 The inverse rotation matrix
     */
    KEMat3 GetInvRoationMatrix(float p_rotation) noexcept;

    /**
     * @brief Get the scale matrix
     * 
     * @param scale The scale to get the matrix out from
     * @return KEMat3 The scale matrix
     */
    KEMat3 GetScaleMatrix(const KEVector2& p_scale) noexcept;
}

inline static CGVector2 operator*(const KEMat3::KEMat3& p_m, const CGVector2& p_v) noexcept
{
    return (CGVector2){p_m[0][0] * p_v.x + p_m[0][1] * p_v.y + p_m[0][2],
                        p_m[1][0] * p_v.x + p_m[1][1] * p_v.y + p_m[1][2]};
}