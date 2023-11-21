//
// Created by vnbk on 24/03/2023.
//

#ifndef SELEX_BOOTLOADER_lkv_LOGGER_H
#define SELEX_BOOTLOADER_lkv_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LOG_BUFFER_SIZE 1024

typedef void (*lkv_logger_output_fn_t)(const char*);
typedef enum {
    LOG_LEVEL_ERR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_NUMBER
}LOG_LEVEL;

int32_t lkv_logger_init(lkv_logger_output_fn_t _fn, LOG_LEVEL _level);
int32_t lkv_logger_set_level(LOG_LEVEL _level);
LOG_LEVEL lkv_logger_get_level();

void lkv_logger_show(LOG_LEVEL _level, const char* _tag, const char* _log, ...);

#define LOG_ERR(LOG_TAG, ...)       lkv_logger_show(LOG_LEVEL_ERR,     LOG_TAG,    __VA_ARGS__)
#define LOG_WRN(LOG_TAG, ...)       lkv_logger_show(LOG_LEVEL_WARN,    LOG_TAG,    __VA_ARGS__)
#define LOG_INF(LOG_TAG, ...)       lkv_logger_show(LOG_LEVEL_INFO,    LOG_TAG,    __VA_ARGS__)
#define LOG_DBG(LOG_TAG, ...)       lkv_logger_show(LOG_LEVEL_DEBUG,   LOG_TAG,    __VA_ARGS__)
#define LOG_TRACE(LOG_TAG, ...)     lkv_logger_show(LOG_LEVEL_TRACE,   LOG_TAG,    __VA_ARGS__)

/*
 * VD:
 *
 * lkv_logger_init(log_pritnf_interface, LOG_LEVEL_DEBUG);
 *
 * #define TAG "tag_name"
 *
 * LOG_INF(TAG, "Bootloader on slave %d start now",g_slave_address);
 *
 */


#ifdef __cplusplus

    }};
#endif

#endif //SELEX_BOOTLOADER_lkv_LOGGER_H
