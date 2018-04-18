#ifndef LIGHTPATHPLUGINMACROS_HPP_
#define LIGHTPATHPLUGINMACROS_HPP_

#include <Core/CoreMacros.hpp>

/// Defines the correct macro to export dll symbols.
#if defined LightPath_EXPORTS
#    define LP_PLUGIN_API DLL_EXPORT
#else
#    define LP_PLUGIN_API DLL_IMPORT
#endif

#endif // LIGHTPATHPLUGINMACROS_HPP_
