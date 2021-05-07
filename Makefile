all: go python

go:
	GO111MODULE=auto go test -v --bench . --benchmem --timeout 0

python:
	python3 -m unittest sort.TestMergeSort
	@rm -r __pycache__
	python3 sort.py
