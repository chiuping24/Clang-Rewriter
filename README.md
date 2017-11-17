# Clang_Rewriter
Using LLVM Clang API to rewrite the program with
1. Windows 10
2. Visual studio 2015
3. [good reference](https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/) (and good comment  of *Joshua*) 

##### LLVM Clang Installation (Using visual studio)
[Installation guide](https://clang.llvm.org/get_started.html)  

After the installation (CMake and build the VS solution), you will get several .h .lib ... Clang API  
which is used in the following Rewriter.  


##### Also, Clang compilfer can be used in the terminal:
1. using clang compiler: $ clang, windows bash shell: $clang.exe 
```
$ clang --version  
clang version 6.0.0 (trunk 316540)  
Target: x86_64-pc-windows-msvc  
Thread model: posix  
InstalledDir: C:\build_Win64\Release\bin    

$ clang test.cpp  
$ ./a.exe  
```
2. check clang AST:
```
$ clang -Xclang -ast-dump -fsyntax-only test.cpp   
```
3. Using clang to check C++ version Stdlib, it shows the suggestion/error of difference C++ STL version.
```
$ clang++ -std=c++11 -stdlib=libc++ test.cpp
```
##### Rewrite the program according to Example.cpp with Clang 
* [ASTFrontendAction](http://clang.llvm.org/doxygen/classclang_1_1ASTFrontendAction.html)  
* [ASTConsumer](http://clang.llvm.org/doxygen/classclang_1_1ASTConsumer.html)  
* [RecursiveASTVisitor](http://clang.llvm.org/doxygen/classclang_1_1RecursiveASTVisitor.html)  
* How to write RecursiveASTVisitor based ASTFrontendActions? [(Clang official tutorial)](http://clang.llvm.org/docs/RAVFrontendAction.html)  
* [Rewriter](http://clang.llvm.org/doxygen/classclang_1_1Rewriter.html)

##### Build and run Example.cpp in VS2015 with the setting correctly:   
1. Properties/C C++/General/Additional include directory  
    C:\llvm\tools\clang\include  
    C:\build_Win64\tools\clang\include  
    C:\build_Win64\include  
    C:\llvm\include 
    
2. Properties/Linker/General/Additional library directory  
    C:\build_Win64\Release\lib

(There are some errors in VS building, such as unsigned -U issue. It works with removing "-".)
After successful building with VS, .exe file is computed.  
Then you can rewrite the program (ex: test3.cpp) according to your design in Example.cpp  
```
$ Example.exe test3.cpp  
```

output.cpp is the code which is generated after rewrite.  


