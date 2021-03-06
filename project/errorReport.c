// this is code collection for reporting error

void reportOutOfLoop(){
    yyerror("break or continue statement not within loop\n");
    exit(breakContinueError);
}

void reportInvalidBrkCon(){
    fprintf(stderr, "invalid break or continue statement\n");
    exit(breakContinueError);
}

void reportUndefined(char* varName){
    tableNode* var;
    var = getNodeFromTable(varName, Table);
    fprintf(stderr, "line %d: undefined varible: '%s'\n", var->lineNo, var->varName);
    exit(variableUseBeforeDefined);
}

void reportMisMatched(){
    fprintf(stderr, "the type of argument does not match the function used\n" );
    exit(typeMisMatched);
}

void reportFuncUnused(char* funcName){
    fprintf(stderr, "Warning: function %s has been defined but not used\n", funcName);
}

void reportFuncRedefined(char* funcName, int paraCnt){
    fprintf(stderr, "function: %s() with %d parameter(s) has been redefined\n", funcName, paraCnt);
    exit(functionRedefined);
}

void reportInvalidReturn(){
    fprintf(stderr, "invalid return statement in main\n");
    exit(invalidReturn);
}

void reportFuncVarClash(char* funcName){
    fprintf(stderr, "function %s has been conflicted with variable\n", funcName);
    exit(funcVarClash);
}

void reportInvalidIndex(){
    fprintf(stderr, "invalid array index of declaration\n" );
    exit(invalidIndex);
}

void reportArrayUndeclared(char* varName){
    fprintf(stderr, "array: %s is undeclared\n" , varName);
    exit(arrayUndeclared);
}

void reportArrayDuplicatedDeclaration(char* varName){
    fprintf(stderr, "array: %s duplicated declaration\n" , varName);
    exit(arrayDuplicatedDeclared);
}

void reportInvalidArrayUsage(char* varName){
    fprintf(stderr, "array: %s invalid useage\n" , varName);
    exit(arrayInvalidUsage);
}

void reportInvalidArrayPara(){
    fprintf(stderr, "array: invalid passing, maybe passing two or more same arrays, or passing \
        global arrays which can be directly used in the function, or some array argumets are not used int the function\n"  );
    exit(arrayInvalidUsage);
}