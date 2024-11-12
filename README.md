ac_scanner PORT SCANNER
=======================

'ac_scanner' is a port scanner written in C++.

## How to build

In order to build the scanner:

### Linux

Run `bash ./CI/build.sh` and you will find the executable within the `build` folder.

### Windows

Run `cmd /c ./CI/build.bat` command, and you will find the executable within the
`build` folder.

## Usage

To use this tool, the following command structure needs to be run:

ac_scanner [-v | --version] [-h | --help] [-s | --system] [-u | --user] [-d | --dynamic] [-a | --all] <ip_address>

Parameters:
    -[ ] `-s | --system`: Will scan all ports between `0` and `1023`.
    -[ ] `-u | --user`: Will scan all ports between `1024` and `49151`.
    -[ ] `-d | --dynamic`: Will scan all ports between `49152` and `65535`.
    -[ ] `-a | --all`: Will scan all ports between `0` and `65535`.
    - `<ip_address>`: The address to scan (default: `127.0.0.1`)
