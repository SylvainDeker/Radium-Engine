#ifndef FANCYMESHPLUGIN_FANCYMESHLOADER_HPP
#define FANCYMESHPLUGIN_FANCYMESHLOADER_HPP

#include <string>
#include <vector>

#include <Plugins/FancyMeshPlugin/FancyMeshLoadingData.hpp>

typedef std::vector<FancyMeshPlugin::FancyComponentData,
        Ra::Core::AlignedAllocator<FancyMeshPlugin::FancyComponentData, 16>> DataVector;

namespace FancyMeshPlugin
{

    namespace FancyMeshLoader
    {
        RA_API DataVector loadFile( const std::string& name );

    } // namespace FancyMeshLoader;

} // namespace FancyMeshPlugin

#endif // FANCYMESHPLUGIN_FANCYMESHLOADER_HPP
