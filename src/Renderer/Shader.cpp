#include "Shader.h"
#include "bgfx/bgfxShader.h"
#include "fmt/format.h"
#include <memory>

namespace Toucan
{
Ref<Shader> Shader::Create(const String &Name, const String &Filepath)
{
    return std::make_shared<BgfxShader>(Name, Filepath);
}

ShaderLibrary::ShaderLibrary() {}

ShaderLibrary::~ShaderLibrary() {}

void ShaderLibrary::Load(const String &name)
{
    m_Shaders[name] = Shader::Create(name, fmt::format("{}/{}.hlsl", "Assets/Shaders", name));
}

Ref<Shader> ShaderLibrary::GetShader(const String &name)
{
    return m_Shaders[name];
}
} // namespace Toucan