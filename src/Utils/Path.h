#pragma once
#include "Toucan.h"
#include <initializer_list>
#include <string>
#include <string_view>
#include <tuple>

namespace Toucan
{
class Path
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