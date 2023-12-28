#include "types.h"
#include "gdt.h"

void printf(char* str){

  static uint16_t* VideoMemory = (uint16_t*)0xb8000;

  for(int i = 0; str[i] != '\0'; ++i)
    VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
  
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){

  for(constructor* i = &start_ctors; *i != end_ctors; *i++)
    (*i)();
}

extern "C" void kernel_main(const void* multiboot_structure, uint32_t magic_number){

    printf("Hello world - shiftedgears.github.io");
    
    GlobalDescriptorTable gdt; //instantiate the GDT

    while(1); //leep the kernel active
    
}
