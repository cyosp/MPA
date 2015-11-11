# [MPA](https://github.com/cyosp/MPA) dependencies

## Dependencies

[MPA](https://github.com/cyosp/MPA) project dependencies are:

* OS

| Name                                       | Version    | Architecture   |
|:-------------------------------------------|:-----------|:---------------|
| [Debian GNU/Linux](https://www.debian.org) | 8 (Jessie) | amd64 (x86_64) |

* IDE

| Component                             | Version |
|:--------------------------------------|:--------|
| [Eclipse](http://www.eclipse.org)     | 3.8.1   |
| [Eclipse CDT](http://eclipse.org/cdt) | 8.0.2   |

* Server side

| Library                                                           | Version                          |
|:------------------------------------------------------------------|:---------------------------------|
| [Boost](http://www.boost.org/)                                    | 1.59.0 (to compile from sources) |
| [Libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/) (MHD) | 0.9.40 (to compile from sources) |
| [LiteSQL](http://sourceforge.net/projects/litesql)                | 0.3.17 (to compile from sources) |

* Client side

| Library          | Version          |
|:-----------------|:-----------------|
| **TO COMPLETE ** | **TO COMPLETE ** |

## Compile [LiteSQL](http://sourceforge.net/projects/litesql)

[LiteSQL](http://sourceforge.net/projects/litesql) must be compiled with:
 * [CYOSP](http://sourceforge.net/u/cyosp/profile/) commit: [[7b03c1] Add double to float conversion ](http://sourceforge.net/p/litesql/litesql/ci/7b03c1c739981af4378e16bf61d4da62c8827638)
 * [eXpat](http://expat.sourceforge.net/)
 * [SQLite](http://www.sqlite.org/)

Steps to build [LiteSQL](http://sourceforge.net/projects/litesql) are:

```bash
# Create directory which will host sources
mkdir -p ~/src/litesql
# Move into this directory
cd ~/src/litesql
# Get sources
wget http://sourceforge.net/code-snapshots/git/l/li/litesql/litesql.git/litesql-litesql-7b03c1c739981af4378e16bf61d4da62c8827638.zip
# Uncompress sources
unzip litesql-litesql-7b03c1c739981af4378e16bf61d4da62c8827638.zip
# Move into uncompressed directory
cd litesql-litesql-7b03c1c739981af4378e16bf61d4da62c8827638
# Add missing packages for compilation
sudo apt-get install automake libc6 libc6-dev
# This package to solve:
#   /usr/include/c++/4.9/string:38:28: fatal error: bits/c++config.h: No such file or directory
sudo apt-get install g++-multilib
# Add eXpat and SQLite 3 development packages
sudo apt-get install libexpat1-dev libsqlite3-dev

# Configure for 64 bits build
./configure --build=x86_64-pc-linux-gnu "CFLAGS=-m64" "CXXFLAGS=-m64" "LDFLAGS=-m64"

# Build from sources
make
# HTML documentation is now available in this folder:
#   ~/src/litesql/litesql-litesql-7b03c1c739981af4378e16bf61d4da62c8827638/docs/doxygen/docs/doxygen/html

# Install what has been built
sudo make install
# Load new libraries installed into /usr/local/lib
sudo ldconfig
```
## Compile [Boost](http://www.boost.org/)

[Boost](http://www.boost.org/) must be compiled as a shared library and with:
 * [International Components for Unicode](http://site.icu-project.org/)
 * [Python](https://www.python.org/)
 * [GCC](http://gcc.gnu.org/)

Steps to build [Boost](http://www.boost.org/) are:

```bash
# Create directory which will host sources
mkdir -p ~/src/boost
# Move into this directory
cd ~/src/boost
# Get sources
wget http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.bz2
# Uncompress sources
tar -xjvf  boost_1_59_0.tar.bz2
# Move into uncompressed directory
cd boost_1_59_0
# Add missing packages for compilation
sudo apt-get install libicu-dev libbz2-dev

# Configure for build
./bootstrap.sh --with-libraries=all --with-icu=/usr/lib/x86_64-linux-gnu/icu --with-python=/usr/bin/python --prefix=/usr/local

# Build from sources in 64 bits and install
sudo ./b2 architecture=x86 address-model=64 variant=release toolset=gcc link=shared threading=multi runtime-link=shared install >> b2.log
```