#include <string>
#include <vector>
#include <map>

using namespace std;

class ASTProg;
class ASTnode;
class ASTDeclaration;
class ASTVarDecl;
class ASTFuncDecl;
class ASTVariableDecl;
class ASTVarDeclSingle;
class ASTFunctionDecl;
class ASTParamList;
class ASTParamSingle;
class ASTBlock;

class ASTStatement;
class ASTAssignstat;
class ASTFuncstat;
class ASTControlstat;
class ASTForstat;
class ASTWhilestat;
class ASTReturnstat;
class ASTBreakstat;
class ASTDeclstat;

class ASTExpr;
class ASTExprLocation;
class ASTExprFunc;
class ASTExprUnary;
class ASTExprBinary;
class ASTExprTernary;
class ASTExprId;
class ASTExprLiteral;

class ASTLocation;
class ASTFunctionCall;
class ASTInputList;
class ASTIfElseBlock;
class ASTIfBlock;
class ASTElseBlock;
class ASTElifBlock;
class ASTForBlock;
class ASTWhileBlock;
class ASTReturnStmt;

class ASTvisitor{
    public:
         virtual void visit(ASTProg &node)=0;
         virtual void visit(ASTDeclaration &node)=0;
         virtual void visit(ASTVarDecl &node)=0;
         virtual void visit(ASTFuncDecl &node)=0;
         virtual void visit(ASTVariableDecl &node)=0;
         virtual void visit(ASTVarDeclSingle &node)=0;
         virtual void visit(ASTFunctionDecl &node)=0;
         virtual void visit(ASTParamList &node)=0;
         virtual void visit(ASTParamSingle &node)=0;
         virtual void visit(ASTBlock &node)=0;

         virtual void visit(ASTStatement &node)=0;
         virtual void visit(ASTAssignstat &node)=0;
         virtual void visit(ASTFuncstat &node)=0;
         virtual void visit(ASTControlstat &node)=0;
         virtual void visit(ASTForstat &node)=0;
         virtual void visit(ASTWhilestat &node)=0;
         virtual void visit(ASTReturnstat &node)=0;
         virtual void visit(ASTBreakstat &node)=0;
         virtual void visit(ASTDeclstat &node)=0;

         virtual void visit(ASTExpr &node)=0;
         virtual void visit(ASTExprLocation &node)=0;
         virtual void visit(ASTExprFunc &node)=0;
         virtual void visit(ASTExprUnary &node)=0;
         virtual void visit(ASTExprBinary &node)=0;
         virtual void visit(ASTExprTernary &node)=0;
         virtual void visit(ASTExprId &node)=0;
         virtual void visit(ASTExprLiteral &node)=0;

         virtual void visit(ASTLocation &node)=0;
         virtual void visit(ASTFunctionCall &node)=0;
         virtual void visit(ASTInputList &node)=0;
         virtual void visit(ASTIfElseBlock &node)=0;
         virtual void visit(ASTIfBlock &node)=0;
         virtual void visit(ASTElseBlock &node)=0;
         virtual void visit(ASTElifBlock &node)=0;
         virtual void visit(ASTForBlock &node)=0;
         virtual void visit(ASTWhileBlock &node)=0;
         virtual void visit(ASTReturnStmt &node)=0;
};

class DataTypeInfo{
    public:
        bool isArray1=false;
        bool isArray2=false;
};

class ASTnode{
    public:
        virtual ~ASTnode(){}
    // string name="";
    // ASTnode* parent=nullptr;
    // map<string,ASTVarDeclSingle*>variables;
    virtual void accept(ASTvisitor &V) = 0;
};

class ASTProg : public ASTnode{
    public:
        vector<ASTDeclaration*> decl;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTDeclaration : public ASTnode{
    public:
        virtual ~ASTDeclaration(){}
        virtual void accept(ASTvisitor &v)=0;
};

class ASTVarDecl : public ASTDeclaration{
    public:
        ASTVariableDecl* var_decl;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTFuncDecl : public ASTDeclaration{
    public:
         ASTFunctionDecl* func_decl;
         virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTVariableDecl : public ASTnode{
    public:
        vector<ASTVarDeclSingle*> var_decl_single;
        string type;
        ASTVariableDecl(string typeVal){
            type=typeVal;
        }
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTVarDeclSingle : public ASTnode{
    public:
        string id;
        vector<ASTExpr*> exprs;
        ASTExpr* val=nullptr;
        ASTVarDeclSingle(string id_val){
            id=id_val;
        }
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }

};

class ASTFunctionDecl : public ASTnode{
    public:
        string id;
        string type;
        ASTBlock* block=nullptr;
        ASTParamList* param_list=nullptr;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTParamList : public ASTnode{
    public:
        vector<ASTParamSingle*> params;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTParamSingle : public ASTnode{
    public:
        string type;
        ASTVarDeclSingle* var;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }     
};

class ASTBlock : public ASTnode{
    public:
        vector<ASTStatement*> statements;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTStatement : public ASTnode{
    public:
        virtual ~ASTStatement(){

        }
        virtual void accept(ASTvisitor &v){

        }
        
};

class ASTAssignstat : public ASTStatement{
    public:
        ASTLocation* lhs;
        ASTExpr* rhs;
        string op;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTFuncstat : public ASTStatement{
    public:
        ASTFunctionCall* func_call;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTControlstat : public ASTStatement{
    public:
        ASTIfElseBlock* if_else_block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTIfElseBlock : public ASTnode{
    public:
        ASTIfBlock* if_block;
        vector<ASTElifBlock*> elif_block;
        ASTElseBlock* else_block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTIfBlock : public ASTnode{
    public:
        ASTExpr* expr;
        ASTBlock* block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTElifBlock : public ASTnode{
    public:
        ASTExpr* expr;
        ASTBlock* block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTElseBlock : public ASTnode{
    public:
        ASTBlock* block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTForBlock : public ASTnode{
    public:
        vector<ASTStatement*> for_1_and_3;
        ASTExpr* for_2;
        ASTBlock* block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTWhileBlock : public ASTnode{
    public:
        ASTExpr* expr;
        ASTBlock* block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTForstat : public ASTStatement{
    public:
        ASTForBlock* for_block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTWhilestat : public ASTStatement{
    public:
        ASTWhileBlock* while_block;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTBreakstat : public ASTStatement{
    public:
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }   
};

class ASTReturnstat : public ASTStatement{
    public:
        ASTReturnStmt* ret_stat;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTReturnStmt : public ASTnode{
    public:
        ASTExpr* expr=nullptr;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTDeclstat : public ASTStatement{
    public:
        ASTVariableDecl* var_decl;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTExpr : public ASTnode{
    public:
        string type;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTLocation : public ASTnode{
    public:
        string id;
        vector<ASTExpr*> expr;
        ASTLocation(string id_val){
            id=id_val;
        }
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTFunctionCall : public ASTnode{
    public:
        string id;
        ASTInputList* input_list=nullptr;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTInputList : public ASTnode{
    public:
        vector<ASTExpr*> expression_list;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTExprLocation : public ASTExpr{
    public:
        ASTLocation* loc;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTExprFunc : public ASTExpr{
    public:
        ASTFunctionCall* func_call;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }  
};

class ASTExprUnary : public ASTExpr{
    string unary_op;
    ASTExpr* expr;
    public:
        ASTExprUnary(string op_val,ASTExpr* expr_val){
            unary_op=op_val;
            expr=expr_val;
        }
        ASTExpr* getExpr(){
            return expr;
        }

        string getOp(){
            return unary_op;
        }
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        } 
};

class ASTExprBinary : public ASTExpr{
    string binary_op;
    ASTExpr* left;
    ASTExpr* right;
    public:
        ASTExprBinary(string op_val,ASTExpr* left_val,ASTExpr* right_val){
            binary_op=op_val;
            left=left_val;
            right=right_val;
        }
        ASTExpr* getLeftExpr(){
            return left;
        }
        ASTExpr* getRightExpr(){
            return right;
        }

        string getOp(){
            return binary_op;
        }
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        } 
};

class ASTExprTernary : public ASTExpr{
    ASTExpr *first;
    ASTExpr *second;
    ASTExpr *third;

    public:
        ASTExprTernary(ASTExpr *first, ASTExpr *second, ASTExpr *third) : first(first), second(second), third(third) {}

        ASTExpr *getFirst(){
            return first;
        }

        ASTExpr *getSecond(){
            return second;
        }

        ASTExpr *getThird(){
            return third;
        }

        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTExprId : public ASTExpr{

    string id;

    public:
        ASTExprId(string id) : id(id) {}

        string getID(){
            return id;
        }

        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTExprLiteral : public ASTExpr{
    public:
        int int_val;
        float float_val;
        string string_val;
        char char_val;
        bool bool_val;
        virtual void accept(ASTvisitor &v){
            v.visit(*this);
        }
};

class ASTContext{
    public:
        ASTnode *root;

        ~ASTContext(){
            clearAST();
        }

        /// free all saved expression trees
        void clearAST(){
            delete root;
        }
};



