#include "common.h"

char __license[] __section("license") = "Dual MIT/GPL";

extern void bpf_testmod_test_mod_kfunc(int) __ksym;

__section("tc") int call_kfunc() {
	bpf_testmod_test_mod_kfunc(0);
	return 1;
}

extern void bpf_kfunc_common_test() __weak __ksym;

__section("tc") int call_weak_kfunc() {
	if (bpf_ksym_exists(bpf_kfunc_common_test)) {
		bpf_kfunc_common_test();
		return 1;
	}
	return 0;
}
