/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#pragma once
#include "../../Math/Algebra/Matrix44.hpp"

namespace GAM400
{
    class MatrixData
    {
    public:
        MatrixData()
        {
        }

        MatrixData(const Matrix44& m, const Matrix44& v, const Matrix44& p)
            : model(m), view(v), projection(p)
        {
        }

        MatrixData(const Matrix44& v, const Matrix44& p)
            : view(v), projection(p)
        {
            model.SetIdentity();
        }

        ~MatrixData()
        {
        }

        Matrix44 GetMVPMatrix() const
        {
            return model * view * projection;
        }

    public:
        Matrix44 model;
        Matrix44 view;
        Matrix44 projection;
    };
}
