set(INC_PATH     "./include")
set(LIB_DIR_PATH "./lib")
# Lib include
set(LIB_SRC_FILES)
set(LIB_INC_PATH)

set(LIBRARIES ${CMAKE_SOURCE_DIR}/lib/${LOCAL_LIB})
foreach(libdir ${LIBRARIES})
    set(subdir ${libdir}/src)
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

include_directories(${INC_PATH} ${LIB_INC_PATH})
