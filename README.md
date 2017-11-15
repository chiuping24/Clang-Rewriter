# Clang_Rewriter
Using LLVM Clang API to rewrite the program.

#### I am using:
1. Windows 10
2. Visual studio 2015

#### Installation guide: (Using visual studio)
https://clang.llvm.org/get_started.html

After the installation (CMake and build the VS solution), you will get several .h .lib ... Clang API
which is used in the following Rewriter.

##### Also, Clang compilfer can be used in the terminal:
>clang --version
>>clang version 6.0.0 (trunk 316540)  
>>Target: x86_64-pc-windows-msvc  
>>Thread model: posix  
>>InstalledDir: C:\build_Win64\Release\bin




#### Build and run Example.cpp in VS2015 with the setting correctly:   
1. Properties/C C++/General/Additional include directory  
    C:\llvm\tools\clang\include  
    C:\build_Win64\tools\clang\include  
    C:\build_Win64\include  
    C:\llvm\include 
    
2. Properties/Linker/General/Additional library directory  
    C:\build_Win64\Release\lib
    
After   



#### Reference:
https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/  
(The comment of Joshua is also good for reference.)
