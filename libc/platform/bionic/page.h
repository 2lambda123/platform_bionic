/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sys/auxv.h>

// For PAGE_SIZE.
#include <sys/user.h>

inline size_t page_size() {
  /*
   * PAGE_SIZE defines the maximum supported page size. Since 4096 is the
   * minimum supported page size we can just let it be constant folded if it's
   * also the maximum.
   */
#if PAGE_SIZE == 4096
  return PAGE_SIZE;
#else
  static size_t size = getauxval(AT_PAGESZ);
  return size;
#endif
}

// Returns the address of the page containing address 'x'.
inline uintptr_t page_start(uintptr_t x) {
  return x & ~(page_size() - 1);
}

// Returns the offset of address 'x' in its page.
inline uintptr_t page_offset(uintptr_t x) {
  return x & (page_size() - 1);
}

// Returns the address of the next page after address 'x', unless 'x' is
// itself at the start of a page.
inline uintptr_t page_end(uintptr_t x) {
  return page_start(x + page_size() - 1);
}
