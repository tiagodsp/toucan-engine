#pragma once

#include "Renderer/Buffer.h"

namespace Toucan
{
class BgfxVertexBuffer : public VertexBuffer
{
  uint16 m_Handle;
  
  public:
    virtual void Bind();
    virtual void Unbind();
    virtual void SetData(void *Data, uint32 Size);
};

class BgfxIndexBuffer : public IndexBuffer
{
  uint16 m_Handle;
  
  public:
    virtual void Bind();
    virtual void Unbind();
    virtual void SetData(void *Data, uint32 Size);
};
}; // namespace Toucan