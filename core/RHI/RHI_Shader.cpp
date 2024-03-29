#include "RHI_Shader.h"

#include "Utils/Path.h"

#include "RHI/bgfx/Bgfx_Shader.h"
#include "fmt/format.h"
#include <memory>

namespace Toucan
{

Map<String, Ref<ShaderLibrary>> ShaderLibrary::s_ShaderLibraries = {};

Ref<RHI_Shader> RHI_Shader::Create(const String &Name, const String &FragmentFilepath, const String &VertexFilepath)
{
    return std::make_shared<Bgfx_Shader>(Name, FragmentFilepath, VertexFilepath);
}

ShaderLibrary::ShaderLibrary() {}

ShaderLibrary::~ShaderLibrary() {}

void ShaderLibrary::Load(const String &name)
{
    String fragmentFileName = fmt::format("fs_{}.sc", name);
    String vertexFileName = fmt::format("vs_{}.sc", name);
    m_Shaders[name] = RHI_Shader::Create(
        name, Path::Join(Path::ShaderDir(), fragmentFileName), Path::Join(Path::ShaderDir(), vertexFileName));
}

Ref<RHI_Shader> ShaderLibrary::GetShader(const String &name)
{
    return m_Shaders[name];
}

Ref<ShaderLibrary> ShaderLibrary::Create(const String &name)
{
    // Check if the library already exists
    if(s_ShaderLibraries.find(name) != s_ShaderLibraries.end())
    {
        // Return the existing library
        return s_ShaderLibraries[name];
    }
    
    // Create a new library
    Ref<ShaderLibrary> shaderLibrary = std::make_shared<ShaderLibrary>();
    s_ShaderLibraries[name] = shaderLibrary;
    return shaderLibrary;
}

Ref<ShaderLibrary> ShaderLibrary::GetLibrary(const String &name)
{
    return s_ShaderLibraries[name];
}
} // namespace Toucan