cmake_minimum_required(VERSION 3.20)
project(CPostgresql VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/dependency/pqxx.dependency.cmake)

set(NAME cExposed)

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Создание библиотеки
add_library(${NAME} STATIC
        src/dbclient.cpp
        src/value/timestamp.value.cpp
)

# Алиас для удобства
add_library(CPostgresql::cpostgresql ALIAS ${NAME})

# Настройка include директорий
target_include_directories(${NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Настройка свойств компиляции
target_compile_features(${NAME} PUBLIC cxx_std_23)

# Зависимости - используем современный подход с target
target_link_libraries(${NAME} PUBLIC ${PQXX_LIBS})

# Добавляем include директории только если они не пустые и используем генераторные выражения
if(PQXX_LIBS_INCLUDE_DIRS)
    target_include_directories(${NAME} 
        PUBLIC 
        $<BUILD_INTERFACE:${PQXX_LIBS_INCLUDE_DIRS}>
    )
endif()

# Установка библиотеки
include(GNUInstallDirs)

install(TARGETS ${NAME}
        EXPORT MyLibraryTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Экспорт targets
install(EXPORT MyLibraryTargets
        FILE MyLibraryTargets.cmake
        NAMESPACE CPostgresql::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CPostgresql
)

# Создание конфигурационного файла
include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPostgresqlConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/CPostgresqlConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CPostgresql
)

write_basic_package_version_file(
        CPostgresqlConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/CPostgresqlConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/CPostgresqlConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyLibrary
)
