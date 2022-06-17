#pragma once
#include "Toucan.h"

namespace Toucan
{

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T> using Ref = std::shared_ptr<T>;
using HANDLE = void *;

using String = std::string;
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Vector = Vector3;
using Vector2Int = glm::ivec2;
using Vector3Int = glm::ivec3;
using Vector4Int = glm::ivec4;
using Matrix4 = glm::mat4;
using Quaternion = glm::quat;
using Color = glm::vec4;
using Rect = glm::vec4;
using Size = glm::vec2;
using Point = glm::vec2;
using Range = glm::vec2;

} // namespace Toucan
