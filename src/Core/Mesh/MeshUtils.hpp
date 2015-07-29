﻿#ifndef RADIUMENGINE_MESHUTILS_HPP
#define RADIUMENGINE_MESHUTILS_HPP

#include <vector>
#include <array>

#include <Core/Mesh/TriangleMesh.hpp>

namespace Ra { namespace Core
{
    /// Functions to operate on a TriangleMesh
    namespace MeshUtils
    {
        //
        // Geometry/Topology  utils
        //

        /// Fills the given array with the vertices of a given triangle.
        inline void getTriangleVertices(const TriangleMesh& mesh, TriangleIdx triIdx,
                                        std::array<Vector3, 3>& verticesOut);

        /// Returns the area of a given triangle.
        inline float getTriangleArea(const TriangleMesh& mesh, TriangleIdx triIdx);

        /// Computes the normal of a given triangle.
        inline Vector3 getTriangleNormal(const TriangleMesh& mesh, TriangleIdx triIdx);

        inline Aabb getAabb(const TriangleMesh& mesh);

        /// Automatically compute normals for each vertex by averaging connected triangle normals.
        void getAutoNormals(TriangleMesh& mesh, VectorArray<Vector3>& normalsOut);

        /// Finds the duplicate vertices in a mesh, returning an array indicating for each vertex where to find the
        /// first occurrence.
        bool findDuplicates(const TriangleMesh& mesh, std::vector<VertexIdx>& duplicatesMap);

        //
        // Primitive construction
        //
        /// Create a 2D quad mesh given half extents, centered on the origin with x axis as normal
        TriangleMesh makeXNormalQuad(const Vector2& halfExts = Vector2(0.5, 0.5));

        /// Create a 2D quad mesh given half extents, centered on the origin with y axis as normal
        TriangleMesh makeYNormalQuad(const Vector2& halfExts = Vector2(0.5, 0.5));

        /// Create a 2D quad mesh given half extents, centered on the origin with z axis as normal
        TriangleMesh makeZNormalQuad(const Vector2& halfExts = Vector2(0.5, 0.5));

        /// Create an axis-aligned cubic mesh with the given half extents, centered on the origin.
        TriangleMesh makeBox(const Vector3& halfExts = Vector3(0.5, 0.5, 0.5));

        /// Create an axis-aligned cubic mesh
        TriangleMesh makeBox(const Aabb& aabb);

        /// Create a parametric spheric mesh of given radius. Template parameters set the resolution.
        template<uint U = 16, uint V = U>
        TriangleMesh makeParametricSphere(Scalar radius = 1.0);

        /// Create a spheric mesh by subdivision of an icosaherdon.
        TriangleMesh makeGeodesicSphere(Scalar radius =1.f, uint numSubdiv = 3);

        //
        // Checks
        //

        /// Check that the mesh is well built, asserting when it is not.
        /// only compiles to something when in debug mode.
        void checkConsistency(const TriangleMesh& mesh);
    }
}}

#include <Core/Mesh/MeshUtils.inl>

#endif //RADIUMENGINE_MESHUTILS_HPP

