void load_from_disk()
{
  uint64_t load_size = 1024 * 1024 * 2;
  phys_addr_t buf_page = page_alloc_continuous(load_size / PAGE_SIZE);

  phys_addr_t gpat_pt = (hgatp.ppn << 12);

  // set SEPC to entrypoint when sret?
  sepc = entrypoint();

  phys_addr_t start_page_head = s.sh_addr() >> 12 << 12;
  phys_addr_t end_page_head   = (s.sh.addr() + s.sh.size()) >> 12 << 12;
  int last_idx = (end_page_head - start_page_head) / PAGE_SIZE;
  int seek = s.sh.addr & 0xfff;

  for (int i = 0; i < last_idx; i++) {
    dest_base_vaddr = start_page-head + i * PAGE_SIZE;
    dest_addr = resolve (dest_base_vaddr, gpat_pt, 2) + seek % PAGE_SIZE;
    src_addr = buf_addr(s.sh.offset()) + (seek - (s.sh.addr() & 0xfff));
    copy_size = min(PAGE_SIZE, ...);
    memcpy(dest_addr, src_addr, copy_size);
  }
}
