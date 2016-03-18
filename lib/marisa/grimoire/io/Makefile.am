MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion $(MY_INCLUDE)

noinst_LTLIBRARIES = libio.la

libio_la_LDFLAGS = -no-undefined

libio_la_SOURCES = \
  mapper.cc \
  reader.cc \
  writer.cc

noinst_HEADERS = \
  mapper.h \
  reader.h \
  writer.h
