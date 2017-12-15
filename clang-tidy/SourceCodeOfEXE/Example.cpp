#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>      // std::ofstream
#include <vector>
#include <string>
#include <map>
#include <direct.h>
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/StringRef.h"

#include "llvm/Support/FileSystem.h"
#include "clang/Basic/FileManager.h"
#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Rewrite/Frontend/Rewriters.h"
#include "clang/AST/TypeVisitor.h"
#include "clang/Basic/SourceLocation.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using std::vector;
using std::map;

//vector<Rewriter> rewriter;
int numFunctions = 0;
//string filename;
//ofstream output;
//string temp;
int nFile = 0;
std::map<int, const RewriteBuffer*> RewriteBufMap;
//const RewriteBuffer *RewriteBuf = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());

class ExampleVisitor : public RecursiveASTVisitor<ExampleVisitor> {
private:
	ASTContext *astContext; // used for getting additional AST info
	Rewriter rewriter; //
public:
	
	//Rewriter rewriter;
	//ASTContext &mContext;
	//std::set<FileID> mRewrittenFileIDs;
	//void markFileForCurrentDecl(Decl *d);
	//string file;
	//Rewriter rewriter;
	//ExampleVisitor(Rewriter &R, ASTContext &astContext)
	//	: rewriter(R), mContext(astContext) {} //
	explicit ExampleVisitor(CompilerInstance *CI)
		: astContext(&(CI->getASTContext())) // initialize private members
	{
		//errs() << "nFile~~~~~~~~~~~" << nFile;
		rewriter.setSourceMgr(astContext->getSourceManager(), astContext->getLangOpts());
	}
	//FileID fileID = astContext->getSourceManager().getMainFileID();
	
	int nRewrite = 0;
	int ismain = 0;
	int inFile = 0;
	virtual bool VisitFunctionDecl(FunctionDecl *func) {
		string funcName = func->getNameInfo().getName().getAsString();
		numFunctions++;
		clang::SourceLocation sourceLocation = func->getLocation();
		clang::SourceManager &sourceManager = rewriter.getSourceMgr();
		clang::FileID fileID = sourceManager.getFileID(sourceLocation);
		//mRewrittenFileIDs.insert(fileID);
		if (astContext->getSourceManager().isInMainFile(func->getLocStart())) { inFile = 1; }
		if (funcName == "main") {
			ismain = 1;
		}
		//if (inFile == 1) {
			//errs() << "ismain: "<< ismain<<", Found " << numFunctions << " functions.\n\n";
			//errs() << "=====??====fileID: " << fileID.getHashValue() <<", fun name:"<< funcName <<"\n";
			//rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(errs());
			//system("PAUSE");
		//}
		/*if (funcName == "do_math" && inFile == 1) {
			rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
			RewriteBufMap[nFile] = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());
			nRewrite++;
			//errs() << "** Rewrote function def: " << funcName << "\n";
		}*/
		return true;
	}
	int isfor = 0;
	int isview = 0;
	int isvar = 0;

	virtual bool VisitStmt(Stmt *st) {
		//errs() << "Stmt name: " << st->getStmtClassName() << "\n"; // stmt name
		if (ForStmt *ret = dyn_cast<ForStmt>(st)) {
			isview += 1;
			isfor = isview;
			//errs() << "isfor: " << isfor << "\n";
			//rewriter.ReplaceText(ret->getLocStart(), 0, "000");
		}
		return true;
	}

	/*bool VisitVarDecl(VarDecl *var) {
		//errs() << "VVVVVV!!!!: " << var->getType().getAsString()<< "\n";
		if ((var->getCanonicalDecl())->getNameAsString() == "val" && inFile == 1) {
			rewriter.ReplaceText((var->getLocation()), 3, "value");
			RewriteBufMap[nFile] = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());
			nRewrite++;
		}
		return true;
	}*/
	vector <string> st_DeclRefExpr;
	vector <string> st_DeclRefExpr_type;
	int isfab = 0;
	int nDeclRefExpr = 0;
	int islongdouble = 0;
	int nView = 0;
	bool VisitDeclRefExpr(DeclRefExpr *sta)
	{
		FullSourceLoc FullLocation = astContext->getFullLoc(sta->getLocStart());
		SourceManager &srcMgr = astContext->getSourceManager();
		//errs() << "FullLocation.isValid ?: " << FullLocation.isValid() <<", "<< (sta->getFoundDecl())->getNameAsString() <<"\n";
		if (FullLocation.isValid())

		{
			/*if ((sta->getFoundDecl())->getNameAsString() == "do_math" && inFile == 1) {
				rewriter.ReplaceText(sta->getLocStart(), 7, "add5");
				RewriteBufMap[nFile] = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());


				nRewrite++;
			}
			if ((sta->getFoundDecl())->getNameAsString() == "val" && inFile == 1) {
				rewriter.ReplaceText(sta->getLocStart(), 3, "value");
				RewriteBufMap[nFile] = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());

				nRewrite++;
			}*/
			nView += 1;
			nDeclRefExpr += 1;
			//if (ismain ==1) { errs() << "DeclRefExpr! nView: " << nView << "==="<< (sta->getFoundDecl())->getNameAsString() <<"\n"; }
			st_DeclRefExpr.push_back((sta->getFoundDecl())->getNameAsString());
			st_DeclRefExpr_type.push_back(sta->getType().getAsString());
			//errs() << "DeclRefExpr: " << (sta->getFoundDecl())->getNameAsString() << ", " << st_DeclRefExpr[nDeclRefExpr - 1] << "\n";
			if ((sta->getFoundDecl())->getNameAsString() == "fabs" && inFile == 1) {
				//errs() << "@@@ fabs type=" << sta->getType().getAsString()<<"=\n";
				if (sta->getType().getAsString() == "long double (long double) noexcept") {
					//errs() << "@@@ fabs type=" << sta->getType().getAsString()<<"=\n";
					islongdouble = 1;
				}
				else {
					islongdouble = 0;
				}
				isfab = nDeclRefExpr;
			}
			if (nDeclRefExpr == isfab + 1 && isfab != 0 && islongdouble == 1 ) {
				nRewrite++;
				rewriter.ReplaceText(sta->getLocStart(), 0, "static_cast<" + st_DeclRefExpr_type[nDeclRefExpr - 3] + "> ("); // "static_cast<double> ("
				RewriteBufMap[nFile] = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());
			}

			if (nDeclRefExpr == isfab + 2 && isfab != 0 && islongdouble == 1) {
				//errs() << nView << " =nView \n";
				//if (sta->getType().getAsString() == "long double") { errs() << st_DeclRefExpr[nDeclRefExpr-1]+")" <<"\n"; }
				nRewrite++;
				rewriter.ReplaceText(sta->getLocStart(), st_DeclRefExpr[nDeclRefExpr - 1].size(), st_DeclRefExpr[nDeclRefExpr - 1] + ")"); // "glBND_yn_limit)"
				//rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(errs());

				RewriteBufMap[nFile] = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());
			}
		}
		return true;
	}
	/*bool VisitReturnStmt(ReturnStmt *re) {
		//if (nRewrite > 0) { errs() << "returnStmt\n"; }
		//system("PAUSE");
		//rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(errs());
		//errs() << "path: " << std::string("output/" + filename) << "\n";
		//errs() << "!!\n";
		if (nRewrite > 0 && ismain ==1) {
			ofstream output(std::string("output/" + filename));
			//errs()  << "ismain: "<<ismain <<", "<< rewriter.getRangeSize() << "\n";
			const RewriteBuffer *RewriteBuf = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());
			output << string(RewriteBuf->begin(), RewriteBuf->end());
			output.close();
			errs() << "save the rewrite program in path: " << std::string("output/" + filename) << "\n";
		}
		return true;
	}*/
	/*bool VisitFloatingLiteral(FloatingLiteral *b) {
	nView += 1;
	if (ismain == 1) {
	errs() << "FloatingLiteral! n: " << nView << "\n";
	}
	return true;
	} */
	/*bool VisitCXXConstructorDecl(CXXConstructorDecl *c) {//!!!????
	//errs() << "=========!!!!" << "\n";
	//if (cl->getNameAsString() == "Rectangle") {
	//rewriter.ReplaceText(cl->getLocation(), 9, "RectangleShape");
	//}
	//return true;
	//}*/
	//bool VisitParmVarDecl(ParmVarDecl *par) {
	//errs() << "VVVVVV!!!!: " << par->getDeclName() << "\n";
	//if (par->getType().getAsString() == "class Rectangle *") {
	//	rewriter.ReplaceText(par->getLocation(), 1, "HHH");
	//}
	//return true;
	//}
	/*
	virtual bool VisitReturnStmt(ReturnStmt *ret) {
	rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
	errs() << "** Rewrote ReturnStmt\n";
	return true;
	}

	virtual bool VisitCallExpr(CallExpr *call) {
	rewriter.ReplaceText(call->getLocStart(), 7, "add5");
	errs() << "** Rewrote function call\n";
	return true;
	}
	*/
};



class ExampleASTConsumer : public ASTConsumer {
private:
	ExampleVisitor *visitor; // doesn't have to be private
public:
	//ExampleVisitor visitor;
	// override the constructor in order to pass CI
	explicit ExampleASTConsumer(CompilerInstance *CI)
		: visitor(new ExampleVisitor(CI)) // initialize the visitor
	{
		nFile++;
		//errs() << "~~~~~~nFile:" << nFile<<"\n";

	}
	//ExampleASTConsumer(Rewriter &rewriter, ASTContext &astContext)
		//: visitor(rewriter, astContext) {}
	//virtual bool HandleTopLevelDecl(DeclGroupRef d);
	// override this to call our ExampleVisitor on the entire source file
	virtual void HandleTranslationUnit(ASTContext &Context) {
		/* we can use ASTContext to get the TranslationUnitDecl, which is
		a single Decl that collectively represents the entire source file */
		visitor->TraverseDecl(Context.getTranslationUnitDecl());
	}
};

class ExampleFrontendAction : public ASTFrontendAction {
public:

	virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
		return std::make_unique<ExampleASTConsumer>(&CI);
	}
};


int main(int argc, const char **argv) {
	std::string fileName(argv[argc - 1]);
	//errs() << "==argv[argc-1]: " << argv[argc - 1];
	/*CompilerInstance compiler;
	compiler.createFileManager();
	compiler.createSourceManager(compiler.getFileManager());
	//HeaderSearchOptions &headerSearchOptions = compiler.getHeaderSearchOpts();
	//AddPlatformSpecificHeaders(headerSearchOptions);
	compiler.createASTContext();
	// Initialize rewriter
	Rewriter rewriter;
	clang::SourceManager &sourceManager = compiler.getSourceManager();
	rewriter.setSourceMgr(sourceManager, compiler.getLangOpts());
	const FileEntry *pFile = compiler.getFileManager().getFile(fileName);
	sourceManager.setMainFileID(
		sourceManager.createFileID(pFile, clang::SourceLocation(),
			clang::SrcMgr::C_User));
	compiler.getDiagnosticClient().BeginSourceFile(compiler.getLangOpts(),
		&compiler.getPreprocessor());

	ASTContext &astContext = compiler.getASTContext();
	ExampleASTConsumer astConsumer(&compiler);
	*/
	/*for (FileID currFileID : astConsumer->visitor.mRewrittenFileIDs)
	{
		const clang::FileEntry *fileEntry = sourceManager.getFileEntryForID(currFileID);
		if (!fileEntry) {
			errs() << "OOPS, failed to find the file entry for fileID\n";
			continue;
		}

		//const string fname = fileEntry->getName();
		std::string sFname = fileEntry->getName();
		//if (shouldIgnorePath(sFname)) {
		//	continue;
		//}
		dumpRewrittenCodeForFile(currFileID, sFname, rewriter);
	}*/


	//Rewriter rewriter;
	llvm::cl::OptionCategory optionCategory("tool options");
	//errs() << "argc = " << argc;
	//system("PAUSE");
	// parse the command-line args passed to your code
	CommonOptionsParser op(argc, argv, optionCategory);
	// create a new Clang Tool instance (a LibTooling environment)
	ClangTool Tool(op.getCompilations(), op.getSourcePathList());
	//errs() << "sourcePathList0: "<< op.getSourcePathList()[0];
	//errs() << "sourcePathList1: " << op.getSourcePathList()[1];
	//errs() << "sourcePathList2: " << op.getSourcePathList()[2];
	//errs() << "sourcePathList3: " << op.getSourcePathList()[3];

	int result = Tool.run(newFrontendActionFactory<ExampleFrontendAction>().get());
	//errs() << "\nFound " << numFunctions << " functions. =======================\n\n";
	//errs() << "0000000000000000 size:"<< RewriteBufMap.size();
	//ofstream outputNoRewrite(std::string("NoRewriteFile.txt"));
	string filepath2 = "RewriteOutput/"; _mkdir(filepath2.c_str());
	ofstream outputRewrite(std::string("RewriteOutput/RewriteFile.txt"));
	ofstream outputRewriteCP(std::string("RewriteOutput/RewriteFileCopy.txt"));
	ofstream outputRewriteCP2(std::string("RewriteOutput/RewriteFileCopy2.txt"));

	for (int i = 1; i <= RewriteBufMap.size(); ++i) {
		//errs() << "\n~~~~~~~~~~~~i = " << i<<", filename: "<< op.getSourcePathList()[i-1] <<"\n";
		if (RewriteBufMap[i] == NULL) {
			errs() << "\n input files without rewrite:    "<< op.getSourcePathList()[i - 1];
			//outputNoRewrite << op.getSourcePathList()[i - 1]<<"\n";
		}
		if (RewriteBufMap[i] != NULL) {
			//errs() << string(RewriteBufMap[i]->begin(), RewriteBufMap[i]->end());
			string filename = op.getSourcePathList()[i - 1];
			//errs() << "\nfile: " << filename<<"\n";
			// a = "a";
			int pathN = 0; //      src/src/x.cpp -> pathN=2 
			vector<int> position; // position of '/' in path
			for (int i = 0; i < filename.size(); ++i) {
				//errs() << filename[i] << "\n";
				string dash = "\\";
				string dash2 = "/";
				//errs() << "\n dash0000000"<<dash[0]<<" =====filename[i] "<<filename[i];
				if (filename[i] == dash[0] || filename[i] == dash2[0]) { position.push_back(i); pathN++; //errs() << "\n !!!!!!!!!!pathN" << pathN; 
				}
			}
			//const int n = position[pathN - 1];
			string BackUpPath;
			if (pathN > 0) {
				string filepath = filename.substr(0, position[pathN - 1]+1);
				string filepath2 = std::string("RewriteOutput/" + filepath);
				BackUpPath = std::string("BackUp/" + filepath);
				//errs() << "\n~~~~filepath:   " << filepath2 << "\n";
				_mkdir(filepath2.c_str());
			}
			//string filepath2 = std::string("output/" + filepath);
			/*(if (pathN > 0){// filepath = filename[0]~filename[position[pathN-1]]
				//errs() << "\n pathN >0 !!!!! ";
				for (int j = 0; j <= position[pathN - 1]; ++j) { 
					errs() << "\n filename[j]:" << filename[j];
					filepath[j] = filename[j]; errs() <<"\n!!!"<< filepath[j] << "\n";
				}
				filepath2 = std::string("output/" + filepath);
			}*/
			if (pathN == 0) { string filepath2 = "RewriteOutput/"; _mkdir(filepath2.c_str());
				BackUpPath = "BackUp/";
			}
			//errs() << "\n~~~~BackUp path:   " << BackUpPath << "\n";
			ofstream output(std::string("RewriteOutput/" + filename));
			output << string(RewriteBufMap[i]->begin(), RewriteBufMap[i]->end());
			output.close();
			outputRewrite << filename << "\n"; // path with /
			//change path / to 
			string CPpath = op.getSourcePathList()[i - 1]; //filename
			string BackUpPath2 = BackUpPath;
			for (int k = 0; k < op.getSourcePathList()[i - 1].size(); ++k)
			{
				string c = "/"; string cc = "\\";
				if (filename[k] != c[0]) { CPpath[k] = filename[k]; }
				if (filename[k] == c[0]) { CPpath[k] = cc[0]; }
				//errs()<<"CPpath: "<< CPpath<<"\n";
			}
			string CPpath_output = std::string("RewriteOutput\\" + CPpath);
			for (int k = 0; k < BackUpPath.size(); ++k)
			{
				string c = "/"; string cc = "\\";
				if (BackUpPath[k] != c[0]) { BackUpPath2[k] = BackUpPath[k]; }
				if (BackUpPath[k] == c[0]) { BackUpPath2[k] = cc[0]; }
				//errs() << "BackUppath: " << BackUpPath2 << "\n";
			}
			if (i < RewriteBufMap.size()) { 
				outputRewriteCP << "copy /Y " << CPpath << " " << BackUpPath2 << " && ";
				outputRewriteCP2 << "copy /Y " << CPpath_output << " .\\" << CPpath << " && ";
			}
			if (i == RewriteBufMap.size()) { 
				outputRewriteCP << "copy /Y " << CPpath << " " << BackUpPath2; 
				outputRewriteCP2 << "copy /Y " << CPpath_output << " .\\" << CPpath;
			}
			errs() << "\n rewrite with fabs(static_cast<long/double>...) done into output/" << op.getSourcePathList()[i - 1];
		}
	}
	//outputNoRewrite.close();
	outputRewrite.close();
	outputRewriteCP.close();
	outputRewriteCP2.close();
	return result;

}


