all: go python c cpp rust

define check_program
	if [ ! -z `which $(1)` ]; then \
		echo "$(1) is installed"; \
	else \
	    echo "$(1) is not installed"; exit 1; \
	fi
endef

check: check-go check-python check-c check-cpp check-rust

go: check-go
	GO111MODULE=auto CGO_ENABLED=0 go test -v --bench . --benchmem --timeout 0

check-go:
	@$(call check_program,go)

python: check-python
	python3 -m unittest sort.TestMergeSort
	@rm -r __pycache__
	python3 sort.py

check-python:
	@$(call check_program,python3)

c: check-c
	gcc sort.c -o sort
	./sort
	valgrind --leak-check=yes ./sort
	rm sort

check-c:
	@$(call check_program,gcc)
	@$(call check_program,valgrind)

cpp: check-cpp
	g++ sort.cpp -o sort
	./sort
	valgrind --track-origins=no --leak-check=yes ./sort
	rm sort

check-cpp:
	@$(call check_program,g++)
	@$(call check_program,valgrind)

rust: check-rust
	rustc sort.rs --extern rand
	./sort
	rm sort

check-rust:
	@$(call check_program,rustc)
