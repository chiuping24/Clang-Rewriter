# Clang_Rewriter
Using LLVM Clang API to rewrite the program with
1. Windows 10
2. Visual studio 2015
3. [good reference](https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/) (and good comment  of *Joshua*) 

#### LLVM Clang Installation (Using visual studio)
[Installation guide](https://clang.llvm.org/get_started.html)  
(Another choice for using Clang:)[official pre-build binary](http://releases.llvm.org/download.html)  But I can not found the overall lib that we need in Clang Rewriter API.

```
I build it from the souce code using visual studio (with CMake).  
So I get the newest version Clang 6.0.0 (non-full-released).  
It may be too new to support all other Clang tools.  
  
總結來說, 基本上LLVM/Clang安裝方法有二:  
1. Build from source code, 可從 LLVM Download Page 中找到對應版本的source code,   
   不用官網教學守則的svn, 因為這樣會拿到最新版但尚未release的版本,有些extra-tools 尚未支援  
2. Pre-build binary 中下載就是已經build好的Clang 執行檔,可以直接使用Clang compiler和extra tools 像是Clang-tidy,  
   但我在裡面找不到很多開發用的.lib, 像是使用Clang API做Rewriter就需要那些從Source code build出來的.lib  
           
以上兩點, 可依照自己需要的功能做選擇  
這邊使用 Clang Rewriter 所以選擇方法1. source code building  
順帶一提,官網說Visual Studio支援 2013版本以上 ,但其實是需要對應的Clang版本,  
(若要使用VS2013 請選擇3.9.0以前的source code安裝)  

```

After the installation (CMake and build the VS solution), you will get several .h .lib ... Clang API  
which is used in the following Rewriter.  


#### Also, Clang compilfer can be used in the terminal:
1. using clang compiler: $ clang, windows bash shell: $ clang.exe 
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
#### Rewrite the program according to Example.cpp 
* The Clang AST structure is important to know before rewriting. [(Ref1)](http://swtv.kaist.ac.kr/courses/cs453-fall13/Clang%20tutorial%20v4.pdf) [(Ref2)](https://llvm.org/devmtg/2013-04/klimek-slides.pdf)
* [ASTFrontendAction](http://clang.llvm.org/doxygen/classclang_1_1ASTFrontendAction.html)  
* [ASTConsumer](http://clang.llvm.org/doxygen/classclang_1_1ASTConsumer.html)  
* [RecursiveASTVisitor](http://clang.llvm.org/doxygen/classclang_1_1RecursiveASTVisitor.html)  
* How to write RecursiveASTVisitor based ASTFrontendActions? [(Clang official tutorial)](http://clang.llvm.org/docs/RAVFrontendAction.html)  
* [Rewriter](http://clang.llvm.org/doxygen/classclang_1_1Rewriter.html)  
* There are several replacements in my Example.cpp such as function/variable/class name, function/variable/class call, class name of member function `(Rectangle::set --> RectangleShape::set)` and so on. Briefly example of rewriter in ASTVisitor for `Rectangle::set --> RectangleShape::set` :

```C++
class ExampleVisitor : public RecursiveASTVisitor<ExampleVisitor> {
private:
    ASTContext *astContext; // used for getting additional AST info

public:
    explicit ExampleVisitor(CompilerInstance *CI) 
      : astContext(&(CI->getASTContext())) // initialize private members
    {
        rewriter.setSourceMgr(astContext->getSourceManager(), astContext->getLangOpts());
    }
	bool VisitCXXMethodDecl(CXXMethodDecl *set) {
		if (set->getQualifiedNameAsString() == "Rectangle::set_values") {
			rewriter.ReplaceText(set->getQualifierLoc().getBeginLoc(), 9, "RectangleShape");
		}
		return true;
	}
};
```
  
* The AST naming (ex: expression type) may be different in different pc (visual studio environment). It's because When Clang compiles C++ code for Windows, it attempts to be compatible with MSVC. [(ref: MSVC compatibility)](https://clang.llvm.org/docs/MSVCCompatibility.html) 

#### Build and run Example.cpp in VS2015 with the setting correctly:   
1. Properties/C C++/General/Additional include directory  
    C:\llvm\tools\clang\include  
    C:\build_Win64\tools\clang\include  
    C:\build_Win64\include  
    C:\llvm\include 
    
2. Properties/Linker/General/Additional library directory  
    C:\build_Win64\Release\lib
      
3. Properties/Linker/input/Additional Dependencies  
    all .lib (I don't know the exactly used lib, so I put all I have in C:\build_Win64\Release\lib .)  

(There are some errors in VS building, such as unsigned -U issue. It works with removing "-".)
After successful building with VS, .exe file is computed.  
Then you can rewrite the program (ex: test3.cpp) according to your design in Example.cpp  
```
$ ExampleRewriter.exe test3.cpp -- 
```

output.cpp is the code which is generated after rewrite.  

#### Clang extra tool: clang-tidy 
More information is described in the document [clang-tidy](https://github.com/chiuping24/Clang_Rewriter/tree/master/clang-tidy)
