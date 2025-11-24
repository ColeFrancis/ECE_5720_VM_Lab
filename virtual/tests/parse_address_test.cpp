#include <stdint.h>
#include <iostream>
#include <iomanip>

// the width of the virtual address
#define VIRTUAL_WIDTH 20
// the width of the physical address 
#define PHYSICAL_WIDTH 15
// the page size in bytes (64 in the example)
#define PAGE_SIZE 1024 
// the TLB associativity (4 in the example)
#define TLB_ASSOC 8
// the TLB size (16 in the example)
#define TLB_SIZE 16

int log2(unsigned int num) {
  if (num == 0) {
    return -1;
  }

  int count = 0;
  for (; num > 1; num >>= 1) {
    count++;
  }

  return count;
}

void parseAddress(unsigned int virtualAddress, int* tlbt, int* tlbi, int* vpn, int* po) {
  unsigned int num_po_bits = log2(PAGE_SIZE);
  unsigned int num_tlbi_bits = log2(TLB_SIZE/TLB_ASSOC);
  unsigned int num_tlbt_bits = VIRTUAL_WIDTH - num_po_bits - num_tlbi_bits;

  unsigned int po_mask = (1U << num_po_bits) - 1;
  unsigned int tlbt_mask = (1U << num_tlbt_bits) - 1;
  unsigned int tlbi_mask = (1U << num_tlbi_bits) - 1;
  unsigned int vpn_mask = (1U << (num_tlbt_bits + num_tlbi_bits)) - 1;

  *po = virtualAddress & po_mask;
  virtualAddress >>= num_po_bits;

  *vpn = virtualAddress & vpn_mask;

  *tlbi = virtualAddress & tlbi_mask;
  virtualAddress >>= num_tlbi_bits;

  *tlbt = virtualAddress & tlbt_mask;
}

int main(){
    uint32_t nums[10] = {
        0x0A3F1,  //  67185
        0x3FFFF,  // 262143
        0x54321,  // 344865
        0x0F12C,  //  61740
        0xABCDE,  // 703710
        0x13579,  //  79257
        0x7BEEF,  // 506607
        0x00001,  //      1
        0xFFFFF,  // 1,048,575 (max 20-bit)
        0x24680   // 149,760
    };

    for (int i = 0; i < 10; i++){
        int tlbt;
        int tlbi;
        int vpn;
        int po;

        parseAddress((unsigned int)nums[i], &tlbt, &tlbi, &vpn, &po);

        std::cout << "address: 0x"
                  << std::setw(5) << std::setfill('0') << std::hex << std::uppercase << nums[i]
 
                  << " TLBT: 0x"
                  << std::setw(5) << std::setfill('0') << tlbt

                  << " TLBI: 0x"
                  << std::setw(5) << std::setfill('0') << tlbi

                  << " VPN: 0x"
                  << std::setw(5) << std::setfill('0') << vpn

                  << " VPO/PPO: 0x"
                  << std::setw(5) << std::setfill('0') << po

                  << std::dec << std::endl;
    }
}