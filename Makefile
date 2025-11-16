.PHONY: all clean test coverage cpp-test go-test cpp-build

all: test

# C++ тесты
cpp-build:
	mkdir -p build
	cd build && cmake .. && make

cpp-test: cpp-build
	cd build && ./run_tests

cpp-coverage: cpp-test
	cd build && lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
	cd build && lcov --remove coverage.info '/usr/*' '_deps/*' --output-file coverage.info --ignore-errors inconsistent
	cd build && genhtml coverage.info --output-directory coverage_html

# Go тесты
go-test:
	cd go && go test -v

go-coverage:
	cd go && go test -coverprofile=coverage.out
	cd go && go tool cover -html=coverage.out -o coverage.html
	@echo "Coverage report generated in go/coverage.html"

go-bench:
	cd go && go test -bench=. -benchmem

# Все тесты
test: cpp-test go-test

coverage: cpp-coverage go-coverage

clean:
	rm -rf build
	cd go && rm -f coverage.out coverage.html
