#pragma once

#include <cstdarg>
#include <cstdio>
#include <stdexcept>

#undef assert

#define IR_ASSERT(condition, ...) utils::ir_assert(condition, __VA_ARGS__)

namespace utils {

    const int BUFFER_SIZE = 1024;

    void ir_assert(bool condition, const char *errorMessage, ...) {
        if (condition) {
            return;
        }
        char buffer[BUFFER_SIZE];
        va_list args;
        va_start(args, errorMessage);
        vsprintf(buffer, errorMessage, args);
        va_end(args);
        throw std::runtime_error(buffer);
    }
}
