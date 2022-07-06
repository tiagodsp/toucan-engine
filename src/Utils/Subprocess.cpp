#include "Subprocess.h"

#ifdef BUILD_DARWIN
#include "Darwin/DarwinSubprocess.h"
#endif

namespace Toucan
{
Subprocess::Result Subprocess::Run(
    const std::string &Cmd, const std::vector<const std::string> &Args, const Options &opts)
{
#ifdef BUILD_DARWIN
    return DarwinSubprocess::Run(Cmd, Args, opts);
#else
    return Result{-1, ""};
#endif
}
} // namespace Toucan