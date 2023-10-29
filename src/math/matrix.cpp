#include "kos_engine/math/matrix.hpp"

namespace KEMat3
{
    KEMat3 GetPositionMatrix(const KEVector2& p_position) noexcept
    {
        return KEMat3({1.0f, 0.0f, p_position.x,
                    0.0f, 1.0f, p_position.y,
                    0.0f, 0.0f, 1.0f});
    }
    
    KEMat3 GetRotationMatrix(float p_rotation) noexcept
    {
        float sin_theta = sin(p_rotation);
        float cos_theta = cos(p_rotation);
        return KEMat3({cos_theta, -sin_theta, 0.0f,
                    sin_theta, cos_theta, 0.0f,
                    0.0f, 0.0f, 1.0f});
    }

    KEMat3 GetInvRoationMatrix(float p_rotation) noexcept
    {
        float sin_theta = sin(p_rotation);
        float cos_theta = cos(p_rotation);
        return KEMat3({cos_theta, sin_theta, 0.0f,
                    -sin_theta, cos_theta, 0.0f,
                    0.0f, 0.0f, 1.0f});
    }
    
    KEMat3 GetScaleMatrix(const KEVector2& p_scale) noexcept
    {
        return KEMat3({p_scale.x, 0.0f, 0.0f,
                    0.0f, p_scale.y, 0.0f,
                    0.0f, 0.0f, 1.0f});
    }
}