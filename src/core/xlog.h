﻿ /*******************************************************************
  * Copyright (c) 2021-2022 偕臧  All rights reserved.
  *
  * Author: XMuli <xmulitech@gmail.com>
  * GitHub: https://github.com/XMuli
  * Blog:   https://xmuli.tech
  *
  * Date:   2022.03.12
  * Description: 使用 spdlog 来生成日志
  ******************************************************************/
#ifndef XLOG_H
#define XLOG_H

#ifdef Q_OS_WIN
    #define SPDLOG_WCHAR_TO_UTF8_SUPPORT  // 需要定义在 spdlog 之前，以支持 wchar_t 的输出
#endif

#include <QStandardPaths>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/rotating_file_sink.h"


class XLog
{
public:
    static XLog* instance() {
        static XLog instance;
        return &instance;
    }

    std::shared_ptr<spdlog::logger> getLogger() {
        return m_logger;
    }

    void setLevel(const std::string val) { m_level = val; }

private:
    XLog() {
        m_logger = spdlog::rotating_logger_mt("fileLogger", QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first().toStdString() + "/picshot_debug.log", 1024 * 1024 * 20, 10, true);

        // 默认类型：[2022-03-19 22:15:15.885] [fileLogger] [info] [screenshot.cpp:941]
        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        //m_logger->set_pattern("%Y-%m-%d %H:%M:%S %t %l [%@] [%!] %v");
        m_logger->set_pattern("%Y-%m-%d %H:%M:%S %t %l [%!] %v");

        
        setLevel("debug");
        if (m_level == "trace") {
            m_logger->set_level(spdlog::level::trace);
            m_logger->flush_on(spdlog::level::trace);
        } else if (m_level == "debug") {
            m_logger->set_level(spdlog::level::debug);
            m_logger->flush_on(spdlog::level::debug);
        } else if (m_level == "info") {
            m_logger->set_level(spdlog::level::info);
            m_logger->flush_on(spdlog::level::info);
        } else if (m_level == "warn") {
            m_logger->set_level(spdlog::level::warn);
            m_logger->flush_on(spdlog::level::warn);
        } else if (m_level == "error") {
            m_logger->set_level(spdlog::level::err);
            m_logger->flush_on(spdlog::level::err);
        } else if (m_level == "critical") {
            m_logger->set_level(spdlog::level::critical);
            m_logger->flush_on(spdlog::level::critical);
        } else if (m_level == "off") {
            m_logger->set_level(spdlog::level::off);
            m_logger->flush_on(spdlog::level::off);
        } else {
            m_logger->set_level(spdlog::level::n_levels);
        }
    }

    ~XLog() {
        spdlog::drop_all(); // must do this
    }

    XLog(XLog&&) = delete;
    XLog(const XLog&) = delete;
    void operator= (const XLog&) = delete;

private:
    std::string m_level;
    std::shared_ptr<spdlog::logger> m_logger;
};

// use embedded macro to support file and line number
#define XLOG_TRACE(...)    SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::trace, __VA_ARGS__)
#define XLOG_DEBUG(...)    SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define XLOG_INFO(...)     SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::info, __VA_ARGS__)
#define XLOG_WARN(...)     SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define XLOG_ERROR(...)    SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::err, __VA_ARGS__)
#define XLOG_CRITICAL(...) SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::critical, __VA_ARGS__)
#define XLOG_OFF(...)      SPDLOG_LOGGER_CALL(XLog::instance()->getLogger().get(), spdlog::level::off, __VA_ARGS__)


#endif // XLOG_H
