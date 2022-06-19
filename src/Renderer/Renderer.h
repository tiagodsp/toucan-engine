#pragma once
#include "Toucan.h"

namespace Toucan
{
class Renderer
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
};
} // namespace Toucan