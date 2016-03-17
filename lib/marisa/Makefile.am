SUBDIRS = grimoire

MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion $(MY_INCLUDE)

lib_LTLIBRARIES = libmarisa.la

libmarisa_la_LIBADD = grimoire/libgrimoire.la

libmarisa_la_SOURCES = \
  keyset.cc \
  agent.cc \
  trie.cc
