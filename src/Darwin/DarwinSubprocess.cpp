#include "DarwinSubprocess.h"
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

namespace Toucan
{
Subprocess::Result DarwinSubprocess::Run(
    const std::string &Cmd, const std::vector<const std::string> &Args, const Subprocess::Options &opts)
{
    int pid = 0;
    int status = 0;
    std::vector<uint8> output;
    std::vector<uint8> error;

    // get current dir as file descriptor
    int cwd = open(".", O_RDONLY);
    if (cwd == -1)
    {
        CORE_LOGF("Failed to open current directory: {}", strerror(errno));
        return {-1, {}};
    }

    // change to working directory
    if (opts.WorkingDirectory.size() > 0)
    {
        if (chdir(opts.WorkingDirectory.c_str()) == -1)
        {
            CORE_LOGF("Failed to change to working directory: {}", strerror(errno));
            return {-1, {}};
        }
    }

    // build command string
    std::string cmd = Cmd;
    for (auto &arg : Args)
    {
        cmd += " " + arg;
    }

    FILE *p = popen(Cmd.c_str(), "r");
    if (p == nullptr)
    {
        CORE_LOGF("Failed to open process: {}", Cmd);
        return Subprocess::Result{-1, {}};
    }
    uint8 buff[1024];
    while (fgets((char *)buff, sizeof(buff), p) != NULL)
    {
        output.insert(output.end(), buff, buff + strlen((char *)buff));
    }
    status = pclose(p);
    fchdir(cwd);
    close(cwd);
    if (status == -1)
    {
        CORE_LOGF("Failed to close process: {}", Cmd);
        return Subprocess::Result{-1, {}};
    }
    return Subprocess::Result{status, output};
}
} // namespace Toucan