AM_CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion -I$(top_srcdir)/lib

noinst_LTLIBRARIES = libcmdopt.la

libcmdopt_la_SOURCES = cmdopt.cc

noinst_HEADERS = cmdopt.h

bin_PROGRAMS = \
  marisa-build \
  marisa-lookup \
  marisa-reverse-lookup \
  marisa-common-prefix-search \
  marisa-predictive-search \
  marisa-dump \
  marisa-benchmark

marisa_build_SOURCES = marisa-build.cc
marisa_build_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la

marisa_lookup_SOURCES = marisa-lookup.cc
marisa_lookup_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la

marisa_reverse_lookup_SOURCES = marisa-reverse-lookup.cc
marisa_reverse_lookup_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la

marisa_common_prefix_search_SOURCES = marisa-common-prefix-search.cc
marisa_common_prefix_search_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la

marisa_predictive_search_SOURCES = marisa-predictive-search.cc
marisa_predictive_search_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la

marisa_dump_SOURCES = marisa-dump.cc
marisa_dump_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la

marisa_benchmark_SOURCES = marisa-benchmark.cc
marisa_benchmark_LDADD = $(top_srcdir)/lib/libmarisa.la libcmdopt.la
