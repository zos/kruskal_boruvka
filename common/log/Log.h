#pragma once

#include <iostream>

#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define RESET_COLOR "\033[0m"

#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_ERROR 1

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG(msg) std::cout << msg << std::endl;
#else
#define LOG(msg)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOGE(msg) std::cout << RED_COLOR << msg << RESET_COLOR << std::endl;
#else
#define LOGE(msg)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOGI(msg) std::cout << GREEN_COLOR << msg << RESET_COLOR << std::endl;
#else
#define LOGI(msg)
#endif
