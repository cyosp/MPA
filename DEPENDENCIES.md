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
| [Boost](http://www.boost.org/)                                    | 1.56.0 (to compile from sources) |
| [Libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/) (MHD) | 0.9.40 (to compile from sources) |
| [LiteSQL](http://sourceforge.net/projects/litesql)                | 0.3.17 (to compile from sources) |

* Client side

| Library          | Version          |
|:-----------------|:-----------------|
| **TO COMPLETE ** | **TO COMPLETE ** |

## Compile [LiteSQL](http://sourceforge.net/projects/litesql)

[LiteSQL](http://sourceforge.net/projects/litesql) must be compiled with:
 * [CYOSP](http://sourceforge.net/u/cyosp/profile/) commit: [[7b03c1] Add double to float conversion ](http://sourceforge.net/p/litesql/litesql/ci/7b03c1c739981af4378e16bf61d4da62c8827638).
 * [eXpat](http://expat.sourceforge.net/)
 * [SQLite 3](https://www.sqlite.org/)

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

# Install what as been built
sudo make install
# Load new libraries installed into /usr/local/lib
sudo ldconfig
```