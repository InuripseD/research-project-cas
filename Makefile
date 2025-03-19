.PHONY: all clean cas-db tests benchmarks

all: create_dirs cas-db tests benchmarks

create_dirs:
	mkdir -p obj bin

cas-db:
	$(MAKE) -C cas-db

tests:
	$(MAKE) -C tests

benchmarks:
	$(MAKE) -C benchmarks

# server:
# 	$(MAKE) -C server

clean:
	$(MAKE) -C cas-db clean
	$(MAKE) -C tests clean
	$(MAKE) -C benchmarks clean
