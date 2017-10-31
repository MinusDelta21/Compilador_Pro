#include "sintactico.h"

Sintactico::Sintactico()
{
    cont =0;
}
void Sintactico::getTokens(vector<string>theToken, vector<string>theLexem){//Obtiene Tokens
    this->Token = theToken;
    this->Lexem = theLexem;
}
//Variables
void Sintactico::getVar(){//Lee variables
    if(Lexem[cont] =="ID"){
        cont++;
        if(Lexem[cont] == "Agrup" && Token[cont] == "["){
            cont++;
            if(Lexem[cont] == "ConstInt"){
                cont++;
                if(Lexem[cont] == "Agrup" && Token[cont] == "]"){
                    cont++;
                }else{ Error.push_back("Expected  a ]"); cont++;}
            }
            else{
                Error.push_back("Expected int");
                cont++;
                if(Lexem[cont] == "Agrup" && Token[cont] == "]"){
                    cont++;
                }else {Error.push_back("Expected  a ]");cont++;}
            }
        }
    }
    else {Error.push_back("Expected an ID");cont++;}
}
void Sintactico::VarDeclare(){//Declaracion de variables
    getVar();
    while(Token[cont] !=";"){
        if(Token[cont] ==","){
            cont++;
            getVar();
        }
        if(Token[cont] == ":"){
            cont++;
            if(Lexem[cont] == "VarType"){
                cont++;
                if(Token[cont] ==";"){
                    cont++;
                    return;
                }else{
                    Error.push_back("Expected a ;");
                    cont++;
                    return;
                }
            }else{ Error.push_back("Expected a VarType");cont++;}
        }
    }
}
void Sintactico::VarAssign(){//Asignacion de variables
    while(Token[cont] !=";"){
        getVar();
        if(Lexem[cont] == "Asig"){
            cont++;
            if(Lexem[cont] == "ConstLog" ||Lexem[cont] == "ConstInt" ||Lexem[cont] == "ConstFloat" || Lexem[cont] == "ID"){
                cont++;
                if(Token[cont] ==";"){
                    return;
                }else{
                    Error.push_back("Expected a ;");
                    cont++;
                    return;
                }
            }else {Error.push_back("Expected a value");cont++;}

        }else {Error.push_back("Expected a =");cont++;}
    }


}
//Expresiones
void Sintactico::getExpr(){ //Obtener expresiones
    if(Token[cont] =="!") cont++;
    checkTerm();
    if(Lexem[cont] == "OpRel") cont++;
    else {Error.push_back("Expected operator");cont++;}
    checkTerm();
    return;
}
void Sintactico::checkTerm(){//Diferentes tipos de terminos posibles
    if(Lexem[cont] == "Agrup"){
        if(Token[cont] == "("){
            cont++;
            getExpr();
            cont++;
            if(Lexem[cont] == "Agrup" && Token[cont] == ")"){
                cont++;
                return;
            }else {Error.push_back("Expected  a )");cont++;}
        }else {Error.push_back("Expected  a (");cont++;}
    }
    else if(Lexem[cont] == "ID"){
        if(Token[cont+1] == "("){
            proc_Call();
            return;
        }
        else {
            getVar();
            return;
        }
        }
    else {Error.push_back("Term must start with ( or an ID");cont++;}
}
//Funciones y procedimientos
void Sintactico::decl_Fn(){//Declaracion de procedimiento o funcion
    if(Lexem[cont]=="ID"){
        cont++;
        if(Token[cont] == "("){
            cont++;
            if(Token[cont]!= ")"){
                getVar();
                while(Token[cont] !=":"){

                    if(Token[cont] ==","){
                        cont++;
                        getVar();
                    }
                }
                if(Token[cont] == ":"){
                    cont++;
                    if(Lexem[cont] == "VarType"){
                        cont++;
                        if(Token[cont] == ")"){
                            cont++;
                            if(Token[cont] == "{"){
                                cont++;
                                checkSyntax();
                            }else{
                                cont++;
                                Error.push_back("Expected {");
                                checkSyntax();
                            }
                        }else{
                            cont++;
                            Error.push_back("Expected )");
                        }
                    }else {
                        cont++;
                        Error.push_back("Expected VarType");
                    }
                }else{
                    cont++;
                    Error.push_back("Expected :");
                }
            }else{
                cont++;
                if(Token[cont] == "{"){
                    cont++;
                    checkSyntax();
                }else{
                    cont++;
                    Error.push_back("Expected {");
                    checkSyntax();
                }
            }
        }else{
            cont++;
            Error.push_back("Expected (");
        }
    }else{
        cont++;
        Error.push_back("Expected ID");
    }
}
void Sintactico::proc_Call(){//Llamada a funcion o procedimiento
    while(Token[cont] !=";"){
        if(Lexem[cont] == "ID"){
            cont++;
            if(Token[cont] !="("){Error.push_back("Expected )");cont++;}
        }
        if(Token[cont] =="("){
            cont++;
            getVar();
        }
        if(Token[cont] == ","){
            cont++;
            getVar();
        }
        if(Token[cont]==")"){
            cont++;
            if(Token[cont] == ";"){
                cont++;
                return;
            }else{
                Error.push_back("Expected ;");
                cont++;
                return;
            }
        }


    }
}
void Sintactico::fn_print(){
    while(Token[cont] !=";"){
        if(Token[cont] == "("){
            cont++;
            expr_List();
            cont++;
            if(Token[cont] == ")"){
                cont++;
                if(Token[cont] ==";"){
                    cont++;
                    return;
                }else{
                    Error.push_back("Expected a ;");
                    cont++;
                    return;
                }
            }else {Error.push_back("Expected a )");cont++;}
        }else {Error.push_back("Expected a (");cont++;}
    }
}
void Sintactico::fn_read(){
    while(Token[cont] !=";"){
        if(Token[cont] == "("){
            cont++;
            getVar();
            if(Token[cont] == ")"){
                cont++;
                if(Token[cont] ==";"){
                    cont++;
                    return;
                }else{
                    Error.push_back("Expected a ;");
                    cont++;
                    return;
                }
            }else{ Error.push_back("Expected a )");cont++;}
        }else {Error.push_back("Expected a (");cont++;}
    }
}
void Sintactico::fn_return(){
    getExpr();
}
void Sintactico::main(){
    if(Token[cont] == "("){
        cont++;
        if(Token[cont]!= ")"){
            getVar();
            while(Token[cont] !=":"){

                if(Token[cont] ==","){
                    cont++;
                    getVar();
                }
            }
            if(Token[cont] == ":"){
                cont++;
                if(Lexem[cont] == "VarType"){
                    cont++;
                    if(Token[cont] == ")"){
                        cont++;
                        if(Token[cont] == "{"){
                            cont++;
                            checkSyntax();
                        }else{
                            cont++;
                            Error.push_back("Expected {");
                            checkSyntax();
                        }
                    }else{
                        cont++;
                        Error.push_back("Expected )");
                    }
                }else {
                    cont++;
                    Error.push_back("Expected VarType");
                }
            }else{
                cont++;
                Error.push_back("Expected :");
            }
        }else{
            cont++;
            if(Token[cont] == "{"){
                cont++;
                checkSyntax();
            }else{
                cont++;
                Error.push_back("Expected {");
                checkSyntax();
            }
        }
    }else{
        cont++;
        Error.push_back("Expected (");
    }
}
//BLock
void Sintactico::block(){ //Bloque utilizado para if, for, while
    while(Token[cont] != "}"){
        if(Token[cont] == "{"){
            cont++;
            block_checkSyn();
        }
        else{
            Error.push_back("Expected {");
            cont++;
            block_checkSyn();
        }
    }
}
void Sintactico::block_checkSyn(){
    while(cont < Lexem.size()-1){
        if(Lexem[cont] =="ExtraDef"){
            if(Token[cont] == "print"){
                cont++;
                this->fn_print();
            }
            else if(Token[cont] == "read"){
                cont++;
                this->fn_read();
            }
            else if(Token[cont] == "return"){
                cont++;
                this->fn_return();
            }
        }
        else if(Lexem[cont] == "Bucle"){
            if(Token[cont] == "for"){
                cont++;
                for_statement();
            }
            else if(Token[cont] == "while"){
                cont++;
                while_statement();
            }
        }
        else if(Token[cont] == "if"){
            cont++;
            if_statement();
        }
        else if(Token[cont] == "}")return;
        else cont++;
    }
}
//Statements
void Sintactico::if_statement(){
    if(Token[cont] =="("){
        cont++;
        getExpr();
        if(Token[cont] == ")"){
            cont++;
            if(Token[cont] == "{"){
                block();
                cont++;
            }else{ Error.push_back("Expected {");}
        }
    } else {Error.push_back("Expected (");}
    if(Token[cont] == "else"){
        cont++;
        if(Token[cont] == "{"){
            block();
        }
    }
}
void Sintactico::while_statement(){
    if(Token[cont] =="("){
        cont++;
        getExpr();
        if(Token[cont] == ")"){
            cont++;
            if(Token[cont] == "{"){
                block();
            }else Error.push_back("Expected {");
        }
    } else Error.push_back("Expected (");
}
void Sintactico::for_statement(){
    if(Token[cont] =="("){
        cont++;
        VarAssign();
        cont = cont-1;
        if(Token[cont] == ";"){
            cont++;
            getExpr();
            if(Token[cont] == ";"){
                cont++;
                if(Token[cont] == "inc" || Token[cont]=="dec"){
                    cont++;
                    if(Token[cont] == ")"){
                        cont++;
                        if(Token[cont] == "{"){
                            block();
                        }
                    }
                }
            }else{ Error.push_back("Expected {");}
        }
    } else Error.push_back("Expected (");
}
void Sintactico::expr_List(){

}
//Check syntax
void Sintactico::checkSyntax(){
    while(cont < Lexem.size()-1){
        if(Lexem[cont] == "VarDef"){
            cont++;
            this->VarDeclare();
        }
        else if(Lexem[cont] == "ID"){
            if(Token[cont+1]=="("){
                this->proc_Call();
            }
            else{
                this->VarAssign();
            }
        }
        else if(Lexem[cont] =="ExtraDef"){
            if(Token[cont] == "print"){
                cont++;
                this->fn_print();
            }
            else if(Token[cont] == "read"){
                cont++;
                this->fn_read();
            }
            else if(Token[cont] == "return"){
                cont++;
                this->fn_return();
            }
        }
        else if(Lexem[cont] == "Bucle"){
            if(Token[cont] == "for"){
                cont++;
                for_statement();
            }
            else if(Token[cont] == "while"){
                cont++;
                while_statement();
            }
        }
        else if(Token[cont] == "if"){
            cont++;
            if_statement();
        }
        else if(Token[cont] == "}")return;
        else if(Token[cont] == "main"){
            cont++;
            main();
        }
        else if(Lexem[cont] == "ProcFunc"){
            cont++;
            decl_Fn();
        }
        else cont++;
    }
}
