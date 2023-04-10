// Copyright 2023 P1umer

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "afl_ext.h"

int main(int argc, char* argv[]) {

  mutate_helper_init();

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <input> <output>\n", argv[0]);
    return 1;
  }

  FILE* input = fopen(argv[1], "rb");

  if (!input) {
    fprintf(stderr, "Failed to open '%s'\n", argv[1]);
    return 1;
  }

  fseek(input, 0, SEEK_END);
  size_t size = ftell(input);
  fseek(input, 0, SEEK_SET);

  uint8_t* data = (uint8_t*)(malloc(size));
  if (!data) {
    fclose(input);
    fprintf(stderr, "Failed to allocate %zu bytes\n", size);
    return 1;
  }

  size_t bytes_read = fread(data, 1, size, input);
  fclose(input);

  if (bytes_read != (size_t)(size)) {
    free(data);
    fprintf(stderr, "Failed to read %s\n", argv[1]);
    return 1;
  }

  printf("[+] prev data: %s\n", data);

  mutate_helper_generate(data, size);
  int result = mutate_helper_buffer_size();
  uint8_t* transfer =  mutate_helper_buffer();
  
  printf("[+] result data: %d\n %s\n", result,transfer);

  FILE* output=fopen(argv[2],"wb");
  fwrite(transfer, 1,result, output);

  free(data);

  // MutateHelper_C_delete();

  return result;
}