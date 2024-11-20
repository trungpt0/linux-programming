# Scatter Input

Scatter Input refers to a technique in system programming where data is read from a single file descriptor (like a file or socket) and distributed across multiple non-contiguous memory buffers in a single operation. This is commonly implemented using the readv() system call in Unix/Linux, which takes a file descriptor and an array of iovec structures. Each iovec specifies a base address and length for a memory buffer. The operation efficiently fills each buffer sequentially with the data read, eliminating the need for multiple read calls. Scatter input is particularly useful for processing structured or segmented data efficiently.

# Run

GCC Compile:

```bash
$ make
```

Excute:

```bash
$ ./scatter-input test-file.txt
read fewer bytes than requested
total bytes requested: 248
bytes read: 44
```