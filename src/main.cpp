#include "Toucan.h"

int main(int argc, char *argv[])
{
    Toucan::Log::Init();
    Toucan::App app("My app");
    app.Run();
}