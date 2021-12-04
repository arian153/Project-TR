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
#include "../../GraphicsAPI.hpp"
#include IncludeNormalVertexAPI
#include "../../../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class Vector2;
    class Vector3;

    class NormalVertexCommon : public NormalVertexAPI
    {
    public:
        NormalVertexCommon();
        NormalVertexCommon(Real px, Real py, Real pz);
        NormalVertexCommon(Real px, Real py, Real pz, Real nx, Real ny, Real nz);
        NormalVertexCommon(Real px, Real py, Real pz, Real nx, Real ny, Real nz, Real tx, Real ty, Real tz);
        explicit NormalVertexCommon(const Vector3& p);
        NormalVertexCommon(const Vector3& p, const Vector3& n);
        NormalVertexCommon(const Vector3& p, const Vector3& n, const Vector3& t);
        NormalVertexCommon(const Vector3& p, const Vector3& n, const Vector3& t, const Vector3& b);

        Vector3 GetPosition() const;
        Vector3 GetNormal() const;
        Vector3 GetTangent() const;

        void SetPosition(const Vector3& p);
        void SetNormal(const Vector3& n);
        void SetTangent(const Vector3& t);

        void CalculateBinormal();
        void CalculateTangentAndBinormal();

    public:
    };
}
