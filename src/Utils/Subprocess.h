#pragma once
#include "Toucan.h"
#include <string>

namespace Toucan
{
class Subprocess
{
  public:
    struct Options
    {
        std::string WorkingDirectory;
    };

    struct Result
    {
        int ExitCode;
        std::vector<uint8> Output;
    };

  public:
    static Result Run(
        const std::string &Cmd, const std::vector<const std::string> &Args = {}, const Options &opts = Options());
};
} // namespace Toucan