/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "PascalTriangle.hpp"

#include "../../Core/Utility/CoreDef.hpp"

namespace GAM400
{
    PascalTriangle::PascalTriangle(int max)
        : max(max)
    {
        pascal_triangle_table = std::vector<std::vector<int>>(max, std::vector<int>(max, -1));
        CalculateTriangle();
    }

    PascalTriangle::~PascalTriangle()
    {
    }

    void PascalTriangle::CalculateTriangle()
    {
        for (I64 i = 0; i < max; i++)
        {
            for (I64 j = 0; j <= i; j++)
            {
                if (i == j || j == 0)
                    pascal_triangle_table[i][j] = 1;
                else
                    pascal_triangle_table[i][j] = pascal_triangle_table[i - 1][j - 1] + pascal_triangle_table[i - 1][j];
            }
        }
    }

    int PascalTriangle::BinomialCoefficient(int d, int i)
    {
        return pascal_triangle_table[d][i];
    }
}
