#pragma once

#include "Renderer/Buffer.h"

namespace Toucan
{
class CORE_LOCAL BgfxVertexBuffer : public VertexBuffer
{
  uint16 m_Handle;
  
  public:
    virtual void Bind();
    virtual void Unbind();
    virtual void SetData(void *Data, uint32 Size);
};

class CORE_LOCAL BgfxIndexBuffer : public IndexBuffer
{
  uint16 m_Handle;
  
  public:
    virtual void Bind();
    virtual void Unbind();
    virtual void SetData(void *Data, uint32 Size);
};
}; // namespace Toucan