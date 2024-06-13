cmake_minimum_required(VERSION 3.18)
project(climin)

set(TARGET_BASE_NAME "${PROJECT_NAME}")
set(APP_NAME "${TARGET_BASE_NAME}")

add_executable(${APP_NAME}
  src/app.c
  src/argtable3.c
)

target_include_directories(${APP_NAME} PRIVATE
  "${TCL_INCLUDE_PATH}"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${APP_NAME} PRIVATE -Wall)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set_property(TARGET ${APP_NAME} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
  )
endif()
