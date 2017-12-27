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

#### Python
If you don't have python installed in pc.  
You can just download the package (What I use is Python 3.5.2)  
https://www.python.org/downloads/release/python-352/  
Windows x86-64 embeddable zip file  


將上述的Python包以及LLVM/Clang pre-built binaries包,放在對應批次檔的路徑  
即可在使用者不需要安裝任何東西的情況下  
對程式碼做重構  
  

#### Clang compilation database (compile_commands.json)
It's the complete information to Clang compiler when looking at source files.  
For windows user, you can download [Sourcetrail Extension](https://www.sourcetrail.com/blog/export_clang_compilation_database_from_visual_studio_solution/) to export compilation database with Visual Studio.

#### Refactoring a project with easy button: Refactoring.bat
Here put a demo project with (compile_commands.json) which is includes:   
Header.h  
Source.cpp  
src/Calc.cpp  
src/domath.cpp  
  
#### Refactoring results
For example: A part of Source.cpp
```c++

struct B : public A {
	int a = 0;
	virtual void foo(int x) {
		if (x == 1) {
			a = 5;
		}
	};
};

```
After refactoring, here shows the C++11 transfer by clang-tidy:   
```c++

struct B : public A {
	int a = 0;
	void foo(int x) override {
		if (x == 1) {
			a = 5;
		}
	};
};
```  
The other part of Source.cpp: 

```c++
distance  = fabs(glBND_xp_limit - glBND_xn_limit);
distance2 = fabs(glBND_yp_limit - glBND_yn_limit);
```  
After refactoring, here shows the Rewriter by ClangExample.cpp:  
It is defined when `A = fabs(longdouble-longdouble)`  
--> chang to  `A = fabs(static_cast<typeOfA>(longdouble-longdouble))`
```c++
distance  = fabs(static_cast<double> (glBND_xp_limit - glBND_xn_limit));
distance2 = fabs(static_cast<long> (glBND_yp_limit - glBND_yn_limit));
```
