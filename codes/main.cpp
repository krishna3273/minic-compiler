#include <iostream>

#include "antlr4-runtime.h"
#include "MinicLexer.cpp"
#include "MinicParser.cpp"

#include "MinicBuildASTVisitor.h"

// #include "PostfixVisitor.h"
//#include "ast.h"

using namespace std;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;

    cout << "Processing input file " << argv[1] << endl;
    stream.open(argv[1]);
    
    ANTLRInputStream input(stream);

    MinicLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    MinicParser parser(&tokens);    

    MinicParser::ProgContext *ctx = parser.prog();

    MinicVisitor *visitor = new MinicBuildASTVisitor();

    ASTProg *program_root = visitor->visitProg(ctx);
    
    // PostFixVisitor *pv = new PostFixVisitor();
    // pv->visit(*program_root);

    return 0;
}
