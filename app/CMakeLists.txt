set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

cmake_minimum_required(VERSION 3.24)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(perrete_face_tracking src/main.cpp)

target_link_libraries(perrete_face_tracking PRIVATE Qt6::Widgets)

add_custom_command(TARGET perrete_face_tracking POST_BUILD
    COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe" "$<TARGET_FILE:perrete_face_tracking>"
)