#pragma once

#include "../Services/Log/Logger.hpp"
#include <spdlog/spdlog.h>

#define XN_INTERNAL_TRACE(...) spdlog::trace(__VA_ARGS__)
#define XN_INTERNAL_INFO(...) spdlog::info(__VA_ARGS__)
#define XN_INTERNAL_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define XN_INTERNAL_WARN(...) spdlog::warn(__VA_ARGS__)
#define XN_INTERNAL_ERROR(...) spdlog::error(__VA_ARGS__)
#define XN_INTERNAL_CRITICAL(...) spdlog::critical(__VA_ARGS__)