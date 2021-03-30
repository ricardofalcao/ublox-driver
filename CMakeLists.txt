cmake_minimum_required(VERSION 3.19)
project(ublox C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
add_library(ublox src/ublox/ublox.c src/ublox/ublox_read.c src/ublox/bits.c src/ublox/message/ubx_nav.c)

add_executable(linux_example example/linux.c example/linux_uart.c)
target_link_libraries(linux_example
        PRIVATE
        ublox
        )