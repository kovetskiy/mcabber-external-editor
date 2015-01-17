# Why?
I hate multi-mode flow. But I love my editor and want use it
everywhere.

# Installation
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```

Add to your mcabberrc
```
module load editor
```

### Dependencies
- cmake
- mcabber headers

# todo
- [ ] check on errors
- [ ] check editor exit status
- [x] move to module (like a fifo)
- [ ] use *arg
