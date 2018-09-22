# UEFI Hello world

* A Skeleton of My UEFI Application

## Requirements

* rake (ruby)
* llvm (clang/lld)
* nasm
* qemu (qemu-system-x86_64)
* [ovmf](https://sourceforge.net/projects/edk2/files/OVMF/)

## Cross Compling

### x64 (amd64)

```
$ rake ARCH=x64
$ rake run ARCH=x64
```

### i386

```
$ rake ARCH=i386
$ rake run ARCH=i386
```

### aarch64 (arm64)

```
$ rake ARCH=aa64
$ rake run ARCH=aa64
```

### aarch32 (arm32)

* Currently not supported :cry:

## License

* PUBLIC DOMAIN/WTFL

## References

* [liumOS](https://github.com/hikalium/liumos)
