# Set minimum required version of CMake
cmake_minimum_required (VERSION 3.12)

# Include build functions from Pico SDK
include ($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include ($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project (button-debounce C CXX ASM)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable (
  ${PROJECT_NAME}
)

# sources to include
target_sources (${PROJECT_NAME} PRIVATE
  ${PROJECT_NAME}.c
  pico_debounce.c
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries (
  ${PROJECT_NAME}
  pico_stdlib
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs (${PROJECT_NAME})

# Enable usb output, disable uart output (default)
# If using UART over USB with a single Pico, swap
# the 0, 1 values and uncomment the following:
#
# pico_enable_stdio_usb(${PROJECT_NAME} 0)
# pico_enable_stdio_uart(${PROJECT_NAME} 1)
