
void printf(char* str){ //our own printf function

  unsigned short* VideoMemory = (unsigned short*)0xb8000;//start at the buffer beginning

  for(int i = 0; str[i] != '\0'; ++i)
    VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i]; //copy the high signal concatenated with the character to the video memory
  
}

//extern "C" is to make the function name explicit so that assembler can find it
extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number){

    printf("Hello world");
    
    while(1);
    
}
