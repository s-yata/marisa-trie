MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion $(MY_INCLUDE)

noinst_LTLIBRARIES = libtrie.la

libtrie_la_LDFLAGS = -no-undefined

libtrie_la_SOURCES = \
  tail.cc \
  louds-trie.cc

noinst_HEADERS = \
  config.h \
  header.h \
  key.h \
  range.h \
  entry.h \
  tail.h \
  cache.h \
  history.h \
  state.h \
  louds-trie.h
