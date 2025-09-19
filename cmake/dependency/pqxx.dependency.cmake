if (APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBPQXX REQUIRED libpqxx)
    include_directories(${LIBPQXX_INCLUDE_DIRS})
    link_directories(${LIBPQXX_LIBRARY_DIRS})
    add_definitions(${LIBPQXX_CFLAGS_OTHER})

    set(LIBPQXX_TARGET ${LIBPQXX_LIBRARIES})
elseif (UNIX AND NOT APPLE)
    find_package(PostgreSQL REQUIRED)

    set(LIBPQXX_TARGET       "${CMAKE_CURRENT_SOURCE_DIR}/libs/libpqxx/lib/amd64/libpqxx-7.10.a")
    set(LIBPQXX_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/libs/libpqxx/include")

    set(PQ_LIB ${PostgreSQL_LIBRARIES})
else()
    find_package(libpqxx CONFIG REQUIRED)

    set(LIBPQXX_TARGET libpqxx::pqxx)
endif ()

set(PQXX_LIBS ${LIBPQXX_TARGET} ${PQ_LIB})
set(PQXX_LIBS_INCLUDE_DIRS ${LIBPQXX_INCLUDE_DIRS})