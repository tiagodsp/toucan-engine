#pragma once
#include "Toucan.h"

namespace Toucan
{

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T> using Ref = std::shared_ptr<T>;
using HANDLE = void *;

using String = std::string;

} // namespace Toucan
