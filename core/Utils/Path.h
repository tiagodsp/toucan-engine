#pragma once
#include "CoreTypes.h"

namespace Toucan
{
class CORE_API Path
{
  public:
    static const String ExecutableDir();
    static const String DataDir();
    static const String ShaderDir();

    template <typename... Args>
    static const String Join(Args &&...paths)
    {
        return _Join({std::forward<Args>(paths)...});
    }

  private:
    static const String _Join(const std::vector<String> &paths);
};
} // namespace Toucan