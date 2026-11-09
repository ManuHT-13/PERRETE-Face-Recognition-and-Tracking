set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

cmake_minimum_required(VERSION 3.24)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_package(OpenCV REQUIRED COMPONENTS core imgproc videoio)

add_executable(perrete_face_tracking src/main.cpp)

target_link_libraries(perrete_face_tracking PRIVATE Qt6::Widgets ${OpenCV_LIBS})

add_custom_command(TARGET perrete_face_tracking POST_BUILD
    COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe" "$<TARGET_FILE:perrete_face_tracking>"
)

add_custom_command(TARGET perrete_face_tracking POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OpenCV_DIR}/x64/vc16/bin/opencv_world$<$<CONFIG:Debug>:d>.dll"
        $<TARGET_FILE_DIR:perrete_face_tracking>
)