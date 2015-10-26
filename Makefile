.PHONY: test
.PHONY: sample

sample:
	 node-gyp configure && node-gyp build && ./build/Release/sample

test:
	 node-gyp configure -debug && node-gyp build && ./build/Debug/test

xcode-proj:
	node-gyp configure -- -f xcode

clean:
	node-gyp clean
