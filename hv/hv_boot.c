#define EXCP_INST_ADDR_MIS     (0)
#define EXCP_INST_ACC_FAULT    (1)
#define EXCP_ILLEGAL_INST      (2)
#define EXCP_BREAKPOINT        (3)
#define EXCP_LOAD_ADDR_MIS     (4)
#define EXCP_LOAD_ACC_FAULT    (5)
#define EXCP_ST_AMO_ADDR_MIS   (6)
#define EXCP_ST_AMO_ACC_FAULT  (7)
#define EXCP_U_ECALL           (8)
#define EXCP_S_ECALL           (9)
#define EXCP_M_ECALL           (11)
#define EXCP_INST_PAGE_FAULT   (12)
#define EXCP_LOAD_PAGE_FAULT   (13)
#define EXCP_ST_AMO_PAGE_FAULT (15)



void hv_boot()
{
  volatile asm ("csrw hedeleg %0" :
                1 << EXCP_INST_ADDR_MIS |
                1 << EXCP_BREAKPOINT |
                1 << EXCP_U_ECALL |
                1 << EXCP_INST_PAGE_FAULT |
                1 << EXCP_LOAD_PAGE_FAULT |
                1 << EXCP_ST_AMO_PAGE_FAULT);

  volatile asm ("csrw hideleg %0" :
                1 << INT_V_EXTERNAL |
                1 << INT_V_TIMER    |
                1 << INT_V_SOFTWARE);

  volatile asm ("csrw hvip, zero");

  config_guest();
  switch_to_guest ();
}
