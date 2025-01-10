#include "types.h"
#include "defs.h"
#include "assert.h"
#include "riscv.h"
/* Start wanna jump here */
/* Machine-mode -> Supervisor-mode */
int main();

char stack0[4096];
void
setup_jump(void)
{
	/* Set MPP ([1:0]) to supervisor mode. */
	u64 x = r_mstatus();
	x &= ~MSTATUS_MPP_MASK;
	x |= MSTATUS_MPP_S;
	w_mstatus(x);

	/* beginning of supervisor. */
	w_mepc((u64)main);

	/* Disable paging for now. */
	w_satp(0);

	/* Give supervisor power to handle interrupts and exceptions. */
	w_medeleg(0xFFFF);
	w_mideleg(0xFFFF);
	w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);

	/* Configure physical memory protection. */
	/* Supervisor can access all of memory. */
	w_pmpaddr0(0x3FFFFFFFFFFFFFULL);
	w_pmpcfg0(0xF);

	/* Timer init. */

	/* Enable supervisor-mode timer interrupts. */
	w_mie(r_mie() | MIE_STIE);

	w_menvcfg(r_menvcfg() | (1L << 63));

	w_mcounteren(r_mcounteren() | 2);

	w_stimecmp(r_time() + 1000000);

	/* Keep each CPU's hartid in its tp register, for cpuid(). */
	w_tp(r_mhartid());

	asm volatile("mret");

}

int
kernel_main(void)
{
	setup_jump();
	/* won't arrive here. */
	/*
	uart_init();
	printf("printf: %s %s %d %d\n", "Hello", "Lemos!", 10, -100);
	assert(1);
	*/
	while (1)
		;
}
