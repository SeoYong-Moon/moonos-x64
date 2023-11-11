# MoonOS-x64

MoonOS is an operating system running on a legacy-free architecture (UEFI BIOS, Intel 64 mode).

---

### File Configuration:

- MoonLoaderPkg
Bootloader configured as a UEFI app
- kernel
The kernel of MoonOS

---

### Build:

It has been tested on Ubuntu 18.04 with using development tools such as Clang, NASM, and EDK II. The build repository will be added with procedures.

---

### Currently Implemented Features:

- Booting from UEFI BIOS
- Runs in 64-bit
- Retriving memory map
- Booting in kernel, rendering fonts
- Scan PCI Devices

---

### Future Work:

- Rendering mouse

- Implement inturrupt and FIFO

- Memory management with paging

- GUI interface

- Timer and ACPI

- Keyboard input

- Multitasking

- Terminal with command

- File system

- Application

- System call

- Unicode language
