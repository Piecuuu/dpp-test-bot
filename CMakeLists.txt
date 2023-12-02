cmake_minimum_required(VERSION 3.22)
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/config.cpp
  src/commands/ping.cpp
  src/slash.cpp
  src/commands/hello.cpp
)

find_package(DPP REQUIRED)
find_package(yaml-cpp REQUIRED)

target_link_libraries(${PROJECT_NAME}
  ${DPP_LIBRARIES}
  ${YAML_CPP_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${DPP_INCLUDE_DIR}
  ${YAML_INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
