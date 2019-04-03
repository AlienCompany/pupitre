cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)


set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)

set(PROJECT_BOARD mega)
set(PORT COM8)

set(LIB_DIR_PATH "./src")
# Lib include
set(LIB_SRC_FILES)
set(LIB_INC_PATH)
file(GLOB_RECURSE lib_files "${LIB_DIR_PATH}/*.cpp"
        "${LIB_DIR_PATH}/*.cc"
        "${LIB_DIR_PATH}/*.c"
        "${LIB_DIR_PATH}/*.cxx"
        "${LIB_DIR_PATH}/*.S"
        "${LIB_DIR_PATH}/*.s"
        "${LIB_DIR_PATH}/*.sx"
        "${LIB_DIR_PATH}/*.asm")
if(IS_DIRECTORY ${LIB_DIR_PATH})
    list(APPEND LIB_INC_PATH  "${LIB_DIR_PATH}")
endif()
list(APPEND LIB_SRC_FILES "${lib_files}")

include_directories(${INC_PATH} ${LIB_INC_PATH})

## ==================== ALL TEST : BEGIN ====================
#FOREACH(TESTNAME "ComB1" "ComB2" "MatriceLed" "Moteur" "UltraSon" "Debug")
#    # -------------------- MarvinTest : BEGIN --------------------
#    set(PROJECT_NAME_TEST MarvinTest${TESTNAME})
#    project(${PROJECT_NAME_TEST})
#
#    print_board_list()
#    #### Uncomment below additional settings as needed.
#    set(${PROJECT_NAME_TEST}_SRCS test${TESTNAME}.cpp ${COMMON_CPPS})
#    set(${PROJECT_NAME_TEST}_HDRS ${COMMON_HS})
#    set(${PROJECT_NAME_TEST}_BOARD ${PROJECT_BOARD})
#    set(${PROJECT_NAME_TEST}_PORT ${PORT})
#    set(${PROJECT_NAME_TEST}_ARDLIBS ${COMMON_LIB})
#
#    generate_arduino_firmware(${PROJECT_NAME_TEST})
#    # -------------------- MarvinTest : END --------------------
#ENDFOREACH()
## ==================== ALL TEST : END ====================

# ==================== Reveil : BEGIN ====================
set(PROJECT_NAME basic)
project(${PROJECT_NAME})

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_SKETCH examples/${PROJECT_NAME}/${PROJECT_NAME}.ino) ## ${COMMON_CPPS} ${LIB_SRC_FILES})
set(${CMAKE_PROJECT_NAME}_SRCS ${COMMON_CPPS} ${LIB_SRC_FILES})
set(${CMAKE_PROJECT_NAME}_HDRS ${COMMON_HS})
set(${CMAKE_PROJECT_NAME}_BOARD ${PROJECT_BOARD})
set(${CMAKE_PROJECT_NAME}_PORT ${PORT})
## set(${CMAKE_PROJECT_NAME}_ARDLIBS ${COMMON_LIB} )

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
# ==================== Reveil : END ====================


