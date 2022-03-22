#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <sanitizer/coverage_interface.h>

#include "./trace-pc.h"

extern void
__sanitizer_cov_trace_pc_guard_init (uint32_t *start, uint32_t *stop) {
  static uint64_t N = 0;  // Counter for the guards.
  if (start == stop || *start) return;  // Initialize only once.
  printf("INIT: %p %p\n", start, stop);
  for (uint32_t *x = start; x < stop; x++)
    *x = ++N;  // Guards should start from 1.
}

extern void 
__sanitizer_cov_trace_pc_guard (uint32_t *guard) {
  if (!*guard) return;  // Duplicate the guard check.
  void *PC = __builtin_return_address(0);
  char PcDescr[1024];
  __sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr));
  printf("guard: %p %x PC %s\n", guard, *guard, PcDescr);

  if (bcov_fp != 0x0) {
     unsigned int PcD_len = (unsigned int) strlen(PcDescr); 
     fwrite(guard, 1, 8, bcov_fp);
     fwrite(&PcD_len, 1, 4, bcov_fp);
     fwrite(PcDescr, 1, PcD_len, bcov_fp);
  }
}
