//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>

#include "ublox/uart.h"
#include "ublox/internal/ublox_write.h"
#include "ublox/bits.h"
#include "ublox/message/ubx_cfg.h"

#define PORT_PAYLOAD_LENGTH     20
#define CFG_PAYLOAD_LENGTH      8
#define RATE_PAYLOAD_LENGTH     6
#define PSM_PAYLOAD_LENGTH      8
#define SBAS_PAYLOAD_LENGTH     8

void
_config_port(uint8_t port_id, uint16_t tx_ready, uint32_t mode, uint32_t baud, uint16_t proto_in, uint16_t proto_out,
             uint16_t flags) {
    uint8_t buffer[PORT_PAYLOAD_LENGTH] = {0};

    bits_write_uint8(buffer, port_id);
    bits_write_uint16(buffer + 2, tx_ready);
    bits_write_uint32(buffer + 4, mode);
    bits_write_uint32(buffer + 8, baud);
    bits_write_uint16(buffer + 12, proto_in);
    bits_write_uint16(buffer + 14, proto_out);
    bits_write_uint16(buffer + 16, flags);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_PORT, buffer, sizeof(buffer));
}

void ubx_config_setup_port(uint16_t baud) {
#if defined(DECODE_UBX) && defined(DECODE_NMEA)
    uint16_t proto_in = UART_PROTO_UBX | UART_PROTO_NMEA;
#elif defined(DECODE_UBX)
    uint16_t proto_in = UBX_UART_PROTO_UBX;
#elif defined(DECODE_NMEA)
    uint16_t proto_in = UART_PROTO_NMEA;
#else
    uint16_t proto_in = 0;
#endif

    _config_port(UBX_PORT_UART_ID, UBX_PORT_UART_TX_READY, UBX_PORT_UART_STOPBITS | UBX_PORT_UART_PARITY | UBX_PORT_UART_DATA_LEN, baud,
                 proto_in, UBX_UART_PROTO_UBX, 0);
    // reopen current serial port
    ubx_uart_create();

    _config_port(UBX_PORT_I2C_ID, 0, 0x08 << 1, 0, 0, 0, 0);
    _config_port(UBX_PORT_SPI_ID, 0, 0, 0, 0, 0, 0);
    _config_port(UBX_PORT_USB_ID, 0, 0, 0, 0, 0, 0);
}

void ubx_config_msg_rate(uint8_t message_class, uint8_t message_id, uint8_t rate) {
    uint8_t buffer[CFG_PAYLOAD_LENGTH] = {0};

    bits_write_uint8(buffer, message_class);
    bits_write_uint8(buffer + 1, message_id);
    bits_write_uint8(buffer + 2 + UBX_PORT_UART_ID, rate);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_MSG, buffer, sizeof(buffer));
}

void ubx_config_nav_rate(uint16_t rate_ms, uint16_t cycles) {
    uint8_t buffer[RATE_PAYLOAD_LENGTH] = {0};

    bits_write_uint16(buffer, rate_ms);
    bits_write_uint16(buffer + 2, cycles);
    bits_write_uint16(buffer + 4, 0x01);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_RATE, buffer, sizeof(buffer));
}

void ubx_config_psm(uint8_t power_mode) {
    uint8_t buffer[PSM_PAYLOAD_LENGTH] = {0};

    bits_write_uint8(buffer, 0);
    bits_write_uint8(buffer + 1, power_mode);
    bits_write_uint16(buffer + 2, 0);
    bits_write_uint8(buffer + 4, 0);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_PSM, buffer, sizeof(buffer));
}

void ubx_config_sbas(uint8_t enabled, uint8_t usage, uint8_t max, uint32_t scanmode, uint8_t scanmode2) {
    uint8_t buffer[SBAS_PAYLOAD_LENGTH] = {0};

    bits_write_uint8(buffer, !!enabled);
    bits_write_uint8(buffer + 1, usage);
    bits_write_uint8(buffer + 2, max);
    bits_write_uint8(buffer + 3, scanmode2);
    bits_write_uint32(buffer + 4, scanmode);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_SBAS, buffer, sizeof(buffer));
}