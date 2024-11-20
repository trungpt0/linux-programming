# Large File

off64_t, open64(), lseek64()...

# Run

GCC compile:

```bash
$ make
```

Excute:

```bash
$ ./access-lfile large-file.txt 1000000
$ cat large-file.txt
test
```