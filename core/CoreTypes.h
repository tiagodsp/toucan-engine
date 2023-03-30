#pragma once
#include "toucanengine.PCH.h"

// primitive types
#ifndef __GNUG__
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
namespace Toucan
{

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T>
using Weak = std::weak_ptr<T>;

template <typename K, typename V>
using Map = std::map<K, V>;

template <typename T>
using Array = std::vector<T>;

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
using LinearColor = glm::vec4;
using Rect = glm::vec4;
using Size = glm::vec2;
using Point = glm::vec2;
using Range = glm::vec2;

} // namespace Toucan
