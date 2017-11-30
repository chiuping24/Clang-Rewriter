# clang-tidy

Using clang-tidy to automatic refactoring /fixing your code.  
Clang-tidy is used to perform various code transformations and fixes like modernizing code to C++11/14/17 and finding subtle latent bugs.   

#### LLVM/Clang/clang-extra-tools installation
First of all, LLVM/Clang need to be installed.  
Please install it from [pre-built binaries](http://releases.llvm.org/download.html).  
The suggestion is don't install from source code building by yourself, the newest version of Clang will be produced. It may be not full-released. And it's difficult to get (another build ?) the clang extra tools such as clang-tidy...  
```
$ clang --version  
clang version 5.0.0 (tags/RELEASE_500/final)  
Target: x86_64-pc-windows-msvc  
Thread model: posix  
InstalledDir: C:\Program Files\LLVM\bin  
  
$ clang-tidy --version  
LLVM (http://llvm.org/):  
  LLVM version 5.0.0  
  Optimized build.  
  Default target: x86_64-pc-windows-msvc  
  Host CPU: skylake  

```

#### 

#### 
* run-clang-tidy.py
```
usage: run-clang-tidy.py [-h] [-clang-tidy-binary PATH]
                         [-clang-apply-replacements-binary PATH]
                         [-checks CHECKS] [-header-filter HEADER_FILTER]
                         [-j J] [-fix] [-format] [-style STYLE]
                         [-p BUILD_PATH] [-extra-arg EXTRA_ARG]
                         [-extra-arg-before EXTRA_ARG_BEFORE] [-quiet]
                         [files [files ...]]

```
