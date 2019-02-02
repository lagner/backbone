

.PHONY: clean prepare conan-install

clean:
	rm -rf build

conan-install:
	conan install . --install-folder=build --profile=clang --build=missing
