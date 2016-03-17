MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion $(MY_INCLUDE)

noinst_LTLIBRARIES = libgrimoire.la

libgrimoire_la_SOURCES = \
  io/mapper.cc \
  io/reader.cc \
  io/writer.cc \
  vector/bit-vector.cc \
  trie/tail.cc \
  trie/louds-trie.cc

noinst_HEADERS = \
  intrin.h \
  io.h \
  io/mapper.h \
  io/reader.h \
  io/writer.h \
  vector.h \
  vector/pop-count.h \
  vector/rank-index.h \
  vector/vector.h \
  vector/flat-vector.h \
  vector/bit-vector.h \
  algorithm.h \
  algorithm/sort.h \
  trie.h \
  trie/config.h \
  trie/header.h \
  trie/key.h \
  trie/range.h \
  trie/entry.h \
  trie/tail.h \
  trie/cache.h \
  trie/history.h \
  trie/state.h \
  trie/louds-trie.h
