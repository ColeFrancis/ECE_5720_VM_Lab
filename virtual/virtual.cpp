
#include<stdio.h> //printf
#include<math.h>  //log2
#include<stdlib.h>//strtol

#include "constants.h"

// pretty print TLB, included for help with debugging
void printTLB() {
  printf("TLB: \n");
  // print headers
  printf("%4s|", "Set");
  for (int set = 0; set < TLB_ASSOC; set++)
    printf("%3s %4s %5s|", "Tag", "PPN", "Valid");
  // print set
  printf("\n");
  for (int set = 0; set < TLB_SIZE/TLB_ASSOC; set++) {
    printf("%3d |", set);
    // print entries
    for (int entry = 0; entry < TLB_ASSOC; entry++) {
      printf(" %02x   %02x  %3d |", tlb[set][entry].tag, 
          tlb[set][entry].ppn, tlb[set][entry].valid);
    }
    printf("\n");
  }
  printf("\n");
}

// print page table, can be used in debugging if desired
void printPageTable() {
  printf("Page Table:\nVPN  PPN Valid\n");
  for (int i = 0; i < 16; i++) {
    printf(" %02x | %02x %1d |\n", i, pageTable[i], pageTableValid[i]);
  }
  printf("\n");
}

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
 
// translates virtual address to physical address
int translate(int virtualAddress) {
  // TODO: implement address translation (insert code here)

  int tlbt;
  int tlbi;
  int vpn;
  int po;
  int ppn;

  parseAddress((unsigned int)virtualAddress, &tlbt, &tlbi, &vpn, &po);



  int physicalAddress = 0;

  return physicalAddress;
}

// main function
int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("requries virtual address in HEX as argument!\n");
    return 0;
  }
  // set up TLB and page table (in constants.cpp)
  setupConstants();

  //take input address and parse it as a hexadecimal number
  int inputAddress = (int)strtol(argv[1], NULL, 16);

  //translate to a physical address and print results
  printf("Physical address: %x \n", translate(inputAddress));

  return 0;
}
