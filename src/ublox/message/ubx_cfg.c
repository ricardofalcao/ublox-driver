//
// Created by ricardo on 30/03/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "ublox/uart.h"
#include "ublox/internal/ublox_write.h"
#include "ublox/bits.h"
#include "ublox/message/ubx_cfg.h"

#define PORT_PAYLOAD_LENGTH     20
#define ANT_PAYLOAD_LENGTH      4
#define INF_PAYLOAD_LENGTH      10
#define CFG_PAYLOAD_LENGTH      12
#define MSG_PAYLOAD_LENGTH      8
#define RATE_PAYLOAD_LENGTH     6
#define PSM_PAYLOAD_LENGTH      8
#define NAV5_PAYLOAD_LENGTH     36
#define RST_PAYLOAD_LENGTH      4

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

    _config_port(UBX_PORT_UART_ID, UBX_PORT_UART_TX_READY,
                 UBX_PORT_UART_STOPBITS | UBX_PORT_UART_PARITY | UBX_PORT_UART_DATA_LEN, baud,
                 proto_in, UBX_UART_PROTO_UBX, 0);
    // reopen current serial port
    ubx_uart_create();

    _config_port(UBX_PORT_I2C_ID, 0, 0x08 << 1, 0, 0, 0, 0);
    _config_port(UBX_PORT_SPI_ID, 0, 0, 0, 0, 0, 0);
    _config_port(UBX_PORT_USB_ID, 0, 0, 0, 0, 0, 0);
}

void ubx_config_ant(uint16_t flags, uint16_t pins) {
    uint8_t buffer[ANT_PAYLOAD_LENGTH] = {0};

    bits_write_uint16(buffer, flags);
    bits_write_uint16(buffer + 2, pins);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_ANT, buffer, sizeof(buffer));
}

void ubx_config_cfg(uint32_t clear_mask, uint32_t save_mask, uint32_t load_mask) {
    uint8_t buffer[CFG_PAYLOAD_LENGTH] = {0};

    bits_write_uint32(buffer, clear_mask);
    bits_write_uint32(buffer + 4, save_mask);
    bits_write_uint32(buffer + 8, load_mask);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_CFG, buffer, sizeof(buffer));
}

void ubx_config_inf(uint8_t protocol_id, uint8_t inf_mask) {
    uint8_t buffer[INF_PAYLOAD_LENGTH] = {0};

    bits_write_uint8(buffer, protocol_id);
    bits_write_uint8(buffer + 5, inf_mask); //port1

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_INF, buffer, sizeof(buffer));
}

void ubx_config_gnss(uint8_t tracking_channels, uint8_t used_channels, GNSSConfig_t *configs, size_t configsLen) {
    size_t pretended_gnss_config_len = 4 + 8 * configsLen;
    uint8_t * buffer = calloc(pretended_gnss_config_len, sizeof(uint8_t));

    bits_write_uint8(buffer, 0x00);
    bits_write_uint8(buffer + 1, tracking_channels);
    bits_write_uint8(buffer + 2, used_channels);
    bits_write_uint8(buffer + 3, configsLen);

    for (uint8_t i = 0; i < configsLen; i++) {
        bits_write_uint8(buffer + (4 + 8 * i), configs[i].id);
        bits_write_uint8(buffer + (5 + 8 * i), configs[i].minimumChannels);
        bits_write_uint8(buffer + (6 + 8 * i), configs[i].maximumChannels);
        bits_write_uint32(buffer + (8 + 8 * i), configs[i].flags);
    }

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_GNSS, buffer, pretended_gnss_config_len);
    free(buffer);
}

void ubx_config_msg_rate(uint8_t message_class, uint8_t message_id, uint8_t rate) {
    uint8_t buffer[MSG_PAYLOAD_LENGTH] = {0};

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

void ubx_config_dynmodel(uint8_t model) {
    uint8_t buffer[NAV5_PAYLOAD_LENGTH] = {0};

    bits_write_uint16(buffer, UBX_NAV5_DYNMODEL_MASK);
    bits_write_uint8(buffer + 2, model);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_NAV5, buffer, sizeof(buffer));
}

void ubx_config_rst(uint16_t section, uint8_t reset_mode) {
    uint8_t buffer[RST_PAYLOAD_LENGTH] = {0};

    bits_write_uint16(buffer, section);
    bits_write_uint8(buffer + 2, reset_mode);

    ubx_write_ubx_packet(UBX_CLASS_CFG, UBX_MESSAGE_CFG_RST, buffer, sizeof(buffer));

}

/*
 *
 */

void ubx_process_ubx_cfg(uint8_t packet_id, uint8_t * payload, size_t payload_length) {
    switch(packet_id) {
        case UBX_MESSAGE_CFG_GNSS: {
            break;
        }
    }
}