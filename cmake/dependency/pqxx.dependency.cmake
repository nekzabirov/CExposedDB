if (APPLE)
    # Используем libpqxx из vcpkg вместо системного pkg-config
    find_package(libpqxx CONFIG REQUIRED)
    set(PQXX_LIBS libpqxx::pqxx)
    set(PQXX_LIBS_INCLUDE_DIRS "") # Не нужно, libpqxx::pqxx уже содержит пути
else()
    find_package(libpqxx CONFIG REQUIRED)
    set(PQXX_LIBS libpqxx::pqxx)
    set(PQXX_LIBS_INCLUDE_DIRS "") # Не нужно для современных CMake targets
endif()
