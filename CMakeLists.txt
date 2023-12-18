cmake_minimum_required(VERSION 3.22)
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(SRCDIR src)
set(EVENTDIR ${SRCDIR}/events)
set(CMDDIR ${SRCDIR}/commands)

set(EVENTS
  ${EVENTDIR}/ready.cpp
  ${EVENTDIR}/slashcommand.cpp
)

set(COMMANDS
  ${CMDDIR}/avatar.cpp
  ${CMDDIR}/hello.cpp
  ${CMDDIR}/ping.cpp
)

add_executable(${PROJECT_NAME}
  ${SRCDIR}/main.cpp
  ${SRCDIR}/config.cpp
  ${SRCDIR}/slash.cpp
  ${SRCDIR}/bot.cpp
  ${SRCDIR}/event.cpp
  ${SRCDIR}/logger.cpp
  ${COMMANDS}
  ${EVENTS}
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
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
