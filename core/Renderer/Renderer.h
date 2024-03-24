#pragma once
#include "CoreTypes.h"
#include "Toucan.h"

namespace Toucan
{
class CORE_API Renderer
{
  public:
    /**
     * @brief Get the instance of the renderer
     * @return Ref<Renderer> 
     */
    static Ref<Renderer> Get();
    
    /**
     * @brief Initialize the renderer
     */
    void Init();
    
    /**
     * @brief Shutdown the renderer
     */
    void Shutdown();
    
    /**
     * @brief Mark the beginning of a new frame drawing
     */
    void Begin();
   
    /**
     * @brief Mark the end of a frame drawing
     */
    void End();

    /**
     * @brief Clear the screen with a color
     * @param color The color to clear the screen with
     */
    void Clear(const LinearColor &color);

    /**
     * @brief Set clear state
     * @param color The color to clear the screen with
     */
     void SetClearState(const LinearColor &color);

     /**
      * @brief Set the viewport size
      * @param Size The size of the viewport
      */
      void SetViewportSize(const Vector2Int &Size);
};
} // namespace Toucan