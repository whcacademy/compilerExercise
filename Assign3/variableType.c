// this is code collection for varible table and type checking

int getTypeFromTable(int offset, tableNode* root){
    if (root==NULL){
        return -1;
    }else{
        if (root->offset == offset){
            return root->varType;
        }else{
            return getTypeFromTable(offset, root->leftNode)!=-1?
                    getTypeFromTable(offset, root->leftNode):
                    getTypeFromTable(offset, root->rightNode);
        }
    }
}

void createTypeNode(tableNode* src, tableNode** root){
    if (*root==NULL){
        tableNode* newOne = (tableNode*)malloc(sizeof(tableNode));
        strcpy(newOne->varName, src->varName);
        newOne->varType = typeVar;
        newOne->offset = src->offset;
        newOne->lineNo = src->lineNo;
        newOne->leftNode = NULL;
        newOne->rightNode = NULL;
        *root = newOne;
    }else{
        int flag = strcmp((*root)->varName, src->varName);
        if(flag < 0){
            createTypeNode(src, &((*root)->leftNode));
        }else{
            createTypeNode(src, &((*root)->rightNode));
        }
    }
}

void updateNodeType(int offset, int type, tableNode* root){
    #ifdef DEBUG
    printf("starting update inside fucntion updateNodeType\n");
    #endif
    if (root==NULL){
        return;
    }else{
        if(root->offset == offset){
            root->varType = type;
            #ifdef DEBUG
            printf("update the varType in some node\n");
            #endif
        }else{
            #ifdef DEBUG
            printf("update the varType in subnode\n");
            #endif
            updateNodeType(offset, type, root->leftNode);
            updateNodeType(offset, type, root->rightNode);
        }
    }
}
void updateCurrentVarCountAndTypeTable(int offset){
    currenVarCount++;
    // create a node and add in typetable
    
    tableNode* node = getNodeFromTable(offset, Table);
    #ifdef DEBUG
    printf("starting creating node for the varible: %s\n", node->varName);
    #endif
    createTypeNode(node, &typeTable);
    #ifdef DEBUG
    printf("finish creating node for the varible: %s\n", node->varName);
    #endif


}


int checkDefined(nodeType *p){
    #ifdef DEBUG
    printf("check varible definition\n");
    #endif
    if (p->var.offset >= currenVarCount){
        #ifdef DEBUG
        printf("offset:%d > currenVarCount:%d\n", p->var.offset,currenVarCount);
        #endif
        reportUndefined(p->var.offset);
        return -1;
    }
    return getTypeFromTable(p->var.offset, typeTable);
}


void checkUndefiedAndMatching(nodeType *p, int typeCon){
    if (p->type == typeVar){
        #ifdef DEBUG
        printf("find the type of varible\n");
        #endif
        int typeVar = checkDefined(p);
        if (typeVar - typeCon !=4){
            #ifdef CHECK
            printf("typeVar: %d, typeCon: %d\n", typeVar, typeCon);
            #endif
            reportMisMatched();
        }
        #ifdef DEBUG
        printf("check the variable finish\n");
        #endif
    }else if (p->type == typeOpr){
        int i;
        for (i = 0; i < p->opr.nops; i++){
            checkUndefiedAndMatching(p->opr.op[i], typeCon);
        }
    }else{
        #ifdef DEBUG
        printf("find the type of constant\n");
        #endif
        if (p->type != typeCon){
            reportMisMatched();
        }
    }
}


// this function have two responsibilties:
// 1. check if the expression is consistent in terms of type
// 2. if consistent, return the consistent type.
// Note that the type are all casted to constant type
int getRValueType(nodeType* p){
    if (p->type == typeVar) {
        return checkDefined(p) - 4;
    }
    if (p->type == typeConInt) return typeConInt;
    if (p->type == typeConChar) return typeConChar;
    if (p->type == typeConStr) return typeConStr;
    if (p->type == typeOpr){
        if (p->opr.nops == 1){
            return getRValueType(p->opr.op[0]); // deal with UMINUS
        }else{
            // deal with double operands
            int * typeList = (int*)malloc(p->opr.nops * sizeof(int));
            int i;        
            for (i = 0; i < p->opr.nops; ++i){
                typeList[i] = getRValueType(p->opr.op[i]);
                // if there is one variable undefined
                if (typeList[i] == -1){
                    return -1;
                }
            }
            int accType = -1;
            // currently not allow string or char as valid argument for AND OR
            for (i = 0; i < p->opr.nops; ++i){
                if (accType==-1){
                    accType = typeList[i];
                }else{
                    if (accType != typeList[i]){
                        reportMisMatched();
                        return -1;
                    }
                }
            }
            return accType;
        }
    }
}