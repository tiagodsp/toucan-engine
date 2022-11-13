#pragma once
#include "Toucan.h"

namespace Toucan
{
class GraphicsAPI
{
  public:
    enum EAPIName
    {
        API_None,
        API_OpenGL,
        API_Direct3D11,
        API_Direct3D12,
        API_Vulkan,
        API_Metal,
    };

  private:
    EAPIName m_APIName;

  public:
    /** Get the graphics API. */
    static Ref<GraphicsAPI> Get();
    
    /** Initialize the graphics API. */
    virtual void Init() = 0;
    /** Shutdown the graphics API. */
    virtual void Shutdown() = 0;
    /** Begin a new scene. */
    virtual void BeginScene() = 0;
    /** End the current scene. */
    virtual void EndScene() = 0;
    /** Set the clear color. */
    virtual void SetClearColor(const LinearColor &color) = 0;
    /** Clear the screen. */
    virtual void Clear() = 0;
    /** Get the name of the graphics API. */
    const EAPIName GetAPIName() const { return m_APIName; }

  protected:
    /** Set graphics api name. Only called by subclasses. */
    void SetAPIName(EAPIName apiName) { m_APIName = apiName; }
};

} // namespace Toucan