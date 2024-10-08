
#include "memory_management_unit.h"
#include "student_code.h"

MMU MMU__pagetable__init() {
  MMU m = {
    .page_pointer = calloc(NUM_PAGES, sizeof(PageTableEntry)),
    .physical_memory = calloc(NUM_FRAMES, PAGE_SIZE),
    .page_used = calloc(NUM_FRAMES, sizeof(bool)),

      // simple specific functions
    .get_pagetableentry = get_pagetableentry__MMU_pagetable,
    .map_page = map_page__MMU_pagetable,
  };
  return m;
}

AddressMask get_mask(unsigned int num_bits_to_mask) {
  AddressMask base = 0;
  base = ~base; // Invert all bits so they are all 1s
  return (base >> (NUM_BITS_IN_BYTE*sizeof(AddressBasis) - num_bits_to_mask)); // Shift all bits to the right until we are left with only the mask we want
}

AddressMask get_mask_single_bit(unsigned int bit_to_mask) {
  if (bit_to_mask == 0) {
    return 0;
  }
  if (bit_to_mask == 1) {
    return 1;
  }
  return get_mask(bit_to_mask) - get_mask(bit_to_mask-1);
}

bool is_bit_set(PageTableEntry pte, unsigned int bit_number) {
  AddressBasis mask = get_mask_single_bit(bit_number);
  return (pte & mask) != 0;
}

void MMU_destroy(MMU m) {
  free(m.page_pointer);
  free(m.physical_memory);
  free(m.page_used);
  // Question: if we have one big MMU unit that we initialize like in PA3, why do we need to free individual parts here?
}
