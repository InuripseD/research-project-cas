.PHONY: all clean cas-db tests server benchmarks

all: cas-db tests server benchmarks

cas-db:
	$(MAKE) -C cas-db

tests:
	$(MAKE) -C tests

server:
	$(MAKE) -C server

benchmarks:
	$(MAKE) -C benchmarks

clean:
	$(MAKE) -C cas-db clean
	$(MAKE) -C tests clean
	$(MAKE) -C server clean
	$(MAKE) -C benchmarks clean
