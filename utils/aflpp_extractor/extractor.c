// Copyright 2023 P1umer
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <signal.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "extractor.h"

// libFuzzer interface is thin, so we don't include any libFuzzer headers.
__attribute__((weak)) int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
__attribute__((weak)) int LLVMFuzzerInitialize(int *argc, char ***argv){
  // Default implementation does nothing
  return 0;
}

#define INITIAL_SIZE (100)
#define MAX_LENGTH(x, y) ( ((x) > (y)) ? (x) : y )

// #define kMaxAflInputSize (1 * 1024 * 1024)
// static uint8_t AflInputBuf[kMaxAflInputSize];
static mutate_helper_t* afl_mutate_helper;

void fake_init() {
    int fake_argc = 3;

    char *fake_argv_arr[] = {
        "fake1",
        "fake2",
        "fake3"
    };

    char **fake_argv = malloc(fake_argc * sizeof(char *));
    if (!fake_argv) {
        perror("Failed to allocate memory for fake_argv");
        // return 1;
    }

    for (int i = 0; i < fake_argc; i++) {
        fake_argv[i] = fake_argv_arr[i];
    }
    if (LLVMFuzzerInitialize) {
        LLVMFuzzerInitialize(&fake_argc, &fake_argv);
    }
}

void mutate_helper_init() {
    afl_mutate_helper = (mutate_helper_t *)calloc(1, sizeof(mutate_helper_t));
    afl_mutate_helper->len = INITIAL_SIZE;
    afl_mutate_helper->buf = (uint8_t *)calloc(1, afl_mutate_helper->len);
    if (!afl_mutate_helper->buf) perror("mutate_helper_init");
    fake_init();
}

size_t mutate_helper_generate(unsigned char *buf, size_t buf_size) {
    return LLVMFuzzerTestOneInput(buf, buf_size);
}

void mutate_helper_realloc_buf(size_t length) {

    if (afl_mutate_helper->len <= length) {
        // double length
        size_t old_length = afl_mutate_helper->len;
        afl_mutate_helper->len = length * 2;
        afl_mutate_helper->buf = (uint8_t *)realloc(afl_mutate_helper->buf, afl_mutate_helper->len);
        if (!afl_mutate_helper->buf) {
            perror("mutate_helper_realloc");
            return;
        }
    }

    memset(afl_mutate_helper->buf, 0, afl_mutate_helper->len);
}

void mutate_helper_buffer_copy(unsigned char *buf, size_t buf_size){
    mutate_helper_realloc_buf(buf_size);
    // Clear only the newly allocated portion of the buffer
    memcpy(afl_mutate_helper->buf, buf, buf_size);

}

uint8_t* mutate_helper_buffer(){
    return afl_mutate_helper->buf;
}

size_t mutate_helper_buffer_size(){
    return afl_mutate_helper->len;
}

#undef MAX_LENGTH
#undef INITIAL_SIZE

