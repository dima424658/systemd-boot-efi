## systemd-boot
systemd-boot is an easy-to-configure UEFI boot manager.
It provides a textual menu to select the boot entry and an editor for the kernel command line.

This fork has mouse support. Original repository - [systemd/systemd](https://github.com/systemd/systemd)

## How to build
```bash
meson setup ./builddir --prefix=$(pwd)/installdir
meson install -C ./builddir
```

## Debugging

During boot, systemd-boot and the stub loader will output messages like `systemd-boot@0x0A` and `systemd-stub@0x0B`,
providing the base of the loaded code.
This location can then be used to attach to a QEMU session (provided it was run with `-s`).
See `debug-sd-boot.sh` script in the tools folder which automates this processes.

If the debugger is too slow to attach to examine an early boot code passage,
the call to `DEFINE_EFI_MAIN_FUNCTION()` can be modified to enable waiting.
As soon as the debugger has control, we can then run `set variable wait = 0` or `return` to continue.
Once the debugger has attached, setting breakpoints will work like usual.