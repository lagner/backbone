

.PHONY: clean prepare conan-install build

clean:
	rm -rf build

conan-install:
	conan install . --install-folder=build --profile=clang --build=missing

run:
	QT_QPA_FONTDIR=/usr/share/fonts/truetype/ubuntu ./build/bin/TestApp

build:
	cmake --build ./build --target all
