#if __riscv_xlen == 64
# define STORE    sd
# define LOAD     ld
# define REGBYTES 8
#else
# define STORE    sw
# define LOAD     lw
# define REGBYTES 4
#endif

#define STACK_TOP (_end + 4096)
#define SIZEOF_TRAPFRAME_T ((__riscv_xlen / 8) * 36)

    .section    .text.init
    .globl  _start

_start:
    la    t0, trap_vector
    csrw  mtvec, t0
    la    sp, STACK_TOP - SIZEOF_TRAPFRAME_T
    csrr  t0, mhartid
    slli  t0, t0, 12
    add   sp, sp, t0
    csrw  mscratch, sp
    j     hv_boot
