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
#include <map>

#include "../../Math/Math.hpp"
#include <vector>

#include "../Common/Buffer2/ConstantBufferData.hpp"
#include "../DataType/Color.hpp"
#include "../DataType/MatrixData.hpp"
#include "../Common/Vertex/ColorVertexCommon.hpp"
#include "../DataType/Frustum.hpp"

namespace GAM400
{
    class InstanceBufferCommon;
    class ConstantBufferCommon;
    class VertexBufferCommon;
    class IndexBufferCommon;
    class ShaderProgramCommon;
    class Curve;
    class MatrixManager;
    class MeshBufferCommon;
    class RendererCommon;
    class Camera;
    class ColorShaderCommon;

    enum class eRenderingMode
    {
        Dot,
        Line,
        Face
    };

    struct InstancingSubMesh
    {
        VertexBufferCommon* vertex_buffer = nullptr;
        IndexBufferCommon* index_buffer = nullptr;
        InstanceBufferCommon* instance_buffer = nullptr;
        std::vector<InstanceBufferData> instances;
        U32                             max_count = 0;
    };

    class PrimitiveRenderer
    {
    public:
        explicit PrimitiveRenderer(RendererCommon* renderer);
        ~PrimitiveRenderer();
        void DrawPrimitive(Primitive* primitive, eRenderingMode mode, Color color = Color());
        void DrawPrimitive(const Primitive& primitive, eRenderingMode mode, Color color = Color());

        //Draw Direct Primitives
        void DrawPoint(const Vector3& point, Color color = Color());
        void DrawSegment(const Vector3& start, const Vector3& end, Color color = Color());
        void DrawTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, eRenderingMode mode, Color color = Color());
        void DrawRectangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, eRenderingMode mode, Color color = Color());
        void DrawTetrahedron(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, eRenderingMode mode, Color color = Color());
        void DrawBox(const Vector3& position, const Quaternion& orientation, const Vector3& scale, eRenderingMode mode, Color color = Color());
        void DrawRay(const Ray& ray, Color color = Color());
        void DrawArrow(const Vector3& start, const Vector3& end, Color color = Color());

        void DrawCurveLine(const Curve& curve, Color color = Color());
        void DrawDashedLineSegment(const Vector3& start, const Vector3& end, Real length, Color color = Color());

        void Initialize(ShaderProgramCommon* color_shader);
        void Render(ConstantBufferCommon* matrix_buffer) const;
        void RenderInstancing(ShaderProgramCommon* color_shader, ConstantBufferCommon* matrix_buffer) const;
        void Shutdown();
        void Clear();

        void UpdateViewMatrix(const Matrix44& view_matrix);
        void UpdateProjectionMatrix(const Matrix44& projection_matrix);
        void UpdateFrustum(const Frustum& frustum);

        void   PushVertex(const Vector3& pos, eRenderingMode mode, const Color& color = Color());
        void   PushIndex(I32 index, eRenderingMode mode);
        void   PushLineIndices(I32 a, I32 b);
        void   PushFaceIndices(I32 a, I32 b, I32 c);
        void   ReserveVertices(size_t adding_count, eRenderingMode mode);
        void   ReserveIndices(size_t adding_count, eRenderingMode mode);
        size_t VerticesSize(eRenderingMode mode) const;
        size_t IndicesSize(eRenderingMode mode) const;

        void DrawPrimitiveInstancing(const Primitive& primitive, const Matrix44& transform, eRenderingMode mode, Color color = Color());
        void DrawPrimitiveInstancing(const Primitive& primitive, const Transform& transform, eRenderingMode mode, Color color = Color());
        void DrawPrimitiveInstancing(const Primitive& primitive, const Quaternion& orientation, const Vector3& position, eRenderingMode mode, Color color = Color());


    private:
        MatrixData           m_mvp_data;
        RendererCommon*      m_renderer = nullptr;
        Frustum              m_frustum;
        ShaderProgramCommon* m_shader = nullptr;

        U32 m_stride = 0;

        std::vector<ColorVertexCommon> m_dot_vertices;
        std::vector<U32>               m_dot_indices;
        VertexBufferCommon*            m_dot_vertex_buffer = nullptr;
        IndexBufferCommon*             m_dot_index_buffer  = nullptr;

        std::vector<ColorVertexCommon> m_line_vertices;
        std::vector<U32>               m_line_indices;
        VertexBufferCommon*            m_line_vertex_buffer = nullptr;
        IndexBufferCommon*             m_line_index_buffer  = nullptr;

        std::vector<ColorVertexCommon> m_face_vertices;
        std::vector<U32>               m_face_indices;
        VertexBufferCommon*            m_face_vertex_buffer = nullptr;
        IndexBufferCommon*             m_face_index_buffer  = nullptr;

        //instancing
        std::map<size_t, U32>               m_drawing_sub_ins_meshes;
        std::map<size_t, InstancingSubMesh> m_sub_ins_mesh_table;

    public:
        const int CIRCULAR_VERTICES_COUNT    = 100;
        const int SPHERICAL_SLICE_COUNT      = 14;
        const int SPHERICAL_STACK_COUNT      = 15;
        const int SPHERICAL_VERTICES_COUNT   = 212; //(stack_count - 1) * (slice_count + 1) + 2;
        const int CYLINDRICAL_SLICE_COUNT    = 20;
        const int CYLINDRICAL_STACK_COUNT    = 1;
        const int CYLINDRICAL_VERTICES_COUNT = 42; //(stack_count + 1) * (slice_count + 1)
    };
}
