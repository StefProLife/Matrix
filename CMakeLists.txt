cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(SOURCES_FILE src/main.cpp)

project(Matrix_Project VERSION ${PROJECT_VESRION})

add_executable(matrix ${SOURCES_FILE})

set_target_properties(matrix PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(matrix
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT yuri.andreev@mail.com)
set(CPACK_PACKAGE_VENDOR "Andreev@Company")
set(CPACK_PACKAGE_NAME "matrix")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
include(CPack)