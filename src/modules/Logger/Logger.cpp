#include "Logger.h"

Logger::Logger() {
    try {
        if(_LIBMCV_DEV_MODE) {
            console = spdlog::stdout_color_mt("console");
            console->info("Welcome to LibMCV!");
            console->info("Library for Modern Computer Vision");
            console->info("The Debug Mode is on");
        }
        else {
            console = spdlog::rotating_logger_mt("file_logger", "logs/libmcv.log", 1024 * 1024 * 5, 3);
            console->info("Welcome to LibMCV!");
            console->info("Library for Modern Computer Vision");
            console->info("The Debug Mode is off");
            console->info("Logfile will be stored at logs/libmcv.log");
        }
    }
    catch (const spdlog::spdlog_ex & ex) {
        std::cout<<"Logger Failed to Initialize: "<< ex.what() << std::endl; 
    }
}

std::shared_ptr<spdlog::logger> Logger::getLogger() {
    if(console == NULL ) {
        new Logger();
    }
    return console;
}
