# Lab Works of UNIX Network Programming

# Get Start

## Install unp Library

Clone UNP source code from [GitHub](https://github.com/unpbook/unpv13e).

```bash
git clone git@github.com:unpbook/unpv13e.git
```

Compile and install the library on the system, tested on Ubuntu Server 18.04 LTS x64.

```bash
cd unpv13e
# bulid the project
./configure
cd lib
make
```

Edit `unp.h`: replace `#include "../config.h"` with `#include "unpconfig.h"`.

Copy the library to the system.

```bash
# go back to the root directory of unpv13e
cd ..
# copy the header, use sudo if you are not root
cp config.h /usr/include/unpconfig.h
cp lib/unp.h /usr/include
# copy the library
cp libunp.a /usr/lib
```

## Run

```bash
# compile the source code with unp library
gcc xxx.c -o xxx -lunp
# run
./xxx
```

# Projects

`lab-work-1`: an echo server and client