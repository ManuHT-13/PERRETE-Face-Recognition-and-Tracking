cmake_minimum_required(VERSION 3.24)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(OpenCV REQUIRED COMPONENTS core imgproc videoio)
find_package(CUDAToolkit REQUIRED)

set(TENSORRT_ROOT "C:/Program Files/TensorRT-10.16.1.11" CACHE PATH "Raíz de TensorRT")

find_path(TENSORRT_INCLUDE_DIR NvInfer.h
    HINTS ${TENSORRT_ROOT} ENV TENSORRT_ROOT
    PATH_SUFFIXES include)

find_library(TENSORRT_LIB NAMES nvinfer_10 nvinfer
    HINTS ${TENSORRT_ROOT} ENV TENSORRT_ROOT
    PATH_SUFFIXES lib)

if(NOT TENSORRT_INCLUDE_DIR OR NOT TENSORRT_LIB)
    message(FATAL_ERROR "TensorRT not found")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/*.h
)

add_executable(perrete_face_tracking ${SOURCES})

target_include_directories(perrete_face_tracking PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${TENSORRT_INCLUDE_DIR}
)

target_link_libraries(perrete_face_tracking PRIVATE
    Qt6::Widgets
    ${OpenCV_LIBS}
    CUDA::cudart
    ${TENSORRT_LIB}
)

get_filename_component(TENSORRT_LIB_DIR "${TENSORRT_LIB}" DIRECTORY)
file(GLOB TENSORRT_DLLS "${TENSORRT_LIB_DIR}/nvinfer_10.dll" "${TENSORRT_LIB_DIR}/nvinfer.dll")

add_custom_command(TARGET perrete_face_tracking POST_BUILD
    COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe" "$<TARGET_FILE:perrete_face_tracking>"
)

add_custom_command(TARGET perrete_face_tracking POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OpenCV_DIR}/x64/vc16/bin/opencv_world$<$<CONFIG:Debug>:d>.dll"
        $<TARGET_FILE_DIR:perrete_face_tracking>
)

add_custom_command(TARGET perrete_face_tracking POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TENSORRT_DLLS}
        $<TARGET_FILE_DIR:perrete_face_tracking>
        VERBATIM
)