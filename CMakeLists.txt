cmake_minimum_required(VERSION 3.23)
project(GachaKelompok
  LANGUAGES CXX C
  VERSION 0.1.2
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
include(GNUInstallDirs)

add_subdirectory(libs/ftxui)
include_directories(libs/ftxui/include)
set(SRCDIR src/Gacha)
include_directories(${SRCDIR})

add_library(gacha_lib STATIC
  ${SRCDIR}/cli.hpp
  ${SRCDIR}/cli.cpp
  ${SRCDIR}/Gacha.hpp
  ${SRCDIR}/Gacha.cpp
  ${SRCDIR}/Colors.cpp
  ${SRCDIR}/gachaui.hpp
  ${SRCDIR}/gachaui.cpp
)
target_link_libraries(gacha_lib
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
target_compile_options(gacha_lib PRIVATE -fno-exceptions)
target_compile_features(gacha_lib PRIVATE cxx_std_17)
target_include_directories(gacha_lib
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${SRCDIR}
)

add_executable(${PROJECT_NAME}   src/Main.cpp)
target_link_libraries(${PROJECT_NAME} gacha_lib)
target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${SRCDIR}) 

if (UNIX AND NOT APPLE)
  set(CPACK_GENERATOR "DEB;External;RPM;STGZ;TBZ2;TGZ;TXZ;TZ;TZST;ZIP")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -Os)
elseif (UNIX AND APPLE)
  set(CPACK_GENERATOR "DragNDrop;NuGet;TGZ;ZIP")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -Os)
elseif (WIN32)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /arch:AVX2 /fp:fast)
  set(CPACK_GENERATOR "DEB;NuGet;TGZ;ZIP")
else()
  set(CPACK_GENERATOR "ZIP")
endif()


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


set(CPACK_DEBIAN_PACKAGE_DEPENDS " ")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE_URL "https://github.com/RizalAchp/GachaKelompok/")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "RizalAchp")
set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Gacha Kelompok terminal UI")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/RizalAchp/GachaKelompok/")
set(CPACK_PACKAGE_NAME "gacha-kelompok")
set(CPACK_PACKAGE_VENDOR "RizalAchp")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

include(CPack)
