ifeq ($(OS),Windows_NT)
    EXE = cmake-build-debug/Debug/vorschau.exe
else
    EXE = cmake-build-debug/vorschau
endif

all: deps configure build run

deps:
	git submodule update --init --recursive

configure:
	cmake -S . -B cmake-build-debug

build:
	cmake --build cmake-build-debug --target vorschau

run:
	$(EXE)

clean:
	rm -rf cmake-build-debug compile_commands.json

add:
	git status
	git add CMakeLists.txt Makefile README.md src/*.c
	git status
