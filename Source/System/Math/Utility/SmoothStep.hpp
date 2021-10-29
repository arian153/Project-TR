#pragma once
#include "MathDef.hpp"

namespace GAM400
{
    class SmoothStep
    {
    public:

        static Real Smooth(Real w, int smooth_level);
        static Real SmoothDerivative(Real w, int smooth_level);

        static Real Linear(Real w);
        static Real Cubic(Real w);
        static Real Quintic(Real w);
        static Real Septic(Real w);

        static Real LinearDerivative(Real w);
        static Real CubicDerivative(Real w);
        static Real QuinticDerivative(Real w);
        static Real SepticDerivative(Real w);
    };
}
