#include<iostream>
#include "ast.h"
#include<vector>
#include "MinicVisitor.h"
#include "symbolTable.h"
// #include "MinicParser.h"

using namespace std;

class MinicBuildASTVisitor : public MinicVisitor{
public:
    symbolTable* globalScope=new symbolTable();
    symbolTable* currScope=globalScope;
    int funcCount=0;
    virtual antlrcpp::Any visitProg(MinicParser::ProgContext *context){
        cout << "In visitProg" << endl;
        ASTProg *node = new ASTProg();
        for(auto curr:context->declaration()){
            ASTDeclaration* decl_node;
            decl_node=visit(curr);
            if(decl_node!=nullptr){
                node->decl.push_back(decl_node);
            }
        }
        return (ASTProg *) node;
    }

    virtual antlrcpp::Any visitVarDecl(MinicParser::VarDeclContext* context){
        cout<<"In visitVarDecl"<<endl;
        ASTVarDecl* node=new ASTVarDecl();
        node->var_decl=visit(context->variableDecl());
        return (ASTDeclaration*)node;
    }

    virtual antlrcpp::Any visitFuncDecl(MinicParser::FuncDeclContext* context){
        cout<<"In visitFuncDecl"<<endl;
        ASTFuncDecl* node=new ASTFuncDecl();
        node->func_decl=visit(context->functionDecl());
        return (ASTDeclaration*)node;
    }

    virtual antlrcpp::Any visitVariableDecl(MinicParser::VariableDeclContext* context){
        cout<<"In visitVariableDecl"<<endl;
        ASTVariableDecl* node;
        string type=context->Type()->getText();
        if(context->Type())
            node=new ASTVariableDecl(type);
        // if(context->varDeclSingle(0)){
            ASTVarDeclSingle *varNode;

            for (auto curr : context->varDeclSingle()){
                varNode = visit(curr);
                if (varNode != nullptr){
                    node->var_decl_single.push_back(varNode);
                    string id=varNode->id;
                    if (currScope->var_map.find(id) == currScope->var_map.end()){
                        if(varNode->val!=nullptr){
                            string rtype=varNode->val->type;
                            // cout<<"rtype "<<rtype<<endl;
                            if(type!=rtype){
                                cout<<"Type Mismatch-1"<<endl;
                                return nullptr;
                            }
                        }
                        else{
                            // cout<<varNode->exprs.size()<<" krishna"<<endl;
                            if(varNode->exprs.size()==1){
                                ASTExpr* tempNode=varNode->exprs[0];
                                if(tempNode->type!="int"){
                                    cout<<"Array size must be integer"<<endl;
                                    return nullptr;
                                }
                            }
                            if(varNode->exprs.size()==2){
                                ASTExpr* tempNode1=varNode->exprs[0];
                                ASTExpr* tempNode2=varNode->exprs[1];
                                if(tempNode1->type!="int" || tempNode2->type!="int"){
                                    cout<<"Array sizes must be integers"<<endl;
                                    return nullptr;
                                }
                            }
                        }
                        currScope->var_map[id]={type,""};
                    }
                    else{
                        cout<<"variable redeclared in current scope"<<" "<<id<<endl;
                        return nullptr;
                    }
                }
            }
            // cout<<"krishna is happy"<<endl;
        // }
        return node;
    }

    virtual antlrcpp::Any visitFunctionDecl(MinicParser::FunctionDeclContext* context){
        cout<<"In visitFunctionDecl"<<endl;
        ASTFunctionDecl* node =new ASTFunctionDecl();
        if(context->Type())
            node->type=context->Type()->getText();
        else
            node->type="void";
        if(context->ID())
            node->id=context->ID()->getText();
        if(currScope->func_retmap.find(node->id) == currScope->func_retmap.end()){
            currScope->func_retmap[node->id]=node->type;
        }
        else{
            cout<<"Function redeclared"<<endl;
            return nullptr;
        }
        symbolTable* newScope=new symbolTable();
        newScope->parent=currScope;
        currScope=newScope;
        cout<<"New Scope created"<<endl<<endl<<endl;
        if(context->paramList())
            node->param_list=visit(context->paramList());
        vector<ASTParamSingle*> params;
        if(node->param_list!=nullptr){
            params=node->param_list->params;
        }
        for(int i=0;i<params.size();i++){
            globalScope->func_declmap[node->id].push_back(params[i]->type);
        }
        if(context->block())
            node->block=visit(context->block());
        return node;
    }

    virtual antlrcpp::Any visitVarDeclSingle(MinicParser::VarDeclSingleContext* context){
        cout<<"In visitVarDeclSingle"<<endl;
        ASTVarDeclSingle* node = new ASTVarDeclSingle(context->ID()->getText());
        // cout<<context->ID()->getText()<<endl;
        if(context->op){
            cout<<context->op->getText()<<endl;
            ASTExpr* tempNode=visit(context->expr(0));
            // if(currScope->var_map.find(id) == currScope->var_map.end())
            node->val=tempNode;
        }
        else{
            for(auto curr:context->expr()){
                node->exprs.push_back(visit(curr));
            }
        }
        // cout<<node->exprs.size()<<endl;
        
        // cout<<"out of it";
        return node;
    }

    virtual antlrcpp::Any visitParamList(MinicParser::ParamListContext* context){
        cout<<"In visitParamList"<<endl;
        ASTParamList* node=new ASTParamList();
        if(context->paramSingle(0)!=nullptr){
            ASTParamSingle* single_param_node;
            for(auto curr:context->paramSingle()){
                single_param_node=visit(curr);
                if(single_param_node!=nullptr){
                    ASTVarDeclSingle* tempVar=single_param_node->var;
                    if (currScope->var_map.find(tempVar->id) == currScope->var_map.end()){
                        currScope->var_map[tempVar->id]={single_param_node->type,""};
                    }
                    else{
                        cout<<"Variable redeclared"<<endl;
                        return nullptr;
                    }
                    node->params.push_back(single_param_node);
                }
            }
        }
        return node;
    }

    virtual antlrcpp::Any visitParamSingle(MinicParser::ParamSingleContext* context){
        cout<<"In visitParamSingle"<<endl;
        ASTParamSingle* node=new ASTParamSingle();
        node->type=context->Type()->getText();
        if(context->varDeclSingle()){
            node->var=visit(context->varDeclSingle());
        }
        return node;
    }

    virtual antlrcpp::Any visitBlock(MinicParser::BlockContext* context){
        cout<<"In visitBlock"<<endl;
        ASTBlock* node=new ASTBlock();
        if(context->statement(0)!=nullptr){
            ASTStatement* stat_node=new ASTStatement();
            for(auto curr:context->statement()){
                stat_node=visit(curr);
                if(stat_node!=nullptr)
                    node->statements.push_back(stat_node);
            }
        }
        return node;
    }

    virtual antlrcpp::Any visitAssignstat(MinicParser::AssignstatContext* context){
        cout<<"In visitAssignstat"<<endl;
        ASTAssignstat* node=new ASTAssignstat();
        node->lhs=visit(context->location());
        node->rhs=visit(context->expr());
        symbolTable* temp=currScope;
        while(temp!=nullptr && temp->var_map.find(node->lhs->id) == temp->var_map.end()){
            if(temp!=nullptr){
                temp=temp->parent;
            }
            else{
                break;
            }
        }
        if(temp==nullptr){
            cout<<"Variable must be declared before usage"<<endl;
            return nullptr;
        }
        string ltype=temp->var_map[node->lhs->id].first;
        string rtype=node->rhs->type;
        if(ltype!=rtype){
            cout<<"Type mismatch-2"<<endl;
            return nullptr;
        }
        node->op=context->op->getText();
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitFuncstat(MinicParser::FuncstatContext* context){
        cout<<"In visitFuncstat"<<endl;
        ASTFuncstat* node=new ASTFuncstat();
        node->func_call=visit(context->functionCall());
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitControlstat(MinicParser::ControlstatContext* context){
        cout<<"In visitControlstat"<<endl;
        ASTControlstat* node=new ASTControlstat();
        node->if_else_block=visit(context->ifElseBlock());
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitForstat(MinicParser::ForstatContext* context){
        cout<<"In visitForstat"<<endl;
        ASTForstat* node=new ASTForstat();
        node->for_block=visit(context->forBlock());
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitWhilestat(MinicParser::WhilestatContext* context){
        cout<<"In visitForstat"<<endl;
        ASTWhilestat* node=new ASTWhilestat();
        node->while_block=visit(context->whileBlock());
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitReturnstat(MinicParser::ReturnstatContext* context){
        cout<<"In visitReturnstat"<<endl;
        ASTReturnstat* node=new ASTReturnstat();
        node->ret_stat=visit(context->returnStmt());
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitBreakstat(MinicParser::BreakstatContext* context){
        cout<<"In visitBreakstat"<<endl;
        ASTBreakstat* node=new ASTBreakstat();
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitDeclstat(MinicParser::DeclstatContext* context){
        cout<<"In visitDeclstat"<<endl;
        ASTDeclstat* node=new ASTDeclstat();
        node->var_decl=visit(context->variableDecl());
        return (ASTStatement*)node;
    }

    virtual antlrcpp::Any visitLocation(MinicParser::LocationContext* context){
        cout<<"In visitLocation"<<endl;
        string id=context->ID()->getText();
        // cout<<id<<endl<<endl<<endl;
        symbolTable* temp=currScope;
        while(temp!=nullptr && temp->var_map.find(id) == temp->var_map.end()){
            if(temp!=nullptr){
                temp=temp->parent;
            }
            else{
                break;
            }
        }
        // cout<<temp;
        if((temp==nullptr)){
            cout<<"Variable not declared"<<endl;
            return nullptr;
        }

        ASTLocation* node = new ASTLocation(id);
        // cout<<context->ID()->getText()<<endl;
        for(auto curr:context->expr()){
            ASTExpr* tempNode=visit(curr);
            if(tempNode->type!="int"){
                cout<<"Array indices must be integers";
                return nullptr;
            }
            node->expr.push_back(tempNode);
        }
        // cout<<node->expr.size()<<endl;
        // cout<<"out of it";
        return node;
    }

    virtual antlrcpp::Any visitFunctionCall(MinicParser::FunctionCallContext* context){
        cout<<"In visitFunctionCall"<<endl;
        ASTFunctionCall* node=new ASTFunctionCall();
        node->id=context->ID()->getText();
        if(globalScope->func_retmap.find(node->id)==globalScope->func_retmap.end()){
            cout<<"Function not declared"<<endl;
            return nullptr;
        }
        vector<string> paramTypes=globalScope->func_declmap[node->id];
        if(context->inputList())
            node->input_list=visit(context->inputList());
        vector<string> inputTypes;
        for(int i=0;i<node->input_list->expression_list.size();i++){
            inputTypes.push_back(node->input_list->expression_list[i]->type);
        }
        int paramSize=paramTypes.size();
        int inputSize=inputTypes.size();
        if(paramSize!=inputSize){
            cout<<"Number of parameters doesnt match"<<endl;
            return nullptr;
        }
        else{
            for(int i=0;i<inputSize;i++){
                if(inputTypes[i]!=paramTypes[i]){
                    cout<<"Parameter types in function doesnt match"<<endl;
                    return nullptr;
                }
            }
        }
        return node;
    }

    virtual antlrcpp::Any visitInputList(MinicParser::InputListContext* context){
        cout<<"In visitInputList"<<endl;
        ASTInputList* node=new ASTInputList();
        if(context->expr(0)!=nullptr){
            ASTExpr* expr_node=new ASTExpr();
            for(auto curr:context->expr()){
                expr_node=visit(curr);
                if(expr_node!=nullptr){
                    node->expression_list.push_back(expr_node);
                }
            }
        }
        return node;
    }

    virtual antlrcpp::Any visitIfElseBlock(MinicParser::IfElseBlockContext* context){
        cout<<"In VisitIfElseBlock"<<endl;
        ASTIfElseBlock* node=new ASTIfElseBlock();
        node->if_block=visit(context->ifBlock());
        if(context->elifBlock(0)!=nullptr){
            ASTElifBlock* elif_node;
            for(auto curr:context->elifBlock()){
                elif_node=visit(curr);
                if(elif_node!=nullptr){
                    node->elif_block.push_back(elif_node);
                }
            }
        }
        if(context->elseBlock()){
            node->else_block=visit(context->elseBlock());
        }
        return node;
    }

    virtual antlrcpp::Any visitIfBlock(MinicParser::IfBlockContext* context){
        cout<<"In visitIfBlock"<<endl;
        ASTIfBlock* node=new ASTIfBlock();
        symbolTable* newScope=new symbolTable();
        newScope->parent=currScope;
        currScope=newScope;
        node->expr=visit(context->expr());
        node->block=visit(context->block());
        return node;
    }

    virtual antlrcpp::Any visitElifBlock(MinicParser::ElifBlockContext* context){
        cout<<"In visitElifBlock"<<endl;
        ASTElifBlock* node=new ASTElifBlock();
        symbolTable* newScope=new symbolTable();
        newScope->parent=currScope;
        currScope=newScope;
        node->expr=visit(context->expr());
        node->block=visit(context->block());
        return node;
    }

    virtual antlrcpp::Any visitElseBlock(MinicParser::ElseBlockContext* context){
        cout<<"In visitElseBlock"<<endl;
        ASTElseBlock* node=new ASTElseBlock();
        symbolTable* newScope=new symbolTable();
        newScope->parent=currScope;
        currScope=newScope;
        node->block=visit(context->block());
        return node;
    }

    virtual antlrcpp::Any visitForBlock(MinicParser::ForBlockContext* context){
        cout<<"In visitForBlock"<<endl;
        ASTForBlock* node=new ASTForBlock();
        node->for_2=visit(context->expr());
        // cout<<"print-1";
        node->for_1_and_3.push_back(visit(context->statement(0)));
        node->for_1_and_3.push_back(visit(context->statement(1)));
        // cout<<"print-2";
        symbolTable* newScope=new symbolTable();
        newScope->parent=currScope;
        currScope=newScope;
        node->block=visit(context->block());
        return node;
    }

    virtual antlrcpp::Any visitWhileBlock(MinicParser::WhileBlockContext* context){
        cout<<"In visitWhileBlock"<<endl;
        ASTWhileBlock* node=new ASTWhileBlock();
        symbolTable* newScope=new symbolTable();
        newScope->parent=currScope;
        currScope=newScope;
        node->expr=visit(context->expr());
        node->block=visit(context->block());
        return node;
    }

    virtual antlrcpp::Any visitReturnStmt(MinicParser::ReturnStmtContext* context){
        cout<<"In visitReturnStmt"<<endl;
        ASTReturnStmt* node=new ASTReturnStmt();
        if(context->expr())
            node->expr=visit(context->expr());
        return node;
    }

    virtual antlrcpp::Any visitExprLocation(MinicParser::ExprLocationContext* context){
        cout<<"In visitExprLocation"<<endl;
        ASTExprLocation* node=new ASTExprLocation();
        node->loc=visit(context->location());
        string id=node->loc->id;
        symbolTable* temp=currScope;
        while(temp!=nullptr && temp->var_map.find(id) == temp->var_map.end()){
            if(temp!=nullptr){
                temp=temp->parent;
            }
            else{
                break;
            }
        }
        node->type=temp->var_map[node->loc->id].first;
        return (ASTExpr*)node;
    }

    virtual antlrcpp::Any visitExprFunc(MinicParser::ExprFuncContext* context){
        cout<<"In visitExprFunc"<<endl;
        ASTExprFunc* node=new ASTExprFunc();
        node->func_call=visit(context->functionCall());
        node->type=globalScope->func_retmap[node->func_call->id];
        return (ASTExpr*)node;
    }

    virtual antlrcpp::Any visitExprUnary(MinicParser::ExprUnaryContext* context){
        cout<<"In visitExprUnary"<<endl;
        ASTExpr* exprNode=visit(context->expr());
        ASTExprUnary* node=new ASTExprUnary(context->UnaryOp()->getText(),exprNode);
        node->type=exprNode->type;
        return (ASTExpr*)node;
    }

    virtual antlrcpp::Any visitExprTernary(MinicParser::ExprTernaryContext* context){
        cout<<"In visitExprTernary"<<endl;
        ASTExpr* first=visit(context->expr(0));
        ASTExpr* second=visit(context->expr(1));
        ASTExpr* third=visit(context->expr(2));
        ASTExprTernary* node=new ASTExprTernary(first,second,third);
        node->type=first->type;
        return (ASTExpr*)node;
    }

    virtual antlrcpp::Any visitExprId(MinicParser::ExprIdContext* context){
        cout<<"In visitExprId"<<endl;
        string id=context->ID()->getText();
        symbolTable* temp=currScope;
        while(temp!=nullptr && temp->var_map.find(id) == currScope->var_map.end()){
            if(temp!=nullptr){
                temp=temp->parent;
            }
            else{
                break;
            }
        }
        if(temp==nullptr){
            cout<<"Variable not declared"<<endl;
            return nullptr;
        }
        string type=currScope->var_map[id].first;
        ASTExprId* node=new ASTExprId(id);
        node->type=type;
        return (ASTExpr*)node;
    }

    virtual antlrcpp::Any visitExprLiteral(MinicParser::ExprLiteralContext* context){
        cout<<"In visitExprLiteral"<<endl;
        ASTExprLiteral* node=new ASTExprLiteral();
        if(context->INTLITERAL()){
            node->type="int";
            node->int_val=stoi(context->INTLITERAL()->getText());
            cout<<node->int_val<<endl;
        }
        else if(context->FLOATLITERAL()){
            node->type="float";
            node->float_val=stof(context->FLOATLITERAL()->getText());
            cout<<node->float_val<<endl;
        }
        else if(context->BOOLLITERAL()){
            node->type="bool";
            if(context->BOOLLITERAL()->getText()!="false")
                node->bool_val=true;
            else
                node->bool_val=false;
            cout<<node->bool_val<<endl;
        }
        else if(context->CHARLITERAL()){
            node->type="char";
            string temp=context->CHARLITERAL()->getText();
            node->char_val=temp[1];
            cout<<node->char_val<<endl;
        }
        else if(context->STRINGLITERAL()){
            node->type="string";
            node->string_val=context->STRINGLITERAL()->getText();
            cout<<node->string_val<<endl;
        }
        cout<<node->type<<endl;
        return (ASTExpr*)node;
    }

    virtual antlrcpp::Any visitExprParenthesis(MinicParser::ExprParenthesisContext *context){
        cout << "In visitExprParenthesis" << endl;
        return visit(context->expr());
    }

    virtual antlrcpp::Any visitExprArthimetic(MinicParser::ExprArthimeticContext *context){
        cout << "In visitExprArthimetic" << endl;
        ASTExpr *left;
        ASTExpr *right;
       
        ASTExprBinary *node;

        left = visit(context->expr(0));
        right = visit(context->expr(1));

        string op = context->ArthimeticOp()->getText();

        node = new ASTExprBinary(op, left, right);
        node->type=left->type;
        return (ASTExpr *) node;
    }

    virtual antlrcpp::Any visitExprRelational(MinicParser::ExprRelationalContext *context){
        cout << "In visitExprRelational" << endl;
        ASTExpr *left;
        ASTExpr *right;
       
        ASTExprBinary *node;

        left = visit(context->expr(0));
        right = visit(context->expr(1));

        string op = context->RelationalOp()->getText();

        node = new ASTExprBinary(op, left, right);
        node->type="bool";
        return (ASTExpr *) node;
    }

    virtual antlrcpp::Any visitExprBoolean(MinicParser::ExprBooleanContext *context){
        cout << "In visitExprBoolean" << endl;
        ASTExpr *left;
        ASTExpr *right;
       
        ASTExprBinary *node;

        left = visit(context->expr(0));
        right = visit(context->expr(1));

        string op = context->BoolOp()->getText();

        node = new ASTExprBinary(op, left, right);
        node->type="bool";
        return (ASTExpr *) node;
    }
};