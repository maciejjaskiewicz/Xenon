#pragma once

#include "Application.hpp"
#include "../Services/Log/Logger.hpp"
#include <spdlog/spdlog.h>

#define XN_ENG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define XN_ENG_INFO(...) spdlog::info(__VA_ARGS__)
#define XN_ENG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define XN_ENG_WARN(...) spdlog::warn(__VA_ARGS__)
#define XN_ENG_ERROR(...) spdlog::error(__VA_ARGS__)
#define XN_ENG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#define XN_TRACE(...) { Application::Services::AppLogger::empty() ? spdlog::trace(__VA_ARGS__) :\
    spdlog::get(Application::Services::AppLogger::ref().name())->trace(__VA_ARGS__); }
#define XN_INFO(...) { Application::Services::AppLogger::empty() ? spdlog::info(__VA_ARGS__) :\
    spdlog::get(Application::Services::AppLogger::ref().name())->info(__VA_ARGS__); }
#define XN_DEBUG(...) { Application::Services::AppLogger::empty() ? spdlog::debug(__VA_ARGS__) :\
    spdlog::get(Application::Services::AppLogger::ref().name())->debug(__VA_ARGS__); }
#define XN_WARN(...) { Application::Services::AppLogger::empty() ? spdlog::warn(__VA_ARGS__) :\
    spdlog::get(Application::Services::AppLogger::ref().name())->warn(__VA_ARGS__); }
#define XN_ERROR(...) { Application::Services::AppLogger::empty() ? spdlog::error(__VA_ARGS__) :\
    spdlog::get(Application::Services::AppLogger::ref().name())->error(__VA_ARGS__); }
#define XN_CRITICAL(...) { Application::Services::AppLogger::empty() ? spdlog::critical(__VA_ARGS__) :\
    spdlog::get(Application::Services::AppLogger::ref().name())->critical(__VA_ARGS__); }
