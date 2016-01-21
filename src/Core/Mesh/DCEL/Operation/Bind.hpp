#ifndef RADIUMENGINE_BIND_OPERATION_DEFINITION_HPP
#define RADIUMENGINE_BIND_OPERATION_DEFINITION_HPP

#include <Core/Mesh/DCEL/Definition.hpp>

namespace Ra {
namespace Core {

void   bind( const Vertex_ptr&   v  );
void unbind( const Vertex_ptr&   v  );

void   bind( const HalfEdge_ptr& he );
void unbind( const HalfEdge_ptr& he );

void   bind( const FullEdge_ptr& fe );
void unbind( const FullEdge_ptr& fe );

void   bind( const Face_ptr&     f  );
void unbind( const Face_ptr&     f  );

} // namespace Core
} // namespace Ra

#endif // RADIUMENGINE_BIND_OPERATION_DEFINITION_HPP