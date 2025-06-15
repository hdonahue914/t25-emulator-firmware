/**
 * @file app.c
 * @author hdonahue (hwdonahue@gmail.com)
 * @brief main application entry point
 * @version 0.1
 * @date 2025-06-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once
#include <stdint.h>
#include <stddef.h>

#include "app.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
 * @fn app_init
 * @brief Initialize the application
 * 
 */
#include "common/i2c.h"
#include "common/uart.h"
#include "common/gpio.h"

/**
 * @fn app_init
 * @brief initialize the application
 * 
 */
 void app_init(void) 
 {
    // Initialize hardware drivers
    

    // Initialize managers
    sensor_manager_init();
    wiring_manager_init();
    relay_manager_init();
 }


/**
 * @fn app_update
 * @brief application main loop
 * 
 */
 void app_update(void)
 {
    while (1)
    {
        
    }
 }


 #ifdef __cplusplus
}
#endif