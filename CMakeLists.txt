cmake_minimum_required(VERSION 3.12)

set(project_name 003-allocators)
set(executable_name custom_alloc)

find_package(Git)
if (Git_FOUND)
    execute_process(COMMAND
    ${GIT_EXECUTABLE} describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE PATCH_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

if (NOT PATCH_VERSION)
    set(PATCH_VERSION "0" CACHE INTERNAL "Patch version")
endif()

set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(${project_name} VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(version.h.in version.h)

# Add executables and libraries
add_executable(${executable_name} main.cpp)
add_library(${project_name} INTERFACE)

# set_target_properties(${executable_name} ${project_name} PROPERTIES
#     CXX_STANDARD 17
#     CXX_STANDARD_REQUIRED ON
# )

target_include_directories(${project_name} 
    INTERFACE "${CMAKE_SOURCE_DIR}"
)

target_link_libraries(${executable_name} PRIVATE
    ${project_name}
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    # add tests executables
    add_executable(test_alloc test_alloc.cpp)
    add_executable(test_MyMap test_MyMap.cpp)

    set(test_list test_alloc test_MyMap)

    set_target_properties(${test_list} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(${test_list} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_alloc
        ${Boost_LIBRARIES}
    )
    target_link_libraries(test_MyMap
        ${Boost_LIBRARIES}
    )
endif()

if (MSVC)
    target_compile_options(${executable_name} PRIVATE
        /W4
    )

    if(WITH_BOOST_TEST)
        target_compile_options(test_alloc PRIVATE
            /W4
        )

        target_compile_options(test_MyMap PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(${executable_name} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_alloc PRIVATE
            -Wall -Wextra -pedantic -Werror
        )

        target_compile_options(test_MyMap PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${executable_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_MyMap test_MyMap)
endif()
