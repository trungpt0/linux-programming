# Seek I/O

# Run

Compile gcc:

```bash
$ touch file_test
$ ./seek-io file_test s100000 wabc
s100000: seek succeeded
wabc: wrote 3 bytes
```

Run with <./seek-io> <file> <s(offset)> <w(write)>

```bash
$ ./seek-io file_test s100000 wabc
s100000: seek succeeded
wabc: wrote 3 bytes
```

Check offset and text:

```bash
$ ls -l file_test
-rw-rw-r-- 1 esacev esacev 100003 11月 20 03:00 file_test
$ cat file_test
abc
```

Test again:

```bash
./seek-io file_test s10000 R5
s10000: seek succeeded
R5: 00 00 00 00 00 
```