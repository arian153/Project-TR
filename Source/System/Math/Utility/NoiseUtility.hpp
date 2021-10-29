#pragma once
#include "../../Core/Utility/CoreDef.hpp"
#include "../Algebra/Vector3.hpp"

namespace GAM400
{
    class PerlinNoise
    {
    public:
        explicit PerlinNoise(U32 seed = 142356);
        ~PerlinNoise();

        Real Noise(const Vector3& p, Vector3& derivative, int smooth_level = 2, bool b_random = true) const;
        void SetSeed(U32 seed);
    private:
        void GeneratePermutation();
        U8   RandomPermutationHash(int x, int y, int z) const;
        U8   OriginPermutationHash(int x, int y, int z) const;
        Real GradientDotV(U8 permutation, Real x, Real y, Real z) const;

    public:
        static const U32 TABLE_SIZE = 256;
        static const U32 SIZE_MASK  = TABLE_SIZE - 1;

    private:
        U32     m_seed = 0;
        Vector3 m_gradients[TABLE_SIZE];
        U32     m_permutation_table[TABLE_SIZE * 2];
    };
}
