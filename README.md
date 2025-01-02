# Jaidenix
UNIX-Like OS written in C and ASM
Works on real hardware.

## Milestones:

### Milestone 1: Basics for a functional OS
- [x] Hello world!
- [x] Screen driver
- [x] GDT and IDT
- [x] Panic and ISR
- [ ] PIC and IRQs
- [ ] Keyboard
- [ ] Paging
- [ ] Heap
- [ ] HDD AHCI driver
- [ ] Ext2 File system
- [ ] Mount root
- [ ] Multitasking
- [ ] Switching to user mode

### Milestone 2: User-space and more functionality to kernel:

- [ ] ELF Loader
- [ ] C Library
- [ ] /dev file system
- [ ] /proc file system
- [ ] Shell
- [ ] /dev/pts file system
- [ ] Shutdown and Reboot
- [ ] Commands (ls, pwd, rm, mv, cp, mknod, etc...)
- [ ] C++ library
- [ ] Login and configuration files such as /etc/passwd, /etc/group, etc.
- [ ] SMP
- [ ] PCI drivers

### Milestone 3: Self-hosting Jaidenix system and some ports

- [ ] Port binutils.
- [ ] Port GCC.
- [ ] Port NASM.
- [ ] Port Make (in future Sh build system will be replaced by Makefiles)
- [ ] Port ncurses
- [ ] Port nano
- [ ] Recompile the OS under itself
- [ ] Of course, will port DOOM + Graphics driver
      
### Milestone 4: Networking

- [ ] Ethernet (NE2000, AMD PCNet)
- [ ] DHCP driver
- [ ] DNS lookup + /etc/resolv.conf
- [ ] TCP/IP driver
- [ ] IPv4
- [ ] IPv6
- [ ] Port OpenSSL
- [ ] Port wget
- [ ] Port git
- [ ] Port ssh
- [ ] Package manager

 ### Milestone 5: USB:

- [ ] USB 3.0 (xHCI) driver
- [ ] USB hubs driver
- [ ] USB devices (keyboard and mice)
- [ ] USB storage
- [ ] USB Ethernet drivers
