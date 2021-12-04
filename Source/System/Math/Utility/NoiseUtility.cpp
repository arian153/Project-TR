/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "NoiseUtility.hpp"
#include <random>
#include <functional>

#include "SmoothStep.hpp"

namespace
{
    GAM400::U32 perlin_permutation[] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36,
        103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0,
        26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56,
        87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
        77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
        46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
        187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109,
        198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
        255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
        170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
        172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112,
        104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
        241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106,
        157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205,
        93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
    };
}

namespace GAM400
{
    PerlinNoise::PerlinNoise(U32 seed)
        : m_seed(seed), m_permutation_table{}
    {
        GeneratePermutation();
    }

    PerlinNoise::~PerlinNoise()
    {
    }

    Real PerlinNoise::Noise(const Vector3& p, Vector3& derivative, int smooth_level, bool b_random) const
    {
        int xi0 = ((int)floorf(p.x)) & SIZE_MASK;
        int yi0 = ((int)floorf(p.y)) & SIZE_MASK;
        int zi0 = ((int)floorf(p.z)) & SIZE_MASK;

        int xi1 = (xi0 + 1) & SIZE_MASK;
        int yi1 = (yi0 + 1) & SIZE_MASK;
        int zi1 = (zi0 + 1) & SIZE_MASK;

        Vector3 t(p.x - (Real)((int)floorf(p.x)), p.y - (Real)((int)floorf(p.y)), p.z - (Real)((int)floorf(p.z)));

        Real u = SmoothStep::Smooth(t.x, smooth_level);
        Real v = SmoothStep::Smooth(t.y, smooth_level);
        Real w = SmoothStep::Smooth(t.z, smooth_level);

        // generate vectors going from the grid points to p
        Vector3 p0 = t;
        Vector3 p1(t.x - 1.0f, t.y - 1.0f, t.z - 1.0f);
        Real    gradients[8] = {0.0f};

        if (b_random)
        {
            gradients[0] = GradientDotV(RandomPermutationHash(xi0, yi0, zi0), p0.x, p0.y, p0.z);
            gradients[1] = GradientDotV(RandomPermutationHash(xi1, yi0, zi0), p1.x, p0.y, p0.z);
            gradients[2] = GradientDotV(RandomPermutationHash(xi0, yi1, zi0), p0.x, p1.y, p0.z);
            gradients[3] = GradientDotV(RandomPermutationHash(xi1, yi1, zi0), p1.x, p1.y, p0.z);
            gradients[4] = GradientDotV(RandomPermutationHash(xi0, yi0, zi1), p0.x, p0.y, p1.z);
            gradients[5] = GradientDotV(RandomPermutationHash(xi1, yi0, zi1), p1.x, p0.y, p1.z);
            gradients[6] = GradientDotV(RandomPermutationHash(xi0, yi1, zi1), p0.x, p1.y, p1.z);
            gradients[7] = GradientDotV(RandomPermutationHash(xi1, yi1, zi1), p1.x, p1.y, p1.z);
        }
        else
        {
            gradients[0] = GradientDotV(OriginPermutationHash(xi0, yi0, zi0), p0.x, p0.y, p0.z);
            gradients[1] = GradientDotV(OriginPermutationHash(xi1, yi0, zi0), p1.x, p0.y, p0.z);
            gradients[2] = GradientDotV(OriginPermutationHash(xi0, yi1, zi0), p0.x, p1.y, p0.z);
            gradients[3] = GradientDotV(OriginPermutationHash(xi1, yi1, zi0), p1.x, p1.y, p0.z);
            gradients[4] = GradientDotV(OriginPermutationHash(xi0, yi0, zi1), p0.x, p0.y, p1.z);
            gradients[5] = GradientDotV(OriginPermutationHash(xi1, yi0, zi1), p1.x, p0.y, p1.z);
            gradients[6] = GradientDotV(OriginPermutationHash(xi0, yi1, zi1), p0.x, p1.y, p1.z);
            gradients[7] = GradientDotV(OriginPermutationHash(xi1, yi1, zi1), p1.x, p1.y, p1.z);
        }

        Real du = SmoothStep::SmoothDerivative(t.x, smooth_level);
        Real dv = SmoothStep::SmoothDerivative(t.y, smooth_level);
        Real dw = SmoothStep::SmoothDerivative(t.z, smooth_level);

        Real k[8] = {};

        k[0] = gradients[0];
        k[1] = (gradients[1] - gradients[0]);
        k[2] = (gradients[2] - gradients[0]);
        k[3] = (gradients[4] - gradients[0]);
        k[4] = (gradients[0] + gradients[3] - gradients[1] - gradients[2]);
        k[5] = (gradients[0] + gradients[5] - gradients[1] - gradients[4]);
        k[6] = (gradients[0] + gradients[6] - gradients[2] - gradients[4]);
        k[7] = (gradients[1] + gradients[2] + gradients[4] + gradients[7] - gradients[0] - gradients[3] - gradients[5] - gradients[6]);

        derivative.x = du * (k[1] + k[4] * v + k[5] * w + k[7] * v * w);
        derivative.y = dv * (k[2] + k[4] * u + k[6] * w + k[7] * v * w);
        derivative.z = dw * (k[3] + k[5] * u + k[6] * v + k[7] * v * w);

        return k[0] + k[1] * u + k[2] * v + k[3] * w + k[4] * u * v + k[5] * u * w + k[6] * v * w + k[7] * u * v * w;
    }

    void PerlinNoise::SetSeed(U32 seed)
    {
        m_seed = seed;
        GeneratePermutation();
    }

    void PerlinNoise::GeneratePermutation()
    {
        std::uniform_real_distribution<Real> real_distribution;
        std::uniform_int_distribution<U32>   uint_distribution;

        std::mt19937 twister_engine(m_seed);
        auto         dice_real = std::bind(real_distribution, twister_engine);

        for (U32 i = 0; i < TABLE_SIZE; ++i)
        {
            Real theta = acosf(2 * dice_real() - 1);
            Real phi   = 2 * dice_real() * Math::PI;

            //generate spherical
            Real x                 = cosf(phi) * sinf(theta);
            Real y                 = sinf(phi) * sinf(theta);
            Real z                 = cosf(theta);
            m_gradients[i]         = Vector3(x, y, z);
            m_permutation_table[i] = i;
        }

        auto dice_int = std::bind(uint_distribution, twister_engine);
        // create random permutation table
        for (U32 i = 0; i < TABLE_SIZE; ++i)
        {
            std::swap(m_permutation_table[i], m_permutation_table[dice_int() & SIZE_MASK]);
        }
        // extend the permutation table in the index range [256:512]
        for (U32 i = 0; i < TABLE_SIZE; ++i)
        {
            m_permutation_table[TABLE_SIZE + i] = m_permutation_table[i];
        }
    }

    U8 PerlinNoise::RandomPermutationHash(int x, int y, int z) const
    {
        return (U8)m_permutation_table[m_permutation_table[m_permutation_table[x] + y] + z];
    }

    U8 PerlinNoise::OriginPermutationHash(int x, int y, int z) const
    {
        return (U8)perlin_permutation[perlin_permutation[perlin_permutation[x] + y] + z];
    }

    Real PerlinNoise::GradientDotV(U8 permutation, Real x, Real y, Real z) const
    {
        switch (permutation & 15)
        {
        case 0:
            return x + y; // (1,1,0) 
        case 1:
            return -x + y; // (-1,1,0) 
        case 2:
            return x - y; // (1,-1,0) 
        case 3:
            return -x - y; // (-1,-1,0) 
        case 4:
            return x + z; // (1,0,1) 
        case 5:
            return -x + z; // (-1,0,1) 
        case 6:
            return x - z; // (1,0,-1) 
        case 7:
            return -x - z; // (-1,0,-1) 
        case 8:
            return y + z; // (0,1,1), 
        case 9:
            return -y + z; // (0,-1,1), 
        case 10:
            return y - z; // (0,1,-1), 
        case 11:
            return -y - z; // (0,-1,-1) 
        case 12:
            return y + x; // (1,1,0) 
        case 13:
            return -x + y; // (-1,1,0) 
        case 14:
            return -y + z; // (0,-1,1) 
        case 15:
            return -y - z; // (0,-1,-1) 
        default:
            return 0.0f;
        }
    }
}
