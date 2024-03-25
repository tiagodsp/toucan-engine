#pragma once

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#elif defined(__clang__)
#define DEBUG_BREAK() __builtin_trap()
#else
#error "Unknown compiler"
#endif

// check debug macro for each compiler type
#if defined(_DEBUG)
#define IS_DEBUG_BUILD true
#elif defined(DEBUG)
#define IS_DEBUG_BUILD true
#elif not defined(NDEBUG)
#define IS_DEBUG_BUILD true
#endif

#ifndef IS_DEBUG_BUILD
#define ASSERT(condition)
#define ASSERT_MSG(condition, message)
#else
#define ASSERT(condition)                                                                                              \
    if (!(condition))                                                                                                  \
    {                                                                                                                  \
        CORE_LOGF("Assertion failed: {}", #condition);                                                                 \
        DEBUG_BREAK();                                                                                                 \
        exit(1);                                                                                                       \
    }

#define ASSERT_MSG(condition, message)                                                                                 \
    if (!(condition))                                                                                                  \
    {                                                                                                                  \
        CORE_LOGF("Assertion failed: {}", message);                                                                    \
        DEBUG_BREAK();                                                                                                 \
        exit(1);                                                                                                       \
    }
#endif