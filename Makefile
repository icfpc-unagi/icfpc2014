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
	cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	cd build && cmake ..
.PHONY: build/Makefile

release:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release ..
.PHONY: release

debug:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
.PHONY: debug

msan:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=msan ..
.PHONY: msan

usan:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=usan ..
.PHONY: usan

asan:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=asan ..
.PHONY: asan
