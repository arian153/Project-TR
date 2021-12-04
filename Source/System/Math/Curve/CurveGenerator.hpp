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
#include "Curve.hpp"

namespace GAM400
{
    class CurveGenerator
    {
    public:

        static Curve GenerateBezierCurve(const std::vector<Vector3>& control_points, int sample = 1000);
        static Curve GeneratePolynomialCurve(const std::vector<Vector3>& control_points, int sample = 100);
        static Curve GenerateSplineCurve(const std::vector<Vector3>& control_points, int sample = 100);

    private:

        static double TruncatedCubicFunction(int idx, double t);
        static double TruncatedCubicDoublePrime(int idx, double t);
        static void   Inverse(std::vector<std::vector<double>> matrix, std::vector<std::vector<double>>& result);
    };
}
