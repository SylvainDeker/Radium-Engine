#ifndef MESHCONVERTER_H
#define MESHCONVERTER_H

#include <Core/Geometry/TopologicalTriMesh/TopologicalMesh.hpp>
#include <Core/Geometry/TriangleMesh.hpp>

namespace Ra {
namespace Core {

//! Adapter class to convert between Core::Mesh and Core::TopologicalMesh
//! \todo take into account texture coordinates and normals more robustly.
class RA_CORE_API MeshConverter {
  public:
    static void convert( TopologicalMesh& in, TriangleMesh& out );
    static void convert( const TriangleMesh& in, TopologicalMesh& out );
};
} // namespace Core
} // namespace Ra

#endif // MESHCONVERTER_H