// REQUIRES: thumbv8m.base
// UNSUPPORTED: thumbv8m.main
// RUN: %cc% %ccflags% %ccout% %s.o %s; llvm-objdump --mcpu=%mcpu% -d %s.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cmsis_compiler.h"

void get_psplim() {
    // CHECK-LABEL: <get_psplim>:
    // CHECK-S: mrs {{r[0-9]+}}, psplim
    // CHECK-NS-NOT: mrs {{r[0-9]+}}, psplim
    volatile uint32_t result = __get_PSPLIM();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void get_psplim_ns() {
    // CHECK-LABEL: <get_psplim_ns>:
#if __ARM_FEATURE_CMSE == 3
    // CHECK-S-NOT: mrs {{r[0-9]+}}, psplim_ns
    volatile uint32_t result = __TZ_get_PSPLIM_NS();
#endif
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void set_psplim() {
    // CHECK-LABEL: <set_psplim>:
    // CHECK-S: msr psplim, {{r[0-9]+}}
    // CHECK-NS-NOT: msr psplim, {{r[0-9]+}}
    __set_PSPLIM(0x0815u);
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void set_psplim_ns() {
    // CHECK-LABEL: <set_psplim_ns>:
#if __ARM_FEATURE_CMSE == 3
    // CHECK-S-NOT: msr psplim_ns, {{r[0-9]+}}
     __TZ_set_PSPLIM_NS(0x0815u);
#endif
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}
