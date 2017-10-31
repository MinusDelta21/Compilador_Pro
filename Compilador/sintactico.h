#ifndef SINTACTICO_H
#define SINTACTICO_H
#include <vector>
#include <string>
using std::vector;
using std::string;

class Sintactico
{
public:
    vector<string> Token;
    vector<string> Lexem;
    vector<string> Error;
    int cont;
    Sintactico();
    void getTokens(vector<string>A, vector<string>B);
    void checkSyntax();
    void VarDeclare();
    void VarAssign();
    void getVar();
    void checkTerm();
    void getExpr();
    void proc_Call();
    void fn_read();
    void fn_print();
    void fn_return();
    void if_statement();
    void while_statement();
    void for_statement();
    void block();
    void expr_List();
    void block_checkSyn();
    void decl_Fn();
    void main();
};

#endif // SINTACTICO_H
