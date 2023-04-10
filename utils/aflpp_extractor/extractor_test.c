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
#include <string.h>

// Simple target function to check if input contains "++".
int target_function(const uint8_t *data, size_t size) {
  for (size_t i = 0; i < size - 1; ++i) {
    if (data[i] == '+' && data[i + 1] == '+') {
      return 1;
    }
  }
  return 0;
}

#include "fuzzer_ext.h"

// libFuzzer's required entry point.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t new_size = size + 2; // Adding 2 for "++"
  uint8_t *modified_data = (uint8_t *)malloc(new_size);
  memcpy(modified_data, data, size);
  modified_data[size] = '+';
  modified_data[size + 1] = '+';

// extractor start

  mutate_helper_buffer_copy(modified_data, size + 2);

// extractor end

  // int result = target_function(modified_data, new_size);

  free(modified_data);
  // return result;
  return 0;
}


