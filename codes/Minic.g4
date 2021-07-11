grammar Minic;
prog: (declaration)+ EOF;
declaration : variableDecl #varDecl
            | functionDecl #funcDecl ;
variableDecl : Type (varDeclSingle',')*(varDeclSingle) ( ';'| ) ;
varDeclSingle : ID | ID op='=' expr | ID'['expr']' | ID '['expr']' '['expr']';
functionDecl : (Type | 'void')ID'('(paramList | /* epsilon*/ )')'(block|( ';'| ));
paramList : (paramSingle',')*(paramSingle);
// paramSingle : Type (ID |  (ID'['']') | (ID '['']' '['']'));
paramSingle : Type varDeclSingle;
block :'{'(statement)*'}';
statement : (location op=('='|'+='|'-='|'*=')expr ( ';'| ) ) #assignstat
            | (functionCall ( ';'| ) ) #funcstat
            | ifElseBlock #controlstat
            | forBlock #forstat
            | whileBlock #whilestat
            | returnStmt #returnstat
            | ('break' ( ';'| )) #breakstat
            | variableDecl #declstat;
location : (ID | (ID'['expr']') | (ID '['expr']' '['expr']'));
functionCall : ID '(' (inputList | /*epsilon */) ')';
inputList : (expr',')*(expr);
ifElseBlock : ifBlock (elifBlock)* (elseBlock)?;
ifBlock:'if' '('expr')' block;
elifBlock:  'elif' '('expr')' block;
elseBlock: 'else' block;
forBlock : 'for' '(' statement  expr ';' statement ')' block;
whileBlock : 'while' '(' expr ')' block;
returnStmt : 'return' ( expr | /*epsilon */) ( ';'| ) ;
expr:
    '(' expr ')' #exprParenthesis
    |location #exprLocation
    | functionCall #exprFunc
    | expr ArthimeticOp expr #exprArthimetic
    | expr RelationalOp expr #exprRelational
    | expr BoolOp expr #exprBoolean
    | UnaryOp expr #exprUnary
    | expr '?' expr ':' expr #exprTernary
    | ID #exprId
    | (INTLITERAL | FLOATLITERAL | CHARLITERAL | BOOLLITERAL | STRINGLITERAL) #exprLiteral;
BOOLLITERAL : 'true' | 'false';
ArthimeticOp:
             '/'
             | '*'
             | '+'
             | '-'
             | '%';
RelationalOp:
             '=='
             | '!='
             | '>'
             | '<'
             | '>='
             | '<=';
UnaryOp: '-' | '!';
BoolOp: '&&' | '||' ;
Type : 'int' | 'float' | 'char' | 'bool' | 'unsignedint' | 'string';
/*Tokens*/
INTLITERAL : [0-9][0-9]*;
FLOATLITERAL : [0-9][0-9]*[.][0-9][0-9]*;
CHARLITERAL : ['][a-zA-Z0-9_]['];
STRINGLITERAL : ["][a-zA-Z0-9_ \n\t'.:!$#*&^%][a-zA-Z0-9_ \n\t'.:!$#*&^%]*["];
ID  : [a-zA-Z][a-zA-Z0-9_]*;
COMMENT : '//' ~[\r\n]*->skip; 
NS : [ \r\t\n]+ -> skip; 