cmake_minimum_required(VERSION 3.20.0)

set(BOARD adafruit_feather_nrf52840)
set(SHIELD ssd1306_adafruit_feather_oled_128x32)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project( app LANGUAGES C VERSION 1.0.0)

configure_file( app_version.h.in ${CMAKE_BINARY_DIR}/app/include/app_version.h)

include(${ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)

target_include_directories( app PRIVATE ${CMAKE_BINARY_DIR}/app/include src)
target_include_directories( app PRIVATE ${CMAKE_BINARY_DIR}/include src)
target_sources( app PRIVATE src/main.c)

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
generate_cfb_font_for_target(app fonts/magic5.ttf ${gen_dir}/cfb_font_magic5.h 8 8 -s 8 --first 32 --last 126)
