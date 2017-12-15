echo Using Clang Tools to Refactoring the project > output.log

set PATH=%PATH%;C:\Windows\System32;LLVM\bin

echo Hello, there are some functions with this tool: 1. Rewrite the program 2. Clang-tidy checks with C++ STL without fixing 3. with fixing 

RewriteFileList.exe >> output.log
for /f "delims=" %%a in (Rewritefilelist.txt) do ( 
   set list=%%a
)

set /p option1=Whether rewrite the program: (y or n) 
echo whether write: >> output.log
echo %option1% >> output.log
 
if %option1%==y (
  ::y
  clang --version >>output.log 

  ClangExample.exe %list% >> output.log
)

move Rewritefilelist.txt RewriteOutput\ >> output.log

  for /f "delims=" %%b in (RewriteOutput\RewriteFileCopy.txt) do (
    set backuplist=%%b
  )
  %backuplist% 
  echo if rewrited: BackUp old code ok! >> output.log

  for /f "delims=" %%c in (RewriteOutput\RewriteFileCopy2.txt) do (
    set copylist=%%c
  )
  %copylist%
  echo need to use % copylist % , now // it 
  echo if rewrited: Renew the files with rewriter ok! >> output.log

set /p check=Whether using Clang-tidy to check the modernize of C++ STL (transfer into C++ 11)? (y: checking, n: without checking, f: checking and fixing) 

echo whether clang-tidy  (y: checking, n: without checking, f: checking and fixing >> output.log
echo %check% >> output.log

if %check%==y  (
::check
clang --version >>output.log 
clang-tidy --version >>output.log 
run-clang-tidy.py -checks='-*,moder*over*,read*braces*' >> output.log
run-clang-tidy.py -checks='-*,moder*over*,read*braces*' 
) else if %check%==f  (
::fix
run-clang-tidy.py -checks='-*,moder*over*,read*braces*' >> output.log
TidyBackUp.exe
echo check and backup check-problem file 
)
for /f "delims=" %%a in (BackUp\TidyBackupFile.txt) do ( 
   set listT=%%a
)
%listT:/=\%
echo BackUp Tidy

if %check%==f (
::ff
run-clang-tidy.py -checks='-*,moder*over*,read*braces*' -fix >> output.log
)

pause
exit


