# Aim

This project includes a very simple C++ header that should allow a
host compiler to process a CUDA source files with as few errors as
possible.

The aim is not to produce an actually useful object file, but just to
allow usage of clang features and editor integration on CUDA files (for
example semantic completion as offered by [YouCompeteMe][ycm]).

[ycm]: https://github.com/Valloric/YouCompleteMe

# Usage

To use it, you simply need to pre-include the `fake_host_cuda.h` header
when compiling, for example:

	cc -x c++ -include /path/to/fake_host_cuda.h -c source.cu


Recent versions of clang (from 3.6.2 at least) support CUDA directly, so
you can actually `-x cuda` instead of `-x c++`, and this will correctly
process the CUDA kernel launch syntax.

To use it with YouCompleteMe, set your vim filetype to `cuda.cpp`
(hopefully future versions of YCM will make this unnecessary) and
add `'-include', '/path/to/fake_host_cuda.h'` to the `'flags'` returned
from a custom `.ycm_extra_conf.py`.

<!-- Example from my 'generic' .ycm_extra_conf.py

```python
import subprocess

cppflags=subprocess.check_output("make -pnr /dev/null | grep ^CPPFLAGS | cut -f2- -d=", shell=True).strip().split()
cxxflags=subprocess.check_output("make -pnr /dev/null | grep ^CXXFLAGS | cut -f2- -d=", shell=True).strip().split()
cflags=subprocess.check_output("make -pnr /dev/null | grep ^CFLAGS | cut -f2- -d=", shell=True).strip().split()

stdcinclude=[ ['-isystem', path.strip()] for path in
        subprocess.check_output("echo | clang -x c -v %(flags)s -E - 2>&1 | awk '/^#include </,/^End of/ { print; }'" % { 'flags' : " ".join(cppflags+cflags) },
            shell=True).split("\n")[1:-2] ]
stdcxxinclude=[ ['-isystem', path.strip()] for path in
        subprocess.check_output("echo | clang  -x c++ -v %(flags)s -E - 2>&1 | awk '/^#include </,/^End of/ { print; }'" % { 'flags' : " ".join(cppflags+cxxflags) },
            shell=True).split("\n")[1:-2] ]

allcxx = ['-x', 'c++'] + cppflags + cxxflags + [el for pair in stdcxxinclude for el in pair]
allcuda = ['-x', 'cuda', 'include', '/path/to/fake-host-cuda.h'] + cppflags + cxxflags + [el for pair in stdcxxinclude for el in pair]
allcc = ['-x', 'c'] + cppflags + cflags + [el for pair in stdcinclude for el in pair]

def FlagsForFile( filename ):
    if filename.endswith(('.C', '.cpp', '.cc', '.H', '.hpp', '.hh')):
        return { 'flags' : allcxx, 'do_cache' : False }
    elif filename.endswith(('.cu', '.cuh')):
        return { 'flags' : allcuda, 'do_cache' : False }
    else:
        return { 'flags' : allcc, 'do_cache' : False }
```
-->

# Notes

* the header will disable warnings about unknown attributes;
* some intrinsics will not be defined;
* as far as I know there is no trivial way to make the host compiler
  accept the bracketed launch grid syntax for CUDA kernels unless it has
  built-in support for CUDA (e.g. recent clang versions), so expect all
  such invokations to produce an error (if anybody has suggestions
  on how to work around this, please share).

