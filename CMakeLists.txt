# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)
 
# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Core/DataAndVideo/RF24/CMakeLists.txt)
# Set name of project (as PROJECT_NAME) and C/C++ standards
project(FlightController C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
    main.cpp
)
add_subdirectory(Core/FileSystem/SDPicoGitProject/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)
# add_subdirectory(Core/DataAndVideo/RF24 NRF24Build)
# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_spi
    hardware_i2c
    FatFs_SPI
    RF24
)
# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

target_compile_definitions(${CMAKE_PROJECT_NAME}
    PUBLIC PICO_DEFAULT_SPI=0 # can only be 0 or 1 (as in `spi0` or `spi1`)
    PUBLIC PICO_DEFAULT_SPI_SCK_PIN=6 # depends on which SPI bus (0 or 1) is being used
    PUBLIC PICO_DEFAULT_SPI_TX_PIN=7  # depends on which SPI bus (0 or 1) is being used
    PUBLIC PICO_DEFAULT_SPI_RX_PIN=4  # depends on which SPI bus (0 or 1) is being used
    PUBLIC PICO_BUILD
)