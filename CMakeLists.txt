cmake_minimum_required(VERSION 3.10)

project(marisa)

if(UNIX)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -Wextra -Wconversion")
endif()

set(MARISA_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option(Marisa_FOUND  "marisa found" ON)
set(Marisa_INCLUDE_PATH ${MARISA_ROOT}/include CACHE INTERNAL "marisa public include path" FORCE)

set(MARISA_INCLUDE_DIRS
    ${MARISA_ROOT}/lib
    ${MARISA_ROOT}/include)

set(MARISA_SRC
    ${MARISA_ROOT}/lib/marisa/grimoire/io/reader.cc
    ${MARISA_ROOT}/lib/marisa/grimoire/io/mapper.cc
    ${MARISA_ROOT}/lib/marisa/grimoire/io/writer.cc
    ${MARISA_ROOT}/lib/marisa/grimoire/trie/tail.cc
    ${MARISA_ROOT}/lib/marisa/grimoire/trie/louds-trie.cc
    ${MARISA_ROOT}/lib/marisa/grimoire/vector/bit-vector.cc
    ${MARISA_ROOT}/lib/marisa/trie.cc
    ${MARISA_ROOT}/lib/marisa/agent.cc
    ${MARISA_ROOT}/lib/marisa/keyset.cc
)

include_directories( ${MARISA_INCLUDE_DIRS} )

add_library( marisa ${MARISA_SRC} )

install(TARGETS marisa
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

set(include_headers ${MARISA_ROOT}/include/marisa.h)
file(GLOB libmarisa_include_headers ${MARISA_ROOT}/include/marisa/*.h)
install(FILES ${include_headers} DESTINATION include)
install(FILES ${libmarisa_include_headers} DESTINATION include/marisa)
