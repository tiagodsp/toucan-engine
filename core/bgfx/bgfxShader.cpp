#include "bgfxShader.h"
#include "CoreTypes.h"
#include "Log.h"
#include "Utils/FileManager.h"
#include "Utils/Path.h"
#include "Utils/Subprocess.h"
#include "fmt/core.h"
#include "bgfx/bgfx.h"
#include <cstdlib>
#include <vector>

namespace Toucan
{
BgfxShader::BgfxShader(const String &fragmentFilepath, const String &vertexFilepath)
    : m_FragmentFilepath(fragmentFilepath), m_VertexFilepath(vertexFilepath)
{
    Invalidate();
    Compile();
}
BgfxShader::BgfxShader(const String &name, const String &fragmentFilepath, const String &vertexFilepath)
    : m_FragmentFilepath(fragmentFilepath), m_VertexFilepath(vertexFilepath), m_Name(name)
{
    Invalidate();
    Compile();
}
BgfxShader::~BgfxShader() {}

void BgfxShader::Invalidate() {}

void BgfxShader::Bind() {}
void BgfxShader::Unbind() {}

bool BgfxShader::Compile()
{
    LOGI(BgfxShader, "Compiling shader: {}", m_Name);

    String profile;
    switch (GraphicsAPI::Get()->GetAPIName())
    {
    case GraphicsAPI::EAPIName::API_OpenGL:
        profile = "440";
        break;
    case GraphicsAPI::EAPIName::API_Direct3D11:
        profile = "s_5_0";
        break;
    case GraphicsAPI::EAPIName::API_Direct3D12:
        profile = "s_5_0";
        break;
    case GraphicsAPI::EAPIName::API_Vulkan:
        profile = "spirv";
        break;
    case GraphicsAPI::EAPIName::API_Metal:
        profile = "metal";
        break;
    default:
        ASSERT_MSG(false, "Unknown Graphics API");
        return false;
    }

    // Compile fragment shader
    {
        LOGI(BgfxShader, "Compiling fragment shader: {}", m_FragmentFilepath);
        auto result = Subprocess::Run(
            "./3rdparty/bgfx/tools/shaderc",
            {"--type",
             "f",
             "--platform",
             "osx",
             "--profile",
             profile,
             "-i",
             Path::Join(Path::ShaderDir(), "common"),
             "-f",
             Path::Join(m_FragmentFilepath),
             "-o",
             Path::Join(m_FragmentFilepath + ".bin")});
        if (result.ExitCode != 0)
        {
            LOGE(BgfxShader, "Failed to compile fragment shader: {}\n{}", m_FragmentFilepath, result.Output.data());
            ASSERT_MSG(false, "Failed to compile fragment shader.");
            return false;
        }
    }

    // Compile vertex shader
    {
        LOGI(BgfxShader, "Compiling vertex shader: {}", m_VertexFilepath);
        auto result = Subprocess::Run(
            "./3rdparty/bgfx/tools/shaderc",
            {"--type",
             "v",
             "--platform",
             "osx",
             "--profile",
             profile,
             "-i",
             Path::Join(Path::ShaderDir(), "common"),
             "-f",
             Path::Join(m_VertexFilepath),
             "-o",
             Path::Join(m_VertexFilepath + ".bin")});
        if (result.ExitCode != 0)
        {
            LOGE(BgfxShader, "Failed to compile vertex shader: {}\n{}", m_VertexFilepath, result.Output.data());
            ASSERT_MSG(false, "Failed to compile vertex shader.");
            return false;
        }
    }

    // Load compiled shaders
    {
        LOGI(BgfxShader, "Loading compiled shaders");
        // Get binary data from file ------------
        auto fragmentFile = FileManager::Get()->OpenRead(Path::Join(m_FragmentFilepath + ".bin"));
        m_FragmentShaderBinaryData.resize(fragmentFile->Size());
        fragmentFile->ReadAll(m_FragmentShaderBinaryData.data());
        // m_FragmentShaderBinaryData[m_FragmentShaderBinaryData.size() - 1] = '\0';
        delete fragmentFile;

        auto vertexFile = FileManager::Get()->OpenRead(Path::Join(m_VertexFilepath + ".bin"));
        m_VertexShaderBinaryData.resize(vertexFile->Size());
        vertexFile->ReadAll(m_VertexShaderBinaryData.data());
        // m_VertexShaderBinaryData[m_VertexShaderBinaryData.size() - 1] = '\0';
        delete vertexFile;

        // Create fragment shader ---------------
        const bgfx::Memory* m_FragmentShaderBinaryMemory = bgfx::alloc(m_FragmentShaderBinaryData.size());
        memcpy(m_FragmentShaderBinaryMemory->data, m_FragmentShaderBinaryData.data(), m_FragmentShaderBinaryData.size());

        m_FragmentShaderHandle.reset(new bgfx::ShaderHandle);
        *m_FragmentShaderHandle = bgfx::createShader(m_FragmentShaderBinaryMemory);

        // Create vertex shader -----------------
        const bgfx::Memory* m_VertexShaderBinaryMemory = bgfx::alloc(m_VertexShaderBinaryData.size());
        memcpy(m_VertexShaderBinaryMemory->data, m_VertexShaderBinaryData.data(), m_VertexShaderBinaryData.size());

        m_VertexShaderHandle.reset(new bgfx::ShaderHandle);
        *m_VertexShaderHandle = bgfx::createShader(m_VertexShaderBinaryMemory);

        // Create program -----------------------
        m_Program = (bgfx::ProgramHandle*) malloc(sizeof(bgfx::ProgramHandle));
        *m_Program = bgfx::createProgram(*m_VertexShaderHandle, *m_FragmentShaderHandle, true);
    }

    LOGI(BgfxShader, "Shader compiled successfully: {}", m_Name);

    return true;
}
} // namespace Toucan