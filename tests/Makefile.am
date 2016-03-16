MY_INCLUDE = -I$(top_srcdir)/include -I$(top_srcdir)/lib
MY_LIBS = $(top_srcdir)/lib/marisa/libmarisa.la

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion -D_DEBUG $(MY_INCLUDE)

TESTS = \
  base-test \
  io-test \
  vector-test \
  trie-test \
  marisa-test

check_PROGRAMS = $(TESTS)

noinst_HEADERS = marisa-assert.h

base_test_SOURCES = base-test.cc
base_test_LDADD = $(MY_LIBS)

io_test_SOURCES = io-test.cc
io_test_LDADD = $(MY_LIBS)

vector_test_SOURCES = vector-test.cc
vector_test_LDADD = $(MY_LIBS)

trie_test_SOURCES = trie-test.cc
trie_test_LDADD = $(MY_LIBS)

marisa_test_SOURCES = marisa-test.cc
marisa_test_LDADD = $(MY_LIBS)
