#ifndef RADIUMENGINE_SHADERCONFIGURATION_HPP
#define RADIUMENGINE_SHADERCONFIGURATION_HPP

#include <list>
#include <string>
#include <set>

#include <Core/CoreMacros.hpp>

namespace Ra
{
    namespace Engine
    {

        struct ShaderType
        {
            RA_API std::string getShaderTypeString ( uint type );
        };

        class RA_API ShaderConfiguration
        {
        public:
            enum ShaderType
            {
                VERT_SHADER = 1 << 0,
                FRAG_SHADER = 1 << 1,
                GEOM_SHADER = 1 << 2,
                TESC_SHADER = 1 << 3,
                TESE_SHADER = 1 << 4,
                COMP_SHADER = 1 << 5,
                TESS_SET = TESC_SHADER | TESE_SHADER, // 0x18

                DEFAULT_SHADER_PROGRAM = VERT_SHADER | FRAG_SHADER, // 0x3
                DEFAULT_SHADER_PROGRAM_W_GEOM = DEFAULT_SHADER_PROGRAM | GEOM_SHADER, // 0x7
                COMPLETE_SHADER_PROGRAM = DEFAULT_SHADER_PROGRAM_W_GEOM | TESS_SET // 0x1F
            };

        public:
            ShaderConfiguration() = default;
            explicit ShaderConfiguration ( const std::string& name,
                                           const std::string& path,
                                           const ShaderType& type = DEFAULT_SHADER_PROGRAM );

            void addProperty ( const std::string& prop );
            void addProperties ( const std::list<std::string>& props );
            void removeProperty ( const std::string& prop );

            bool operator< ( const ShaderConfiguration& other ) const;

            void setName ( const std::string& name );
            void setPath ( const std::string& path );
            void setType ( const ShaderType&  type );

            std::string getName() const;
            std::string getPath() const;
            std::string getFullName() const;
            ShaderType getType() const;
            std::set<std::string> getProperties() const;

        private:
            std::string m_name;
            std::string m_shaderPath;
            ShaderType m_type;
            std::set<std::string> m_properties;
        };

    } // namespace Engine
} // namespace Ra

#endif // RADIUMENGINE_SHADERCONFIGURATION_HPP
