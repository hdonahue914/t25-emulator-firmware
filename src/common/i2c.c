/**
 * @file i2c.c
 * @author hdonahue (hwdonahue@gmail.com)
 * @brief generic i2c driver
 * @version 0.1
 * @date 2025-06-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "i2c.h"
#include <string.h>

// RX circular buffer
static uint8_t rx_buffer[I2C_BUFFER_SIZE];
static volatile size_t rx_head = 0;
static volatile size_t rx_tail = 0;

// TX circular buffer
static uint8_t tx_buffer[I2C_BUFFER_SIZE];
static volatile size_t tx_head = 0;
static volatile size_t tx_tail = 0;

// Platform-specific initialization (you implement this)
extern void platform_i2c_init(uint8_t address1, uint8_t address2);

int i2c_init(uint8_t address1, uint8_t address2) {
    rx_head = rx_tail = tx_head = tx_tail = 0;
    platform_i2c_init(address1, address2);
    return 0;
}

static size_t buffer_write(uint8_t *buf, volatile size_t *head, volatile size_t *tail,
                           const uint8_t *data, size_t len) {
    size_t written = 0;
    for (size_t i = 0; i < len; ++i) {
        size_t next = (*head + 1) % I2C_BUFFER_SIZE;
        if (next == *tail) break; // full
        buf[*head] = data[i];
        *head = next;
        written++;
    }
    return written;
}

static size_t buffer_read(uint8_t *buf, volatile size_t *head, volatile size_t *tail,
                          uint8_t *out, size_t len) {
    size_t read = 0;
    while (*tail != *head && read < len) {
        out[read++] = buf[*tail];
        *tail = (*tail + 1) % I2C_BUFFER_SIZE;
    }
    return read;
}

bool i2c_rx_available(void) {
    return rx_head != rx_tail;
}

bool i2c_tx_pending(void) {
    return tx_head != tx_tail;
}

size_t i2c_read(uint8_t *out, size_t len) {
    return buffer_read(rx_buffer, &rx_head, &rx_tail, out, len);
}

size_t i2c_write(const uint8_t *data, size_t len) {
    return buffer_write(tx_buffer, &tx_head, &tx_tail, data, len);
}

// Called from platform-specific RX interrupt or event
void i2c_on_receive(uint8_t address, const uint8_t *data, size_t len) {
    (void)address; 
    buffer_write(rx_buffer, &rx_head, &rx_tail, data, len);
}

// Called from platform-specific TX event
size_t i2c_on_transmit(uint8_t address, uint8_t *data, size_t max_len) {
    (void)address; 
    return buffer_read(tx_buffer, &tx_head, &tx_tail, data, max_len);
}
