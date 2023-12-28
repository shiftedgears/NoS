#ifndef __GDT_H
#define __GDT_H

#include "types.h"

    class GlobalDescriptorTable
    {

    public:
        class SegmentDescriptor
        {
        private:
            uint16_t limit_lo; //low bytes limit
            uint16_t base_lo; //low bytes of the pointer
            uint8_t base_hi; //one byte extension for pointer
            uint8_t type; //excess bytes
            uint8_t flags_limit_hi; //flag bytes
            uint8_t base_vhi;

        public:
            SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
            uint32_t Base();
            uint32_t Limit();




        } __attribute__ ((packed)); //makes sure this class is laid out exactly as we described, as we need it to be byte perfect

        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        uint16_t CodeSegmentSelector(); //gets offset of code segment selector
        uint16_t DataSegmentSelector(); //and one for data segment

    };

#endif
