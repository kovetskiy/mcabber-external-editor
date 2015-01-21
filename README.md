![whatis](https://cloud.githubusercontent.com/assets/8445924/5816239/f8b26134-a0bf-11e4-830f-c8cd676a9aae.gif)

# Why?
I hate multi-mode flow. But I love my editor and want use it
everywhere.

# Installation
```
$ mkdir build
$ cd build
$ cmake ..
$ make
# make install
```

Add to your mcabberrc
```
module load editor
```

# Usage
`/esay` for writing message in your editor.

### Options
```
set editor = vim
set shell = /bin/zsh
```

### Dependencies
- cmake
- mcabber headers

# todo
- [x] check on errors
- [ ] check editor exit status
- [x] move to module (like a fifo)
- [ ] add `/esay_to` like a `/say_to`
- [x] use $SHELL (which provides to use vim instead of /usr/bin/vim)
