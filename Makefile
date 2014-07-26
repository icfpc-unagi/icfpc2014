build: build/Makefile
	cd build && make -j all
.PHONY: build

build/flame-binary/%: build/Makefile
	cd build && make -j flame-binary/$*
.PHONY: build/flame-binary/%

configure: build/Makefile
.PHONY: configure

test: build build/Makefile
	cd build && make test
.PHONY: test

clean:
	rm -rf build/flame-binary
.PHONY: clean

build/Makefile:
	mkdir -p build
	cd build && \
	    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_COMPILER=clang++ ..
	cd build && cmake ..
.PHONY: build/Makefile

release:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ ..
.PHONY: release

debug:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ ..
.PHONY: debug

msan:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=msan -DCMAKE_CXX_COMPILER=clang++ ..
.PHONY: msan

usan:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=usan -DCMAKE_CXX_COMPILER=clang++ ..
.PHONY: usan

asan:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=asan -DCMAKE_CXX_COMPILER=clang++ ..
.PHONY: asan
