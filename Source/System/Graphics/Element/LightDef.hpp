#pragma once

namespace GAM400
{
    enum class eLightType
    {
        AmbientLight,
        DirectionalLight,
        PointLight,
        SpotLight,
        CapsuleLight
    };

    enum class eLightingMethod
    {
        None,
        Forward,
        Deferred
    };
}
