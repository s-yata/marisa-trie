ALL: swig-perl swig-python3 swig-ruby

swig-perl:
	swig -Wall -c++ -perl -outdir perl marisa-swig.i
	mv marisa-swig_wrap.cxx perl
	cp marisa-swig.cxx marisa-swig.h perl

swig-python:
	swig -Wall -c++ -python -outdir python marisa-swig.i
	mv marisa-swig_wrap.cxx python
	cp marisa-swig.cxx marisa-swig.h python

swig-python3:
	swig -Wall -c++ -python -outdir python3 marisa-swig-python3.i
	mv marisa-swig-python3_wrap.cxx python3
	cp marisa-swig-python3.cxx marisa-swig-python3.h python3

swig-ruby:
	swig -Wall -c++ -ruby -outdir ruby marisa-swig.i
	mv marisa-swig_wrap.cxx ruby
	cp marisa-swig.cxx marisa-swig.h ruby
