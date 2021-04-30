all: go

go:
	GO111MODULE=auto go test -v --bench . --benchmem --timeout 0
