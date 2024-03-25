#pragma once

namespace Toucan
{

class IRHI_Resource
{
  public:
    virtual void *GetRHIResourceHandle() const { return m_RHI_ResourceHandle; };

  protected:
    void *m_RHI_ResourceHandle;
};

} // namespace Toucan