#include "Path.h"
#include "Log.h"
#include <filesystem>
#include <string_view>
#include <utility>

#ifdef BUILD_DARWIN
#include <mach-o/dyld.h>
#endif

namespace fs = std::filesystem;

namespace Toucan
{
const String Path::ExecutableDir()
{
#ifdef BUILD_DARWIN
    char path[PATH_MAX];
    uint32_t size = PATH_MAX;
    _NSGetExecutablePath(path, &size);
    fs::path p(path);
    p = p.parent_path();
    return p.string();
#endif
    ASSERT_MSG(false, "Can't get executable directory on this platform.");
    return "";
}

const String Path::DataDir()
{
    return Path::Join(ExecutableDir(), "data");
}

const String Path::ShaderDir()
{
    return Path::Join(ExecutableDir(), "data", "shaders");
}

const String Path::_Join(const std::vector<String> &paths)
{
    fs::path result_path;
    for (auto &path : paths)
    {
        result_path /= path;
    }
    return result_path.string();
}

} // namespace Toucan