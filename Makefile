.PHONY: build
.PHONY: build-other
.PHONY: test
.PHONY: sample

build:
	 ./node_modules/.bin/node-gyp rebuild

build-other:
	./node_modules/node-gyp/gyp/gyp_main.py --generator-output=./build --depth=. -f ninja other.gyp
	ninja -C build/out/Default -f build.ninja

test: build-other
	./build/out/Default/test || [ $$? -eq 0 ]

sample: build-other
	./build/out/Default/sample

xcode-proj:
	./node_modules/node-gyp/gyp/gyp_main.py --generator-output=./build --depth=. -f xcode other.gyp

clean:
	rm -Rf build
