# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# set(PICO_CYW43_SUPPORTED 1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
# Set minimum required version of CMake
 
# Include build functions from Pico SDK
# include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/RF24/CMakeLists.txt)
 
# set(PICO_BOARD pico)
# set(PROJECT_NAME FlightController)
# Set name of project (as PROJECT_NAME) and C/C++ standards
project(FLIGHTCONTROLLER C CXX ASM)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(FLIGHTCONTROLLER 
    Core/FileSystem/hw_config.c
    main.cpp
)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build) 
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/arduino-pico/libraries ardino_pico) 

# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/RF24 NRF24Build)
# Create map/bin/hex/uf2 files
pico_add_extra_outputs(FLIGHTCONTROLLER)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(FLIGHTCONTROLLER        
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_gpio
    hardware_pwm
    hardware_adc
    hardware_clocks
    FatFs_SPI
    RF24
    # ardino_pico
)
if (PICO_CYW43_SUPPORTED)
    target_link_libraries(FLIGHTCONTROLLER pico_cyw43_arch_none)
endif()
# Enable usb output, disable uart output
pico_enable_stdio_usb(FLIGHTCONTROLLER 0)
pico_enable_stdio_uart(FLIGHTCONTROLLER 1)

target_compile_definitions(${CMAKE_PROJECT_NAME}
    PUBLIC PICO_DEFAULT_SPI=1 # can only be 0 or 1 (as in `spi0` or `spi1`)
    PUBLIC PICO_DEFAULT_SPI_SCK_PIN=10 # depends on which SPI bus (0 or 1) is being used
    PUBLIC PICO_DEFAULT_SPI_TX_PIN=11  # depends on which SPI bus (0 or 1) is being used
    PUBLIC PICO_DEFAULT_SPI_RX_PIN=12 # depends on which SPI bus (0 or 1) is being used 
    PUBLIC PICO_DEFAULT_SPI_CSN_PIN=13
    PUBLIC PICO_BUILD
)