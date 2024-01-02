#include "types.h"
#include "gdt.h"

void printf(char* str){

  static uint16_t* VideoMemory = (uint16_t*)0xb8000;

  static uint8_t x=0, y=0; //cursor for where we are in video memory (starts at the top left)

  for(int i = 0; str[i] != '\0'; ++i){

    switch(str[i])
    {
      case '\n': //if new line character
        y++; //increment vertical line
        x=0; //reset horizontal
        break;
      default:
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
        x++;
        break;
    }

    if(x >= 80){ //if cursor is now off right screen
      y++; //line feed
      x=0; //reset cursor left
    }

    if(y >= 25){ //if the screen is full, move everything up one line

      for(y = 0; y < 24; y++) //from the top of the screen to the second last line
        for(x = 0; x < 80; x++)
          VideoMemory[80*y+x] = (VideoMemory[80*(y)+x] & 0xFF00) | VideoMemory[80*(y+1)+x]; //make the current line whatever the next line is

      x=0; //reset cursor left
      y = 24; //reset cursor to bottom of screen
    }

  }
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){

  for(constructor* i = &start_ctors; *i != end_ctors; *i++)
    (*i)();
}

extern "C" void kernel_main(const void* multiboot_structure, uint32_t magic_number){

    printf("Hello world - shiftedgears.github.io\n");
    
    GlobalDescriptorTable gdt; //instantiate the GDT

    while(1); //leep the kernel active
    
}
