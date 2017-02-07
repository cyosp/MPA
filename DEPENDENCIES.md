# [MPA](https://github.com/cyosp/MPA) dependencies

## Dependencies

[MPA](https://github.com/cyosp/MPA) project dependencies are:

* OS

| Name                                       | Version     | Architecture   |
|:-------------------------------------------|:------------|:---------------|
| [Debian GNU/Linux](https://www.debian.org) | 9 (Stretch) | amd64 (x86_64) |

* IDE

| Component                             | Version |
|:--------------------------------------|:--------|
| [Eclipse](http://www.eclipse.org)     | 4.6.2   |
| [Eclipse CDT](http://eclipse.org/cdt) | 9.2.0   |

* Server side

| Library                                                           | Version                              |
|:------------------------------------------------------------------|:-------------------------------------|
| [Boost](http://www.boost.org/)                                    | 1.62.0 (package: libboost-all-dev)   |
| [Libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/) (MHD) | 0.9.51 (package: libmicrohttpd-dev ) |
| [LiteSQL](http://sourceforge.net/projects/litesql)                | 0.3.17 (to compile from sources)     |

* Client side

| Library                              | Version          |
|:-------------------------------------|:-----------------|
| [Bootstrap](http://getbootstrap.com) | 3.3.5            |
| [jQuery](http://jquery.com)          | 2.1.4            |



## Compile [LiteSQL](http://sourceforge.net/projects/litesql)

[LiteSQL](http://sourceforge.net/projects/litesql) must be compiled with:
 * [CYOSP](http://sourceforge.net/u/cyosp/profile/) commit: [[7b03c1] Add double to float conversion ](http://sourceforge.net/p/litesql/litesql/ci/7b03c1c739981af4378e16bf61d4da62c8827638)
 * [eXpat](http://expat.sourceforge.net/)
 * [SQLite](http://www.sqlite.org/)

Steps to build [LiteSQL](http://sourceforge.net/projects/litesql) are:

```bash
# Create directory which will host sources and move into this directory
mkdir -p ~/src/litesql && cd $_
# Get sources
git clone https://git.code.sf.net/p/litesql/litesql litesql-litesql
# Move to sources
cd litesql-litesql

# This package to solve:
#   /usr/include/c++/4.9/string:38:28: fatal error: bits/c++config.h: No such file or directory
sudo apt-get install g++-multilib
# Add eXpat and SQLite 3 development packages
sudo apt-get install libexpat1-dev libsqlite3-dev

# Update generated configuration files
autoreconf
# Add missing components
automake --add-missing

#
# Apply patch #1
#
cd src/generator
cp <project path>/patch/litesql/2017-02-06/src/generator/Makefile.in.diff .
patch -b -z .`date +%Y%m%d`.CYOSP Makefile.in Makefile.in.diff; echo $?

#
# Apply patch #2
#
cd ../examples
cp <project path>/patch/litesql/2017-02-06/src/examples/Makefile.am.diff .
patch -b -z .`date +%Y%m%d`.CYOSP Makefile.am Makefile.am.diff; echo $?

# Move to main folder and add execution rights to configure script
cd ../.. && chmod u+x configure

# Configure for 64 bits build
./configure --build=x86_64-pc-linux-gnu "CFLAGS=-m64" "CXXFLAGS=-m64" "LDFLAGS=-m64"

# Build from sources
make; echo $?

# Install what has been built
sudo make install
# Load new libraries installed into /usr/local/lib
sudo ldconfig

# Build documentation
cd docs/doxygen && doxygen doxygen.conf; echo $?
# Documentation is now available in ~/src/litesql/litesql-litesql/docs/doxygen/docs/html
```
