all: go python c

go:
	GO111MODULE=auto CGO_ENABLED=0 go test -v --bench . --benchmem --timeout 0

python:
	python3 -m unittest sort.TestMergeSort
	@rm -r __pycache__
	python3 sort.py

c:
	gcc sort.c -o sort
	./sort
	valgrind --leak-check=yes ./sort
	rm sort
