# NoS
## _The N Operating System_




## Desc.

The N Operating System. My own opersating system following the online tutorial by Write Your Own Operating System on YT (https://www.youtube.com/playlist?list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M).

## Programs needed
To be able to run the make files properly, you must have
- g++
- binutils
- libc6-dev-i386

If you're on linux this can be installed with 
``` sh
sudo apt install g++ binutils libc6-dev-i386
```

## Compiling the kernel binary
To compile mykernel.bin, just type
``` sh
make
```
in the terminal in the directory of NoS. The makefile will create all the .o files needed and the resulting .bin file. This is the kernel.

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

## Bugs

As of now, nothing is output when loading the kernel. Not sure why.

## License

GPL 3.0 License

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>
