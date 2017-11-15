#include <fstream>      // std::ofstream
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
#include "clang/AST/TypeVisitor.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

Rewriter rewriter;
int numFunctions = 0;


class ExampleVisitor : public RecursiveASTVisitor<ExampleVisitor> {
private:
    ASTContext *astContext; // used for getting additional AST info

public:
    explicit ExampleVisitor(CompilerInstance *CI) 
      : astContext(&(CI->getASTContext())) // initialize private members
    {
        rewriter.setSourceMgr(astContext->getSourceManager(), astContext->getLangOpts());
    }

    virtual bool VisitFunctionDecl(FunctionDecl *func) {
        numFunctions++;
        string funcName = func->getNameInfo().getName().getAsString();
        if (funcName == "do_math") {
            rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
            errs() << "** Rewrote function def: " << funcName << "\n";
        }    
        return true;
    }
	
    /*virtual bool VisitStmt(Stmt *st) {
		//errs() << "Stmt name: " << st->getStmtClassName() << "\n"; // stmt name
        if (ReturnStmt *ret = dyn_cast<ReturnStmt>(st)) {
            rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
			errs() << "** Rewrote ReturnStmt\n";
        }        
        if (CallExpr *call = dyn_cast<CallExpr>(st)) {
            //rewriter.ReplaceText(call->getLocStart(), 7, "add5");
            errs() << "** Rewrote function call\n";
        }
        return true;
    }*/

	virtual bool VisitCXXRecordDecl(CXXRecordDecl *cla)
	{
		//if (CXXConstructorDecl *cons = dyn_cast<CXXConstructorDecl>(cla)) {
		//	errs() << "OOOOOOOOOOOOO\n";
		//}
		if ((cla->getCanonicalDecl())->getNameAsString() == "Rectangle") {
			rewriter.ReplaceText(cla->getLocation(), 9, "RectangleShape");
		}
		return true;
	}


	bool VisitDeclRefExpr(DeclRefExpr *sta)
	{
		FullSourceLoc FullLocation = astContext->getFullLoc(sta->getLocStart());
		SourceManager &srcMgr = astContext->getSourceManager();
		//errs() << "FullLocation.isValid ?: " << FullLocation.isValid() <<", "<< (sta->getFoundDecl())->getNameAsString() <<"\n";
		if (FullLocation.isValid())
		{
			if ((sta->getFoundDecl())->getNameAsString() == "do_math") {
				rewriter.ReplaceText(sta->getLocStart(), 7, "add5");
			}
			if ((sta->getFoundDecl())->getNameAsString() == "val") {
				rewriter.ReplaceText(sta->getLocStart(), 3, "value");
			}
			if ((sta->getFoundDecl())->getNameAsString() == "rect") {
				rewriter.ReplaceText(sta->getLocStart(), 4, "rect_1");
			}
			// Print function or variable name
			//printf("stm: %-23s at %3u:%-3u in %-14s\n",
			//	(sta->getFoundDecl())->getNameAsString().c_str(),
			//	FullLocation.getSpellingLineNumber(),
			//	FullLocation.getSpellingColumnNumber(),
			//	srcMgr.getFilename(FullLocation).data());
		}
		return true;
	}
	bool VisitVarDecl(VarDecl *var) {
		//errs() << "VVVVVV!!!!: " << var->getType().getAsString()<< "\n";
		if (var->getType().getAsString() == "class Rectangle") {
			rewriter.ReplaceText(var->getTypeSpecStartLoc(), 9, "RectangleShape");
		}
		if ((var->getCanonicalDecl())->getNameAsString() == "val") {
			rewriter.ReplaceText((var->getLocation()), 3, "value");
		}
		if ((var->getCanonicalDecl())->getNameAsString() == "rect") {
			rewriter.ReplaceText(var->getLocation(), 4, "rect_1");
		}
		return true;
	}

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

	bool VisitCXXMethodDecl(CXXMethodDecl *set) {
		//errs() << "VVVVVV!!!!: " << set->getQualifiedNameAsString() << "\n";
		if (set->getNameAsString() == "set_values") {
			rewriter.ReplaceText(set->getLocation(), 10, "setXY");
			//rewriter.ReplaceText(set->getQualifiedNameAsString(), 1, "OOO");
		}
		if (set->getQualifiedNameAsString() == "Rectangle::set_values") {
			rewriter.ReplaceText(set->getQualifierLoc().getBeginLoc(), 9, "RectangleShape");
		}
		return true;
	}
	bool VisitMemberExpr(MemberExpr *mem) {
		if (mem->getMemberDecl()->getNameAsString() == "set_values") {
			rewriter.ReplaceText(mem->getMemberLoc(), 10, "setXY");
		}
		return true;
	}

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
    // override the constructor in order to pass CI
    explicit ExampleASTConsumer(CompilerInstance *CI)
        : visitor(new ExampleVisitor(CI)) // initialize the visitor
    { }

    // override this to call our ExampleVisitor on the entire source file
    virtual void HandleTranslationUnit(ASTContext &Context) {
        /* we can use ASTContext to get the TranslationUnitDecl, which is
             a single Decl that collectively represents the entire source file */
        visitor->TraverseDecl(Context.getTranslationUnitDecl());
    }

};

class ExampleFrontendAction : public ASTFrontendAction {
public:
	virtual std::unique_ptr<ASTConsumer> CreateASTConsumer (CompilerInstance &CI, StringRef file) {
		return std::make_unique<ExampleASTConsumer>(&CI);
	}

};


int main(int argc, const char **argv) {
	llvm::cl::OptionCategory optionCategory("tool options");
	CommonOptionsParser op(argc, argv, optionCategory);
	ClangTool Tool(op.getCompilations(), op.getSourcePathList());

	int result = Tool.run(newFrontendActionFactory<ExampleFrontendAction>().get());
	errs()<<"\nFound " << numFunctions << " functions.\n\n";
	rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(errs());
	//rewriter.overwriteChangedFiles(); //read in pointer is 0x000000 --error
	const RewriteBuffer *RewriteBuf = rewriter.getRewriteBufferFor(rewriter.getSourceMgr().getMainFileID());
	ofstream output("output.cpp");
	output << string(RewriteBuf->begin(), RewriteBuf->end()); 
	output.close();


	return result;
}


