#pragma once

#include <iostream>
#include <string>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

inline void loggerInit(const std::string& file_path) {
    try {
        auto logger = spdlog::basic_logger_mt("basic_logger", file_path);
        spdlog::set_default_logger(logger);
        spdlog::info("File logger init ended successfully.");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Log init failed: " << ex.what() << std::endl;
    }
}