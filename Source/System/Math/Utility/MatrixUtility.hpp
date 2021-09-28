#pragma once
#include "MathDef.hpp"

namespace GAM400
{
    class AxisRadian;
    class Quaternion;
    class Matrix44;
    class Matrix33;
    class EulerAngle;
    class Vector3;
    class Vector4;

    namespace Math
    {
        namespace Matrix44
        {
            //rotation
            GAM400::Matrix44 Rotation(const Quaternion& quaternion);
            GAM400::Matrix44 Rotation(const GAM400::Matrix33& rotation_matrix);
            GAM400::Matrix44 Rotation(const EulerAngle& euler_angle);
            GAM400::Matrix44 Rotation(const AxisRadian& axis_radian);

            //principle rotation
            GAM400::Matrix44 RotationX(Real radian);
            GAM400::Matrix44 RotationY(Real radian);
            GAM400::Matrix44 RotationZ(Real radian);

            //scale
            GAM400::Matrix44 Scale(const GAM400::Vector4& scale);
            GAM400::Matrix44 Scale(const GAM400::Vector3& scale, Real w = 1.0f);

            //translation
            GAM400::Matrix44 Translation(const GAM400::Vector3& translation);

            //Matrix Generation
            GAM400::Matrix44 AffineTransformation
            (
                const GAM400::Vector3& scale,
                const GAM400::Vector3& origin,
                const Quaternion&       rotation,
                const GAM400::Vector3& translation
            );

            GAM400::Matrix44 PerspectiveMatrix
            (
                Real screen_aspect,
                Real field_of_view,
                Real far_plane,
                Real near_plane
            );

            GAM400::Matrix44 OrthoGraphicMatrix
            (
                size_t client_width,
                size_t client_height,
                Real   far_plane,
                Real   near_plane
            );

            GAM400::Matrix44 OrthoGraphicCenterMatrix
            (
                Real right,
                Real left,
                Real top,
                Real bottom,
                Real far_plane,
                Real near_plane
            );

            GAM400::Matrix44 LookAt
            (
                const GAM400::Vector3& eye_position,
                const GAM400::Vector3& focus_position,
                const GAM400::Vector3& up_direction
            );

            GAM400::Matrix44 LookTo
            (
                const GAM400::Vector3& eye_position,
                const GAM400::Vector3& eye_direction,
                const GAM400::Vector3& up_direction
            );
        }

        namespace Matrix33
        {
            //rotation
            GAM400::Matrix33 Rotation(const Quaternion& quaternion);
            GAM400::Matrix33 Rotation(const GAM400::Matrix44& rotation_matrix);
            GAM400::Matrix33 Rotation(const EulerAngle& euler_angle);
            GAM400::Matrix33 Rotation(const AxisRadian& axis_radian);

            //principle rotation
            GAM400::Matrix33 RotationX(Real radian);
            GAM400::Matrix33 RotationY(Real radian);
            GAM400::Matrix33 RotationZ(Real radian);

            //scale
            GAM400::Matrix33 Scale(const GAM400::Vector3& scale);
        }
    }
}
