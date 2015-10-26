.PHONY: test
.PHONY: sample
.PHONY: static

build:
	 node-gyp configure && node-gyp build

build-debug:
	 node-gyp configure -debug && node-gyp build

test:
	 node-gyp configure -debug && node-gyp build && ./build/Debug/test

xcode-proj:
	node-gyp configure -- -f xcode

clean:
	node-gyp clean
