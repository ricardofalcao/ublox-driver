cmake_minimum_required(VERSION 3.19)
project(ublox C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
add_library(ublox
        src/ublox/ublox.c
        src/ublox/internal/ublox_read.c
        src/ublox/internal/ublox_write.c
        src/ublox/bits.c
        src/ublox/message/ubx_nav.c
        src/ublox/message/ubx_ack.c
        src/ublox/message/ubx_cfg.c
        )

add_executable(linux_example example/linux.c example/linux_uart.c)
target_link_libraries(linux_example
        PRIVATE
        ublox
        )