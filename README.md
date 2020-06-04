# shearedSlitporeBD Installation

### Prerequisites

#### cmake (version 3.16.5 or higher)

* Download cmake source from https://cmake.org/download/
* Extract tar.gz via `tar -xvzf cmake*.tar.gz`
* Follow installation instructions on https://cmake.org/install/
    * `./bootstrap`
    * `make`
    * binary lies in folder `bin`, add it to the `PATH`-variable

#### Boost Program Options

###### You have administrator rights
* use `sudo apt-get install libboost-program-options-dev` if you have administrator rights
    * alternatively install `libboost-all-dev` if you want other libraries as well

###### You need to install from source
* download source code from https://www.boost.org/users/download/
* extract tar.gz (`tar -xvzf <archive>`)
* `./bootstrap.sh --prefix=$HOME/local/boost` 
    * you might want to define options `--libdir=<DIR>` and `--includedir=<DIR>`) for more control
* `./b2`
* `./b2 install` (needs `sudo`?)

### Compilation

* `cmake .` (use `-B <build_path>` to specify a build directory, `cd <build_path>` after that)
* `make`
* an example installation bash script is given in `install.sh` (`chmod +x install.sh` to make it executable)
* executable lies in folder `bin`, add it to the `PATH`-variable

### Troubleshooting

* `cmake` uses the `cc`-binary, which is not given by newer GCC versions; set the `CC` and `CXX`
environment variables to solve this issue: `export CC=<path/to/gcc>`, `export CXX=<path/to/g++>`
(for example in `~/.bashrc`)
    * remove any files in the `build`-directory before trying to reinstall
