#pragma once
#include "Toucan.h"
#include "Utils/Subprocess.h"

namespace Toucan
{
class DarwinSubprocess
{
  public:
    static Subprocess::Result Run(
        const std::string &Cmd, const std::vector<const std::string> &Args = {}, const Subprocess::Options &opts = {});
};
} // namespace Toucan