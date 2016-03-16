MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib
MY_LIBS = $(top_srcdir)/lib/marisa/libmarisa.la

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion $(MY_INCLUDE)

lib_LTLIBRARIES = libmarisa.la

libmarisa_la_SOURCES = \
  keyset.cc \
  agent.cc \
  trie.cc \
  grimoire/io/mapper.cc \
  grimoire/io/reader.cc \
  grimoire/io/writer.cc \
  grimoire/vector/bit-vector.cc \
  grimoire/trie/tail.cc \
  grimoire/trie/louds-trie.cc

noinst_HEADERS = \
  grimoire/intrin.h \
  grimoire/io.h \
  grimoire/io/mapper.h \
  grimoire/io/reader.h \
  grimoire/io/writer.h \
  grimoire/vector.h \
  grimoire/vector/pop-count.h \
  grimoire/vector/rank-index.h \
  grimoire/vector/vector.h \
  grimoire/vector/flat-vector.h \
  grimoire/vector/bit-vector.h \
  grimoire/algorithm.h \
  grimoire/algorithm/sort.h \
  grimoire/trie.h \
  grimoire/trie/config.h \
  grimoire/trie/header.h \
  grimoire/trie/key.h \
  grimoire/trie/range.h \
  grimoire/trie/entry.h \
  grimoire/trie/tail.h \
  grimoire/trie/cache.h \
  grimoire/trie/history.h \
  grimoire/trie/state.h \
  grimoire/trie/louds-trie.h
