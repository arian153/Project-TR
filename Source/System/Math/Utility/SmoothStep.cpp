#include "SmoothStep.hpp"

namespace GAM400
{
    Real SmoothStep::Smooth(Real w, int smooth_level)
    {
        int level = smooth_level % 4;
        switch (level)
        {
        case 0:
            return Linear(w);
        case 1:
            return Cubic(w);
        case 2:
            return Quintic(w);
        case 3:
            return Septic(w);
        default:
            return Quintic(w);
        }
    }

    Real SmoothStep::SmoothDerivative(Real w, int smooth_level)
    {
        int level = smooth_level % 4;
        switch (level)
        {
        case 0:
            return LinearDerivative(w);
        case 1:
            return CubicDerivative(w);
        case 2:
            return QuinticDerivative(w);
        case 3:
            return SepticDerivative(w);
        default:
            return QuinticDerivative(w);
        }
    }

    Real SmoothStep::Linear(Real w)
    {
        return w;
    }

    Real SmoothStep::Cubic(Real w)
    {
        //-2w^3 + 3w^2
        return w * w * (w * -2.0f + 3.0f);
    }

    Real SmoothStep::Quintic(Real w)
    {
        //6w^5 + -15w^4 + 10w^3
        return w * w * w * (w * (w * 6.0f - 15.0f) + 10.0f);
    }

    Real SmoothStep::Septic(Real w)
    {
        //-20w^7 + 70w^6 -84w^5 + 35w^4
        return w * w * w * w * (w * (w * (w * -20.0f + 70.0f) - 84.0f) + 35.0f);
    }

    Real SmoothStep::LinearDerivative(Real /*w*/)
    {
        return 1.0f;
    }

    Real SmoothStep::CubicDerivative(Real w)
    {
        //-6w^2 + 6w
        return 6.0f * w * (1.0f - w);
    }

    Real SmoothStep::QuinticDerivative(Real w)
    {
        //30w^4 - 60w^3 + 30w^2
        return 30.0f * w * w * (w * (w - 2.0f) + 1.0f);
    }

    Real SmoothStep::SepticDerivative(Real w)
    {
        //-140w^6 + 420w^5 - 420w^4 + 140w^3
        return 140.0f * w * w * w * (w * (w * (-w + 3.0f) - 3.0f) + 1.0f);
    }
}
