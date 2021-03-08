typedef uint64_t addr_t;
typedef uint64_t phys_addr_t;

static addr_t base_addr;
static bool initialized;
static int64_t last_index = 0;

void paging_init()
{
  uint64_t base_addr = (elf_end() & !0xfff) + 4096;
  initialized = true;
  last_index = 0;
}

phys_addr_t paging_alloc()
{
  if (!initialized) {
    fatal("page manager is not initialized");
  }
  last_index += 1;
  addr_t addr = base_addr + PAGE_SIZE * (last_index - 1);
  if (addr > DRAM_END) {
    fatal("memory exausted; 0x%016lx\n", addr);
  }

  phys_addr_t p_addr = new Page_from_address(new PhysacalAddress(addr));
  memory_clear (p);
  return p;
}


void memory_clear (phys_addr_t p_addr)
{
  for(int i = 0; i < PAGE_SIZE / sizeof(uint64_t); i++) {
    (volatile uint64_t *(p_addr)) = 0;
    p_addr ++;
  }
}


phys_addr_t resolve (vir_addr_t vaddr, phys_addr_t pt, int level)
{
  int vpn = get_vpn(vaddr, level);
  pte_t entry = get_entry(pt, vpn);
  if (!pte_is_valid (entry)) {
    fatal("failed to resolve vaddr %016lx\n", vaddr);
  }
  if (level == 0) {
    addr_base = entry.next_page();
    return addr_base + vaddr & 0xfff;
  } else {
    phys_addr_t entry.next_page();
    phys_addr_t new_pt = next_page;
    resolve (vaddr, new_pt, level-1);
  }
}
