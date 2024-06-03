

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()




########## generic_system block #############
# Definition of system, platform and toolset
#############################################





set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/mingw64/bin/c++.exe")


string(APPEND CONAN_CXX_FLAGS " -m64")
string(APPEND CONAN_C_FLAGS " -m64")
string(APPEND CONAN_SHARED_LINKER_FLAGS " -m64")
string(APPEND CONAN_EXE_LINKER_FLAGS " -m64")



# Conan conf flags start: 
# Conan conf flags end

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/luism/.conan2/p/b/sfml64ec15c86e657/p/lib" "C:/Users/luism/.conan2/p/b/freet8de6425b9bf2f/p/lib" "C:/Users/luism/.conan2/p/b/libpn322031a47a1d2/p/lib" "C:/Users/luism/.conan2/p/b/zlib60507095a962f/p/lib" "C:/Users/luism/.conan2/p/b/bzip2b0a6c993f9dc2/p/lib" "C:/Users/luism/.conan2/p/b/brotl4d186a2bde3e2/p/lib" "lib" "C:/Users/luism/.conan2/p/b/flac9331eafccec84/p/lib" "C:/Users/luism/.conan2/p/b/opena2f2216c58038b/p/lib" "C:/Users/luism/.conan2/p/b/vorbi0cce9bfd98937/p/lib" "C:/Users/luism/.conan2/p/b/ogge57b12bf95c15/p/lib" "lib" "C:/Users/luism/.conan2/p/b/fmtff2cab69d5818/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/luism/.conan2/p/b/sfml64ec15c86e657/p/include" "C:/Users/luism/.conan2/p/b/freet8de6425b9bf2f/p/include" "C:/Users/luism/.conan2/p/b/freet8de6425b9bf2f/p/include/freetype2" "C:/Users/luism/.conan2/p/b/libpn322031a47a1d2/p/include" "C:/Users/luism/.conan2/p/b/zlib60507095a962f/p/include" "C:/Users/luism/.conan2/p/b/bzip2b0a6c993f9dc2/p/include" "C:/Users/luism/.conan2/p/b/brotl4d186a2bde3e2/p/include" "C:/Users/luism/.conan2/p/b/brotl4d186a2bde3e2/p/include/brotli" "include" "C:/Users/luism/.conan2/p/b/flac9331eafccec84/p/include" "C:/Users/luism/.conan2/p/b/opena2f2216c58038b/p/include" "C:/Users/luism/.conan2/p/b/opena2f2216c58038b/p/include/AL" "C:/Users/luism/.conan2/p/b/vorbi0cce9bfd98937/p/include" "C:/Users/luism/.conan2/p/b/ogge57b12bf95c15/p/include" "include" "C:/Users/luism/.conan2/p/b/fmtff2cab69d5818/p/include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration


if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()
