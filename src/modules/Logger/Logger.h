#ifndef _LIBMCV_MODULES_LOGGER_H_
#define _LIBMCV_MODULES_LOGGER_H_

#ifndef _LIBMCV_DEV_MODE
#define _LIBMCV_DEV_MODE true
#endif

#include <iostream>
#include <memory>
#include "../../../lib/spdlog/spdlog.h"


class Logger {
private:
    static std::shared_ptr<spdlog::logger> console;
    Logger();
public:
    static std::shared_ptr<spdlog::logger> getLogger();
    ~Logger();
};

#endif