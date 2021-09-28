#pragma once
#include "../Primitive.hpp"
#include "../../Algebra/Vector2.hpp"


namespace GAM400
{
    class Cone final : public Primitive
    {
    public:
        Cone();
        explicit Cone(const Vector3& position, const Quaternion& orientation, Real radius, Real height);
        ~Cone();

        void Initialize() override;
        void Shutdown() override;

        //Primitive Data
        void SetUnit() override;

        //Minkowski Support - gjk, epa
        Vector3 Support(const Vector3& direction) override;

        //Ray - Primitive Intersection
        bool    TestRayIntersection(const Ray& local_ray, Real& minimum_t, Real& maximum_t) const override;
        Vector3 GetNormal(const Vector3& local_point_on_primitive) override;

        //Draw
        void DrawPrimitive(PrimitiveRenderer* renderer, eRenderingMode mode, const Color& color) const override;

        Vector2 Radius() const;

    public:
        Real radius = 0.5f;
        Real height = 1.0f;
    };
}
