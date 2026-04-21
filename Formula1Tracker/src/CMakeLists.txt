cmake_minimum_required(VERSION 3.10)


set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(F1_GP_Tracker)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(../include)

add_executable(F1_GP_Tracker main.cpp) 

target_link_libraries(F1_GP_Tracker PRIVATE cpr::cpr nlohmann_json::nlohmann_json)