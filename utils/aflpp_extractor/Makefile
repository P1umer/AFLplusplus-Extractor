ifeq "" "$(LLVM_CONFIG)"
  LLVM_CONFIG=llvm-config
endif

ifeq "$(shell uname -s)" "Darwin"
  # On some odd MacOS system configurations, the Xcode sdk path is not set correctly
  SDK_LD = -L$(shell xcrun --show-sdk-path)/usr/lib
  LDFLAGS += $(SDK_LD)
endif

ifeq "" "$(LLVM_CONFIG)"
  LLVM_CONFIG := llvm-config
endif
LLVM_BINDIR = $(shell $(LLVM_CONFIG) --bindir 2>/dev/null)
ifneq "" "$(LLVM_BINDIR)"
  ifeq "$(shell test -x $(LLVM_BINDIR)/clang && echo 1)" "1"
    CC := $(LLVM_BINDIR)/clang
  endif
endif
CC := clang
CFLAGS := -O3 -funroll-loops -g -fPIC

all:    libAFLExtractor.a  reproducer

extractor.o: extractor.c
	-$(CC) -I. -I../../include $(CFLAGS) -c extractor.c

extractor_test.o: extractor_test.c
	-$(CC) -I. -I../../include $(CFLAGS) -c extractor_test.c

libAFLExtractor.a:      extractor.o
	@ar rc libAFLExtractor.a extractor.o
	# @cp -vf libAFLExtractor.a ../../

libExtractorTest.a:     extractor_test.o
	@ar rc libExtractorTest.a extractor_test.o

reproducer: libAFLExtractor.a libExtractorTest.a
	/Users/p1umer/Git/AFLplusplus/afl-clang-fast -D_DEBUG=\"1\" -I../../include -Wl -funroll-loops -o reproducer libExtractorTest.a libAFLExtractor.a reproducer.c

clean:
	rm -f *.o *.a *~ core reproducer