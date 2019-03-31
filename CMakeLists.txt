cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CustomBoard.cmake)

set(LOCAL_LIB arduino-lib-alien-co)
include(${CMAKE_SOURCE_DIR}/cmake/CustomLib.cmake)

set(COMMON_CPPS
        )
set(COMMON_HS
        )
set(COMMON_LIB
        )
set(PROJECT_BOARD mega)
set(PORT COM8)

message(LIB_SRC_FILES ${LIB_SRC_FILES})
message(LIB_INC_PATH ${LIB_INC_PATH})
# ==================== Reveil : BEGIN ====================
set(PROJECT_NAME AlienProject)
project(${PROJECT_NAME})

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_SRCS ${COMMON_CPPS} ${LIB_SRC_FILES}
        main.cpp
        )
set(${CMAKE_PROJECT_NAME}_HDRS ${COMMON_HS}
        )
set(${CMAKE_PROJECT_NAME}_BOARD ${PROJECT_BOARD})
set(${CMAKE_PROJECT_NAME}_PORT ${PORT})
set(${CMAKE_PROJECT_NAME}_ARDLIBS ${COMMON_LIB})

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
# ==================== Reveil : END ====================


