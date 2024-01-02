# NoS
## _The N Operating System_




## Desc.

The N Operating System. My own opersating system following the online tutorial by Write Your Own Operating System on YT (https://www.youtube.com/playlist?list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M).

## Programs needed
To be able to run the make files properly, you must have
- gcc
- g++
- binutils
- libc6-dev-i386

If you're on linux this can be installed with 
``` sh
sudo apt install g++ gcc binutils libc6-dev-i386
```

## Compiling the kernel binary
To compile mykernel.bin, just type
``` sh
make
```
in the terminal in the directory of NoS. The makefile will create all the .o files needed and the resulting .bin file. This is the kernel.

## Booting from Virtual Box
To compile an ISO and boot from the Virtual Box, make sure you have the following package
``` sh
sudo apt install xorriso mtools
```
and that you have Virtual Box installed on our machine (obviously).
Once all is installed, type
``` sh
make mykernel.iso
```
to create the initial iso file needed.

Next, go into Virtual Box and create a new machine. It's name should be NoS, the type is other, and the verison is other/unkown (not the 64-bit version).
As of 12-27-2023 64 MB of memory is fine, and there is no virtual hard disk needed.

You now have the machine, and must now select mykernel.iso to be loaded. In the settings of NoS, select storage, and then click the empty CD icon. In the attributes section on the right, select the disk icon next to Optical Drive and choose a disk file. Navigate to where mykernel.iso was created, select it, and select ok.

Now to run the machine simply press start; or in the directory with all the files and makefile, open the terminal and type

``` sh
make run
```

which will issue a command from the command line and open NoS.

## Booting from Bare Metal
To boot from bare metal, we must first add mykernel.bin to the boot directory. NOTE: This step requires your password. Run 
``` sh
make install
```
in the terminal in the NoS directory. You will be prompted to type in your password. This process copies mykernel.bin into your boot directory. The next step is to tell GRUB about the bin.
To inform GRUB of mykernel.bin, open _/boot/grub/grub.cfg_ in your favourite editor. Scroll to the very bottom and add

``` sh 
### BEGIN MYKERNEL ###
menuentry 'N Operating System' {
        multiboot /boot/mykernel.bin
        boot
}
###END MYKERNEL ###
```

to the end of the file.

**NOTE** This only works for people with an Intel CPU as it's expecting an i836 archticture.

## Bugs

## License

GPL 3.0 License

