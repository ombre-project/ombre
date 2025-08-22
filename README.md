# Ombre
Copyright (c) 2019, The Ombre Cryptocurrency Project

Copyright (c) 2018, Ryo Currency Project

Copyright (c) 2017, Sumokoin.org

Copyright (c) 2014-2017, The Monero Project

Copyright (c) 2012-2013, The Cryptonote developers

## Development Resources

- Web: [www.ombre.cash](http://www.ombre.cash)
- GitHub: [https://github.com/ombre-project/ombre](https://github.com/ombre-project/ombre)

## Introduction

Ombre is a cryptonote currency and an indirect for of the well-known Monero currency. Inherited from Monero are strong security, privacy and untraceability features that form a solid basis for further development. Our mission is to enhance the cryptonote protocol to provide a **lightweight**, **secure**, **well maintained** and **actively developed** (no-nonsense) coin.

Some main differences compared to other cryptonote coins are:

 - We use a 60 second block window which reduce transaction times
 - We enforce a minimum transaction mixin of 10 to fight blockchain analysis which could compromise privacy
 - We actively cooperate with other cryptonote coins and do not treat them as competition.


## Development funding

We do not have a premine. Instead we have a project development reward that causes coins to unlock 0.02% with every block that is found. 

The development fee will be used to pay for development, exchanges and marketing.

## Coin Supply & Emission

- **Total supply**: **500,000,000** coins in first 20 years which is followed by a tail emission each year for inflation.
- **Coin symbol**: **OMB**
- **Coin Units**:
  + 1 NanoOmbre &nbsp;= 0.000000001 **OMB** (10<sup>-9</sup> - _the smallest coin unit_)
  + 1 MicroOmbre = 0.000001 **OMB** (10<sup>-6</sup>)
  + 1 MilliOmbre = 0.001 **OMB** (10<sup>-3</sup>)
- **Hash algorithm**: CryptoNight (Proof-Of-Work)
- **Emission scheme**: Ombre's block reward changes _every 6-months_ as the following "Camel" distribution* (inspired by _real-world mining production_ like of crude oil, coal etc. that is often slow at first,
accelerated in the next few years before declined and depleted). This great emission scheme was first introduced in Sumokoin.


## Compiling ombre from source

### Windows
**Operating System:** Windows 10 64-bit
**Environment:** MSYS2 / mingw64

These packages were explicitly installed on MSYS2:
- `base-devel`
- `mingw-w64-x86_64-icu`
- `mingw-w64-x86_64-toolchain`
- `mingw-w64-x86_64-cmake`
- `mingw-w64-x86_64-zeromq`
- `mingw-w64-x86_64-cppzmq`
- `mingw-w64-x86_64-doxygen`
- `mingw-w64-x86_64-graphviz`

_Some packages, such as `libsodium`, were installed implicitly as dependencies of the above packages._

**Boost installation:**
The default Boost packages in MSYS2 do not include static libraries, so Boost static libraries were built from source following these steps:

```
wget https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz
tar -xvf boost-1.84.0.tar.gz
cd boost-1.84.0
./bootstrap.sh
./b2 variant=release link=static runtime-link=static threading=multi install -j$(nproc)
./b2 headers
```

This process installs the `lib` and `include` folders by default under `C:/usr/local`. The installation path can be customized during `b2` execution, but ultimately the `lib` and `include` directories must be placed in `[MSYS2 install folder]/mingw64/`.

_Note: MSYS2 can theoretically be installed in a custom directory, but it is strongly recommended to use the default path, because the project may not find some libraries and files outside of it._

**Building the project:**
After completing the steps above, the project can be compiled using:
```
make debug-win64
```
or
```
make release-static-win64
```
_Note: debug output directory can get as big as 2.06GB, so building the release version is recommended._

---

### Ubuntu
**Operating System:** Ubuntu (Desktop/Server) 24.04.1 LTS

**Required packages:**
The packages below are required for successful build:
```
sudo apt update
sudo apt install build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev
```
You might also need:
```
sudo apt install cppzmq-dev libreadline-dev
```
In testing, cppzmq-dev was required on a fresh Ubuntu Server 24 installation, and libreadline-dev was required on Desktop. These may or may not be needed depending on your environment, but it is recommended to install both to avoid issues.

_Some packages listed in README.md were installed implicitly as dependencies of the above._

**Building the project:**
After installing the required dependencies, the project can be built as usual with:
```
make debug
```
_Note: release build is also built with `make release-static`, however that will need manually building static boost libraries because they do not come by default on Ubuntu_

---

## Roadmap 2019

### Q3: Android wallet
We will release an Android wallet which will use remote wallet nodes to scan the blockchain for transactions.

One problem with existing Android wallets for cryptonote coins is that they use close to 1GB of data (Sumokoin) to scan the blockchain. we will solve this by allowing the Android wallet to send the wallet's viewkey to the remote wallet node. With this approach the transaction scanning can be done server side and this will significantly increase the performance of the wallet.

All wallet connections will be SSL encrypted and official wallet nodes will be provided.

### Q3. Blockchain protocol optimisations
The blockchain network communication is not optimized and, for example, doesn't even use compression on large data exchanges. We will add compression and will look into modernizing the RPC protocols.

### Q4. Security audit
We plan on doing a full security audit of the codebase and will setup fuzzing for all exposed network logic. Additionally security enhancements are planned for the ombred daemon, the GUI wallet and the communication channel between both.

### Q3. Web wallet
For this roadmap item we would like to have community feedback first: we think a web wallet would be very convenient for our users but we'll be on the lookout for feedback before starting the implementation.

### Q4. Global pool balancer ((under consideration)
We will implement a lightweight and yet protocol aware loadbalancer to spread the mining load on our network across pools evenly. We will create an incentive for pool owners and miners to join the loadbalancer. A healthy spread of the mining across multiple pools is highly beneficial for the stability of the coin.


## About this Project

This is the core implementation of Ombre. It is open source and completely free to use without restrictions, except for those specified in the license agreement below. There are no restrictions on anyone creating an alternative implementation of Ombre that uses the protocol and network in a compatible manner.

As with many development projects, the repository on Github is considered to be the "staging" area for the latest changes. Before changes are merged into that branch on the main repository, they are tested by individual developers in their own branches, submitted as a pull request, and then subsequently tested by contributors who focus on testing and code reviews. That having been said, the repository should be carefully considered before using it in a production environment, unless there is a patch in the repository for a particular show-stopping issue you are experiencing. It is generally a better idea to use a tagged release for stability.

**Anyone is welcome to contribute to Ombre's codebase!** If you have a fix or code change, feel free to submit is as a pull request directly to the "master" branch. In cases where the change is relatively small or does not affect other parts of the codebase it may be merged in immediately by any one of the collaborators. On the other hand, if the change is particularly large or complex, it is expected that it will be discussed at length either well in advance of the pull request being submitted, or even directly on the pull request.

## License

Please view [LICENSE](LICENSE)

[![License](https://img.shields.io/badge/license-BSD3-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

## Precompiled binaries

Along with each release you can find our [precompiled binaries](https://github.com/ombre-project/ombre/releases).
To verify that the downloaded binaries are created by one of our developer please verify the checksums.
The authenticity of the checksums can by verified with the [PGP-key's](docs/pgp_keys.md).

## Compiling ombre from source for older Ubuntu versions

### Dependencies

The following table summarizes the tools and libraries required to build. A
few of the libraries are also included in this repository (marked as
"Vendored"). By default, the build uses the library installed on the system,
and ignores the vendored sources. However, if no library is found installed on
the system, then the vendored source will be built and used. The vendored
sources are also used for statically-linked builds because distribution
packages often include only shared library binaries (`.so`) but not static
library archives (`.a`).

| Dep          | Min. version  | Vendored | Debian/Ubuntu pkg  | Arch pkg     | Fedora            | Optional | Purpose        |
| ------------ | ------------- | -------- | ------------------ | ------------ | ----------------- | -------- | -------------- |
| GCC          | 4.7.3         | NO       | `build-essential`  | `base-devel` | `gcc`             | NO       |                |
| CMake        | 3.0.0         | NO       | `cmake`            | `cmake`      | `cmake`           | NO       |                |
| pkg-config   | any           | NO       | `pkg-config`       | `base-devel` | `pkgconf`         | NO       |                |
| Boost        | 1.58          | NO       | `libboost-all-dev` | `boost`      | `boost-devel`     | NO       | C++ libraries  |
| OpenSSL      | basically any | NO       | `libssl-dev`       | `openssl`    | `openssl-devel`   | NO       | sha256 sum     |
| libzmq       | 3.0.0         | NO       | `libzmq3-dev`      | `zeromq`     | `cppzmq-devel`    | NO       | ZeroMQ library |
| libunbound   | 1.4.16        | YES      | `libunbound-dev`   | `unbound`    | `unbound-devel`   | NO       | DNS resolver   |
| libsodium    | ?             | NO       | `libsodium-dev`    | ?            | `libsodium-devel` | NO       | libsodium      |
| libminiupnpc | 2.0           | YES      | `libminiupnpc-dev` | `miniupnpc`  | `miniupnpc-devel` | YES      | NAT punching   |
| libunwind    | any           | NO       | `libunwind8-dev`   | `libunwind`  | `libunwind-devel` | YES      | Stack traces   |
| liblzma      | any           | NO       | `liblzma-dev`      | `xz`         | `xz-devel`        | YES      | For libunwind  |
| libreadline  | 6.3.0         | NO       | `libreadline6-dev` | `readline`   | `readline-devel`  | YES      | Input editing  |
| ldns         | 1.6.17        | NO       | `libldns-dev`      | `ldns`       | `ldns-devel`      | YES      | SSL toolkit    |
| expat        | 1.1           | NO       | `libexpat1-dev`    | `expat`      | `expat-devel`     | YES      | XML parsing    |
| GTest        | 1.5           | YES      | `libgtest-dev`^    | `gtest`      | `gtest-devel`     | YES      | Test suite     |
| Doxygen      | any           | NO       | `doxygen`          | `doxygen`    | `doxygen`         | YES      | Documentation  |
| Graphviz     | any           | NO       | `graphviz`         | `graphviz`   | `graphviz`        | YES      | Documentation  |


[^] On Debian/Ubuntu `libgtest-dev` only includes sources and headers. You must
build the library binary manually. This can be done with the following command ```sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake . && sudo make && sudo mv libg* /usr/lib/ ```

Debian / Ubuntu one liner for all dependencies  
``` sudo apt update && sudo apt install build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev doxygen graphviz libpgm-dev```

### Cloning the repository

Clone recursively to pull-in needed submodule(s):

`$ git clone https://github.com/ombre-project/ombre.git`

If you already have a repo cloned, initialize and update:

`$ cd ombre`

### Build instructions

ombre uses the CMake build system and a top-level [Makefile](Makefile) that
invokes cmake commands as needed.

#### On Linux and OS X

* Install the dependencies
* Change to the root of the source code directory, change to the most recent release branch, and build:

        cd ombre
        make

    *Optional*: If your machine has several cores and enough memory, enable
    parallel build by running `make -j<number of threads>` instead of `make`. For
    this to be worthwhile, the machine should have one core and about 2GB of RAM
    available per thread.

    *Note*: If cmake can not find zmq.hpp file on OS X, installing `zmq.hpp` from
    https://github.com/zeromq/cppzmq to `/usr/local/include` should fix that error.

    *Note*: The instructions above will compile the most stable release of the
    ombre software. If you would like to use and test the most recent software,
    use ```git checkout master```. The master branch may contain updates that are
    both unstable and incompatible with release software, though testing is always
    encouraged.

* The resulting executables can be found in `build/release/bin`

* Add `PATH="$PATH:$HOME/ombre/build/release/bin"` to `.profile`

* Run ombre with `ombred --detach`

* **Optional**: build and run the test suite to verify the binaries:

        make release-test

    *NOTE*: `core_tests` test may take a few hours to complete.

* **Optional**: to build binaries suitable for debugging:

         make debug

* **Optional**: to build statically-linked binaries:

         make release-static

Dependencies need to be built with -fPIC. Static libraries usually aren't, so you may have to build them yourself with -fPIC. Refer to their documentation for how to build them.

* **Optional**: build documentation in `doc/html` (omit `HAVE_DOT=YES` if `graphviz` is not installed):

        HAVE_DOT=YES doxygen Doxyfile

#### On the Raspberry Pi

Tested on a Raspberry Pi Zero with a clean install of minimal Raspbian Stretch (2017-09-07 or later) from https://www.raspberrypi.org/downloads/raspbian/. If you are using Raspian Jessie, [please see note in the following section](#note-for-raspbian-jessie-users).

* `apt-get update && apt-get upgrade` to install all of the latest software

* Install the dependencies for ombre from the 'Debian' column in the table above.

* Enable zram:
```
	sudo zramctl --find --size=1024M # Note the device name
	sudo mkswap <device name>
	sudo swapon <device name>
```
* Clone ombre and checkout most recent release version:
```
        git clone https://github.com/ombre-project/ombre.git
	cd ombre
	git checkout tags/0.2.0
```
* Build:
```
        make release
```
* Wait 4-6 hours

* The resulting executables can be found in `build/release/bin`

* Add `PATH="$PATH:$HOME/ombre/build/release/bin"` to `.profile`

* Run ombre with `ombred --detach`

* You may wish to reduce the size of the swap file after the build has finished, and delete the boost directory from your home directory

#### *Note for Raspbian Jessie users:*

If you are using the older Raspbian Jessie image, compiling ombre is a bit more complicated. The version of Boost available in the Debian Jessie repositories is too old to use with ombre, and thus you must compile a newer version yourself. The following explains the extra steps, and has been tested on a Raspberry Pi 2 with a clean install of minimal Raspbian Jessie.

* As before, `apt-get update && apt-get upgrade` to install all of the latest software, and enable zram

```
	sudo zramctl --find --size=1024M # Note the device name
	sudo mkswap <device name>
	sudo swapon <device name>
```

* Then, install the dependencies for ombre except `libunwind` and `libboost-all-dev`

* Install the latest version of boost (this may first require invoking `apt-get remove --purge libboost*` to remove a previous version if you're not using a clean install):
```
	cd
	wget https://sourceforge.net/projects/boost/files/boost/1.64.0/boost_1_64_0.tar.bz2
	tar xvfo boost_1_64_0.tar.bz2
	cd boost_1_64_0
	./bootstrap.sh
	sudo ./b2
```
* Wait ~8 hours
```
	sudo ./bjam install
```
* Wait ~4 hours

* From here, follow the [general Raspberry Pi instructions](#on-the-raspberry-pi) from the "Clone ombre and checkout most recent release version" step.

#### On Windows:

Binaries for Windows are built on Windows using the MinGW toolchain within
[MSYS2 environment](http://msys2.github.io). The MSYS2 environment emulates a
POSIX system. The toolchain runs within the environment and *cross-compiles*
binaries that can run outside of the environment as a regular Windows
application.

**Preparing the Build Environment**

* Download and install the [MSYS2 installer](http://msys2.github.io), either the 64-bit or the 32-bit package, depending on your system.
* Open the MSYS shell via the `MSYS2 Shell` shortcut
* Update packages using pacman:

        pacman -Syuu

* Exit the MSYS shell using Alt+F4
* Edit the properties for the `MSYS2 Shell` shortcut changing "msys2_shell.bat" to "msys2_shell.cmd -mingw64" for 64-bit builds or "msys2_shell.cmd -mingw32" for 32-bit builds
* Restart MSYS shell via modified shortcut and update packages again using pacman:

        pacman -Syuu


* Install dependencies:

    To build for 64-bit Windows:

        pacman -S mingw-w64-x86_64-toolchain make mingw-w64-x86_64-cmake mingw-w64-x86_64-boost mingw-w64-x86_64-openssl mingw-w64-x86_64-zeromq mingw-w64-x86_64-libsodium

    To build for 32-bit Windows:

        pacman -S mingw-w64-i686-toolchain make mingw-w64-i686-cmake mingw-w64-i686-boost mingw-w64-i686-openssl mingw-w64-i686-zeromq mingw-w64-i686-libsodium

* Open the MingW shell via `MinGW-w64-Win64 Shell` shortcut on 64-bit Windows
  or `MinGW-w64-Win64 Shell` shortcut on 32-bit Windows. Note that if you are
  running 64-bit Windows, you will have both 64-bit and 32-bit MinGW shells.

**Cloning**

* To git clone, run:

        git clone https://github.com/ombre-project/ombre.git
**Building**

* Change to the cloned directory, run:

        cd ombre

* If you would like a specific [version/tag](https://github.com/ombre-project/ombre/tags), do a git checkout for that version. eg. '0.2.0'. If you dont care about the version and just want binaries from master, skip this step:

        git checkout 0.2.0

* If you are on a 64-bit system, run:

        make release-static-win64

* If you are on a 32-bit system, run:

        make release-static-win32

* The resulting executables can be found in `build/release/bin`

* **Optional**: to build Windows binaries suitable for debugging on a 64-bit system, run:

        make debug-static-win64

* **Optional**: to build Windows binaries suitable for debugging on a 32-bit system, run:

        make debug-static-win32

* The resulting executables can be found in `build/debug/bin`

### On FreeBSD:

The project can be built from scratch by following instructions for Linux above. If you are running ombre in a jail you need to add the flag: `allow.sysvipc=1` to your jail configuration, otherwise lmdb will throw the error message: `Failed to open lmdb environment: Function not implemented`.

We expect to add ombre into the ports tree in the near future, which will aid in managing installations using ports or packages.

### On OpenBSD:

#### OpenBSD < 6.2

This has been tested on OpenBSD 5.8.

You will need to add a few packages to your system. `pkg_add db cmake gcc gcc-libs g++ miniupnpc gtest`.

The doxygen and graphviz packages are optional and require the xbase set.

The Boost package has a bug that will prevent librpc.a from building correctly. In order to fix this, you will have to Build boost yourself from scratch. Follow the directions here (under "Building Boost"):
https://github.com/bitcoin/bitcoin/blob/master/doc/build-openbsd.md

You will have to add the serialization, date_time, and regex modules to Boost when building as they are needed by ombre.

To build: `env CC=egcc CXX=eg++ CPP=ecpp DEVELOPER_LOCAL_TOOLS=1 BOOST_ROOT=/path/to/the/boost/you/built make release-static-64`

#### OpenBSD >= 6.2

You will need to add a few packages to your system. `pkg_add cmake miniupnpc zeromq libiconv`.

The doxygen and graphviz packages are optional and require the xbase set.


Build the Boost library using clang. This guide is derived from: https://github.com/bitcoin/bitcoin/blob/master/doc/build-openbsd.md

We assume you are compiling with a non-root user and you have `doas` enabled.

Note: do not use the boost package provided by OpenBSD, as we are installing boost to `/usr/local`.

```
# Create boost building directory
mkdir ~/boost
cd ~/boost

# Fetch boost source
ftp -o boost_1_64_0.tar.bz2 https://netcologne.dl.sourceforge.net/project/boost/boost/1.64.0/boost_1_64_0.tar.bz2

# MUST output: (SHA256) boost_1_64_0.tar.bz2: OK
echo "7bcc5caace97baa948931d712ea5f37038dbb1c5d89b43ad4def4ed7cb683332 boost_1_64_0.tar.bz2" | sha256 -c
tar xfj boost_1_64_0.tar.bz2

# Fetch and apply boost patches, required for OpenBSD
ftp -o boost_test_impl_execution_monitor_ipp.patch https://raw.githubusercontent.com/openbsd/ports/bee9e6df517077a7269ff0dfd57995f5c6a10379/devel/boost/patches/patch-boost_test_impl_execution_monitor_ipp
ftp -o boost_config_platform_bsd_hpp.patch https://raw.githubusercontent.com/openbsd/ports/90658284fb786f5a60dd9d6e8d14500c167bdaa0/devel/boost/patches/patch-boost_config_platform_bsd_hpp

# MUST output: (SHA256) boost_config_platform_bsd_hpp.patch: OK
echo "1f5e59d1154f16ee1e0cc169395f30d5e7d22a5bd9f86358f738b0ccaea5e51d boost_config_platform_bsd_hpp.patch" | sha256 -c
# MUST output: (SHA256) boost_test_impl_execution_monitor_ipp.patch: OK
echo "30cec182a1437d40c3e0bd9a866ab5ddc1400a56185b7e671bb3782634ed0206 boost_test_impl_execution_monitor_ipp.patch" | sha256 -c

cd boost_1_64_0
patch -p0 < ../boost_test_impl_execution_monitor_ipp.patch
patch -p0 < ../boost_config_platform_bsd_hpp.patch

# Start building boost
echo 'using clang : : c++ : <cxxflags>"-fvisibility=hidden -fPIC" <linkflags>"" <archiver>"ar" <striper>"strip"  <ranlib>"ranlib" <rc>"" : ;' > user-config.jam
./bootstrap.sh --without-icu --with-libraries=chrono,filesystem,program_options,system,thread,test,date_time,regex,serialization,locale --with-toolset=clang
./b2 toolset=clang cxxflags="-stdlib=libc++" linkflags="-stdlib=libc++" -sICONV_PATH=/usr/local
doas ./b2 -d0 runtime-link=shared threadapi=pthread threading=multi link=static variant=release --layout=tagged --build-type=complete --user-config=user-config.jam -sNO_BZIP2=1 -sICONV_PATH=/usr/local --prefix=/usr/local install
```

Build cppzmq

Build the cppzmq bindings.

We assume you are compiling with a non-root user and you have `doas` enabled.

```
# Create cppzmq building directory
mkdir ~/cppzmq
cd ~/cppzmq

# Fetch cppzmq source
ftp -o cppzmq-4.2.3.tar.gz https://github.com/zeromq/cppzmq/archive/v4.2.3.tar.gz

# MUST output: (SHA256) cppzmq-4.2.3.tar.gz: OK
echo "3e6b57bf49115f4ae893b1ff7848ead7267013087dc7be1ab27636a97144d373 cppzmq-4.2.3.tar.gz" | sha256 -c
tar xfz cppzmq-4.2.3.tar.gz

# Start building cppzmq
cd cppzmq-4.2.3
mkdir build
cd build
cmake ..
doas make install
```

Build ombre: `env DEVELOPER_LOCAL_TOOLS=1 BOOST_ROOT=/usr/local make release-static`

### On Solaris:

The default Solaris linker can't be used, you have to install GNU ld, then run cmake manually with the path to your copy of GNU ld:

        mkdir -p build/release
        cd build/release
        cmake -DCMAKE_LINKER=/path/to/ld -D CMAKE_BUILD_TYPE=Release ../..
        cd ../..

Then you can run make as usual.

# LMDB

There is an `mdb_stat` command in the LMDB source that can print statistics about the database but it's not routinely built. This can be built with the following command:

`cd ~/ombre/external/db_drivers/liblmdb && make`

The output of `mdb_stat -ea <path to blockchain dir>` will indicate inconsistencies in the blocks, block_heights and block_info table.

The output of `mdb_dump -s blocks <path to blockchain dir>` and `mdb_dump -s block_info <path to blockchain dir>` is useful for indicating whether blocks and block_info contain the same keys.

These records are dumped as hex data, where the first line is the key and the second line is the data.

