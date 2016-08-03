# CMake settings
cmake_minimum_required(VERSION 3.0)
# Hunter settings
include("cmake/HunterGate.cmake")
HunterGate(
    URL "http://192.168.2.27/packages/hunter/hunter-project-v1.4.11.tar.gz"
    SHA1 "c4b347f845945eb11fb4f7ddf30597e16dd9ef80"
)
include(hunter_fatal_error)

# Module settings
set(LIBRARY_NAME "SQLite3")
set(LIBRARY_VERSION 3.13.0)

project(${LIBRARY_NAME} VERSION ${LIBRARY_VERSION})

###############################################################################
# Library settings
###############################################################################

# Generate source file list.
set(LIBRARY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE LIBRARY_SOURCE_FILES
    ${LIBRARY_SOURCE_DIR}/*.c
    ${LIBRARY_SOURCE_DIR}/*.h)

# Generate public header list.
set(LIBRARY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
file(GLOB_RECURSE LIBRARY_HEADER_FILES
    ${LIBRARY_INCLUDE_DIR}/*.h)

# Define library.
add_library(${LIBRARY_NAME} ${LIBRARY_SOURCE_FILES} ${LIBRARY_HEADER_FILES})
set_target_properties(${LIBRARY_NAME} PROPERTIES DEBUG_POSTFIX "d")

# Configure compiler flags and definitions.
if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSQLITE_CORE")
else()
    set_target_properties(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-DSQLITE_CORE")
endif()

# Generate header files list.
target_include_directories(${LIBRARY_NAME} PRIVATE ${LIBRARY_INCLUDE_DIR} ${LIBRARY_SOURCE_DIR})

###############################################################################
# Installation settings
###############################################################################

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Note: variable 'targets_export_name' used
configure_file("cmake/Config.cmake.in" "${project_config}" @ONLY)

install(
    TARGETS ${LIBRARY_NAME}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

install(
    DIRECTORY ${LIBRARY_INCLUDE_DIR}
    DESTINATION "${include_install_dir}"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
