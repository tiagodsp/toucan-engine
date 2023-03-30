#include "ImGuiLayer.h"
#include "bgfx/bgfxImGuiLayer.h"

namespace Toucan
{
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){};

Ref<ImGuiLayer> ImGuiLayer::Create()
{
    return std::make_shared<BgfxImGuiLayer>();
}
} // namespace Toucan