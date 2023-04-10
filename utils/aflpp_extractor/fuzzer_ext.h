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
typedef struct mutate_helper {
    uint8_t *buf;
    size_t len;
} mutate_helper_t;

#ifdef __cplusplus
extern "C" {
#endif
    extern void mutate_helper_buffer_copy(unsigned char *buf, size_t buf_size);
#ifdef __cplusplus
}
#endif 