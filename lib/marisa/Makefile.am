SUBDIRS = grimoire

MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion $(MY_INCLUDE)

lib_LTLIBRARIES = libmarisa.la

libmarisa_la_LDFLAGS = -no-undefined

libmarisa_la_LIBADD = \
  grimoire/io/libio.la \
  grimoire/trie/libtrie.la \
  grimoire/vector/libvector.la

libmarisa_la_SOURCES = \
  keyset.cc \
  agent.cc \
  trie.cc
