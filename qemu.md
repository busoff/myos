# qemu

- Install qemu on ubuntu
sudo apt-get install qemu-kvm qemu virt-manager virt-viewer libvirt-bin

From <https://www.unixmen.com/how-to-install-and-configure-qemu-in-ubuntu/> 


- Run qemu with your os image
qemu-system-i386 -fda <your image> 

- Debug your image  
```sh
$ qemu-system-i386 -fda <your image> -s -S
# In qumu console, enter
$ gdb
``` 

https://wwssllabcd.github.io/blog/2012/08/03/compile-linux011/
