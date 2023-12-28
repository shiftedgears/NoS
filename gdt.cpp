#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0, 0, 0),
unusedSegmentSelector(0, 0, 0),
codeSegmentSelector(0, 64*1024*1024, 0x9A), //last is flags
dataSegmentSelector(0, 64*1024*1024, 0x92)
{

    uint32_t i[2];
    i[0] = (uint32_t)this; //first byte is the global descriptor table itself
    i[1] = sizeof(GlobalDescriptorTable) << 16; //second byte is the size of the GDT shifted right

    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i) +2)); //one line of assembler code. load the global descriptor table

}


GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16_t GlobalDescriptorTable::DataSegmentSelector()//offset of data selector segment
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector()//offset of code selector segment
{
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags){ //assigning info to bytes in the segment

    uint8_t* target = (uint8_t*)this;

    if(limit <= 65536){ //small limit
        target[6] = 0x40; //tells process this is a 16 bit entry
    }
    else{
        if((limit & 0xFFF) != 0xFFF) //if the limit is not all 1's
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;

        target[6] = 0xC0; //not in 16 bit
    }

    //now must distribute things around

    target[0] = limit & 0xFF; //assign 1 out of the 2 and 1/2 bytes of the target
    target[1] = (limit >> 8) & 0xFF; //assign next byte
    target[6] |= (limit >> 16) & 0xF; //assign half of the byte at index 6

    //now encode pointer to start
    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    //now set access rights
    target[5] = flags;

    //we now have a single entry in the table with the start pointer, flags, limits
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base(){ //retrieve the base from a segment

    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit(){ //retrieve the limit from a segment

    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xF; //retrieve the low limits from shared byte
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF; //only if it is not 16 bits

    return result;
}


