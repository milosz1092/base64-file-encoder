## Base64 file encoder

It is command line program written in C for converting files into Base64 equivalent. Encoding [algorithm](https://github.com/milosz1092/base64-file-encoder/blob/main/src/encode.c) is based on [RFC4648](https://datatracker.ietf.org/doc/html/rfc4648).

## Compiling

***Prerequisites:** [GNU Compiler Collection](https://gcc.gnu.org/) installed.*

In root directory run command presented below:
```
gcc -o base64 ./src/utils.c ./src/encode.c ./src/main.c
```
Executable `base64` file will be created.

## Usage
```
base64 <path-to-file>
```
As a result there will be `<path-to-file>.b64` created includes encoded version.
