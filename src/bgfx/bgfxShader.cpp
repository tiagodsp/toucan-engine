#include "bgfxShader.h"
#include "Utils/FileManager.h"

namespace Toucan
{
BgfxShader::BgfxShader(const String &filepath) : m_FilePath(filepath)
{
    Invalidate();
    Compile();
}
BgfxShader::BgfxShader(const String &name, const String &filepath) : m_FilePath(filepath), m_Name(name)
{
    Invalidate();
    Compile();
}
BgfxShader::~BgfxShader() {}

void BgfxShader::Invalidate()
{
    m_Source.clear();
}

void BgfxShader::Bind() {}
void BgfxShader::Unbind() {}

void BgfxShader::Compile()
{
    auto sourceFileHandle = FileManager::Get()->OpenRead(m_FilePath);
    if (sourceFileHandle == nullptr)
    {
        CORE_LOGF("Failed to open shader source file: {}", m_FilePath);
        return;
    }

    int64 sizeInBytes = FileManager::Get()->FileSize(m_FilePath);
    std::vector<uint8> sourceData(sizeInBytes);
    sourceFileHandle->Read(sourceData.data(), sizeInBytes);
    delete sourceFileHandle;
    
}
} // namespace Toucan