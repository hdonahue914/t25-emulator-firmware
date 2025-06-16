/**
 * @file i2c.h
 * @author hdonahue (hwdonahue@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-06-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define I2C_BUFFER_SIZE 128

#ifdef __cplusplus
extern "C" {
#endif

// Initializes I2C peripheral with two slave addresses
int i2c_init(uint8_t address1, uint8_t address2);

// Called by platform code when data is received from master
void i2c_on_receive(uint8_t address, const uint8_t *data, size_t len);

// Called by platform code when master requests data
size_t i2c_on_transmit(uint8_t address, uint8_t *data, size_t max_len);

// Reads from the internal RX buffer (consumer function)
size_t i2c_read(uint8_t *out, size_t len);

// Writes to the internal TX buffer (producer function)
size_t i2c_write(const uint8_t *data, size_t len);

// Check if RX or TX buffer has data
bool i2c_rx_available(void);
bool i2c_tx_pending(void);

#ifdef __cplusplus
}
#endif
