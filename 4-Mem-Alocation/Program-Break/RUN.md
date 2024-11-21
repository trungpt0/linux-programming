# Program break

GCC compile:

```bash
$ make
```

Excute:

```bash
$ ./break-free 1000 1024 2 10 500
init program break 0x56...
allocating 1000*1024 bytes
program bread is now: 0x56...
freeing blocks from 10 to 500 in steps of 2
after free(), program break is: 0x56...
final program break: 0x56...
```
