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

By default, `editor` will be same as `$EDITOR`.

```
set editor = vim
```

### Dependencies
- cmake
- mcabber headers

# todo
- [ ] add `/esay_to` like a `/say_to`
