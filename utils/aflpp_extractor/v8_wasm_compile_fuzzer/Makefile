ifeq "" "$(LLVM_CONFIG)"
  LLVM_CONFIG=llvm-config
endif

ifeq "$(shell uname -s)" "Darwin"
  # On some odd MacOS system configurations, the Xcode sdk path is not set correctly
  SDK_LD = -L$(shell xcrun --show-sdk-path)/usr/lib
  LDFLAGS += $(SDK_LD)
endif

CC := clang
CFLAGS := -O3 -funroll-loops -g -fPIC

all:    v8_reproducer

v8_reproducer:
	$(CC) -I../ -I../../include -Wl -funroll-loops -o v8_reproducer $(V8_BUILD_PATH)/v8_wasm_compile_fuzzer $(AFL_PATH)/libAFLExtractor.a ../reproducer.c

clean:
	rm -f *.o *.a *~ v8_reproducer
