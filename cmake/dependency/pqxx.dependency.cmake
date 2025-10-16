if (APPLE)
    # Используем libpqxx из vcpkg вместо системного pkg-config
    find_package(libpqxx CONFIG REQUIRED)
    set(PQXX_LIBS libpqxx::pqxx)
    set(PQXX_LIBS_INCLUDE_DIRS "") # Не нужно, libpqxx::pqxx уже содержит пути
elseif (UNIX AND NOT APPLE)
    find_package(PostgreSQL REQUIRED)

    set(LIBPQXX_TARGET       "${CMAKE_CURRENT_SOURCE_DIR}/libs/libpqxx/lib/amd64/libpqxx-7.10.a")
    set(LIBPQXX_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/libs/libpqxx/include")

    set(PQ_LIB ${PostgreSQL_LIBRARIES})
    set(PQXX_LIBS ${LIBPQXX_TARGET} ${PQ_LIB})
    set(PQXX_LIBS_INCLUDE_DIRS ${LIBPQXX_INCLUDE_DIRS})
else()
    find_package(libpqxx CONFIG REQUIRED)
    set(PQXX_LIBS libpqxx::pqxx)
    set(PQXX_LIBS_INCLUDE_DIRS "") # Не нужно для современных CMake targets
endif()
