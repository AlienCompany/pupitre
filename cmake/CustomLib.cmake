set(INC_PATH     "./include")
set(LIB_DIR_PATH "./lib")
# Lib include
set(LIB_SRC_FILES)
set(LIB_INC_PATH "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino")

foreach(libdir ${LOCAL_LIB})
    set(subdir ${CMAKE_SOURCE_DIR}/lib/${libdir}/src)
    file(GLOB_RECURSE lib_files "${subdir}/*.cpp"
            "${subdir}/*.cc"
            "${subdir}/*.c"
            "${subdir}/*.cxx"
            "${subdir}/*.S"
            "${subdir}/*.s"
            "${subdir}/*.sx"
            "${subdir}/*.asm")
    if(IS_DIRECTORY ${subdir})
        list(APPEND LIB_INC_PATH  "${subdir}")
    endif()
    list(APPEND LIB_SRC_FILES "${lib_files}")
endforeach()

message(LIB_SRC_FILES: ${LIB_SRC_FILES})

include_directories(${INC_PATH} ${LIB_INC_PATH})
