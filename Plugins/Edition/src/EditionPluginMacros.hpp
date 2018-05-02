#ifndef EDITIONPLUGINMACROS_HPP_
#define EDITIONPLUGINMACROS_HPP_

#include <Core/CoreMacros.hpp>

/// Defines the correct macro to export dll symbols.
#if defined Edition_EXPORTS
#    define EDITION_PLUGIN_API DLL_EXPORT
#else
#    define EDITION_PLUGIN_API DLL_IMPORT
#endif

#endif // EDITIONPLUGINMACROS_HPP_
