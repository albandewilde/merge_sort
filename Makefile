all: go

go:
	@GO111MODULE=off
	go test -v --bench . --benchmem --timeout 0
