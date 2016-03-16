LIB_DIR = $(top_srcdir)/lib

AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion -D_DEBUG -I$(LIB_DIR)

TESTS = \
  base-test \
  io-test \
  vector-test \
  trie-test \
  marisa-test

check_PROGRAMS = $(TESTS)

noinst_HEADERS = marisa-assert.h

base_test_SOURCES = base-test.cc
base_test_LDADD = $(LIB_DIR)/libmarisa.la

io_test_SOURCES = io-test.cc
io_test_LDADD = $(LIB_DIR)/libmarisa.la

vector_test_SOURCES = vector-test.cc
vector_test_LDADD = $(LIB_DIR)/libmarisa.la

trie_test_SOURCES = trie-test.cc
trie_test_LDADD = $(LIB_DIR)/libmarisa.la

marisa_test_SOURCES = marisa-test.cc
marisa_test_LDADD = $(LIB_DIR)/libmarisa.la
