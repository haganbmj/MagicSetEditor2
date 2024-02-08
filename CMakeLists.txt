cmake_minimum_required(VERSION 3.13)

project(magicseteditor VERSION 2.4.0)
add_definitions(-DUNOFFICIAL_BUILD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(wxWidgets 3 REQUIRED COMPONENTS core base net html)
find_package(Boost REQUIRED COMPONENTS regex)

find_package(PkgConfig)

# find hunspell
pkg_check_modules(HUNSPELL hunspell)
if( NOT HUNSPELL_FOUND )
	message("-- Cannot find Hunspell via pkg-config, checking directly...")
	find_path(HUNSPELL_INCLUDE_DIRS hunspell.hxx)
	message("-- HUNSPELL_INCLUDE_DIRS = ${HUNSPELL_INCLUDE_DIRS}")
	find_library(HUNSPELL_LIBRARIES NAMES hunspell libhunspell)
	message("-- HUNSPELL_LIBRARIES = ${HUNSPELL_LIBRARIES}")
	if ( ${HUNSPELL_INCLUDE_DIRS} STREQUAL "HUNSPELL_INCLUDE_DIRS-NOTFOUND" )
		message(FATAL_ERROR "Hunspell cannot be found")
	else()
		message("-- Found Hunspell at ${HUNSPELL_LIBRARIES}")
	endif()
endif()

include_directories("${PROJECT_BINARY_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src")
include(${wxWidgets_USE_FILE})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${HUNSPELL_INCLUDE_DIRS})

# Magic Set Editor executable

add_executable(magicseteditor WIN32)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${HUNSPELL_LIBRARIES})

file(GLOB_RECURSE sources src/*.cpp)
list(FILTER sources EXCLUDE REGEX win32_cli_wrapper.cpp)
target_sources(magicseteditor PRIVATE ${sources})
target_precompile_headers(magicseteditor PRIVATE src/util/prec.hpp)

configure_file(src/config.hpp.in src/config.hpp)

# resource file

target_sources(magicseteditor PRIVATE resource/win32_res.rc)

# Halian trying Mac stuff

if(BUILD_APPLE_BUNDLE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/magicseteditor.app/Contents/PlugIns")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    set_target_properties(
    "magicseteditor"
        PROPERTIES
        MACOSX_BUNDLE_NAME                             "magicseteditor"
        MACOSX_BUNDLE_VERSION                          "${PROJECT_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER                   "org.magicseteditor.gui"
        MACOSX_BUNDLE_ICON_FILE                        "mse.icns"
        MACOSX_BUNDLE_INFO_PLIST                       "MacOSXBundleInfo.plist.in"
        MACOSX_BUNDLE                                  "TRUE"
        # MACHO_COMPATIBILITY_VERSION                  "12.0.0"
        RESOURCE                                       "${RESOURCE_FILES}"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY             ""
        XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED          NO
        XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT       dwarf
        XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
        XCODE_ATTRIBUTE_CLANG_LINK_OBJC_RUNTIME        NO
    )
    add_custom_command(
        TARGET "magicseteditor"
        POST_BUILD
        COMMAND dylibbundler ARGS -od -ns -b -x "${CMAKE_BINARY_DIR}/magicseteditor.app/Contents/MacOS/magicseteditor" -d "${CMAKE_BINARY_DIR}/magicseteditor.app/Contents/libs"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Changing library search path from absolute to relative…"
    )
    add_custom_command(
        TARGET "magicseteditor"
        POST_BUILD
        COMMAND mkdir ARGS -v "${CMAKE_BINARY_DIR}/magicseteditor.app/Contents/Resources"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Copying icons…"
    )
    add_custom_command(
        TARGET "magicseteditor"
        POST_BUILD
        COMMAND cp ARGS -v "${PROJECT_SOURCE_DIR}/*.icns" "${CMAKE_BINARY_DIR}/magicseteditor.app/Contents/Resources"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Copying icons…"
    )
endif()

# magicseteditor.com: wrapper to enable command line executable on windows

if(WIN32)
  add_executable(magicseteditor-cli)
  target_sources(magicseteditor-cli PRIVATE src/cli/win32_cli_wrapper.cpp)
  add_custom_command(TARGET magicseteditor-cli POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/magicseteditor-cli.exe" "${PROJECT_BINARY_DIR}/magicseteditor.com"
  )
endif()


# warnings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wsuggest-override -Wstrict-null-sentinel -Wno-comment -Wno-unused-parameter")
endif()

# visual studio debugger
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT magicseteditor)

# Static linking on windows
if (${VCPKG_TARGET_TRIPLET} MATCHES ".*-static")
  message("Static linking")
  set(CompilerFlags CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE)
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GL")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG")
  # Need explicit dependencies on wx's dependencies
  find_package(png REQUIRED)
  find_package(tiff REQUIRED)
  find_package(jpeg REQUIRED)
  find_package(zlib REQUIRED)
  target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} ${TIFF_LIBRARIES})
  # Defines
  add_definitions(-DSTATIC)
  add_definitions(-DHUNSPELL_STATIC)
endif()

# Test suite
include(test/tests.cmake)
