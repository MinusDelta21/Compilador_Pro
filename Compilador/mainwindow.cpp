#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "sintactico.h"
Sintactico ASintactico;
enum
{
    _OperadorArit = 0,
    _OperadorLog,
    _Asig,
    _OperadorRel,
    _ConstantesLog,
    _Delim,
    _Agrup,
    _Bucle,
    _EstructurasCtrl,
    _ProcFunc,
    _Var,
    _VarType,
    _Main,
    _Extra

};
bool isInteger(const std::string & s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

bool isFloat(std::string myString)
{
    std::istringstream iss(myString);
    float f;
    // noskipws considers leading whitespace invalid
    iss >> std::noskipws >> f;
    // Check the entire strin-g was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::on_New_triggered()
{
  file_path_ = "";
  ui->CodeBox->setText("");
}
void MainWindow::on_Save_As_triggered()
{
  QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
  QFile file(file_name);
  file_path_ = file_name;
  if(!file.open(QFile::WriteOnly | QFile::Text)) {
      QMessageBox::warning(this,"..","file not open");
      return;
    }
  QTextStream out(&file);
  QString text = ui->CodeBox->toPlainText();
  out << text;
  file.flush();
  file.close();
}
void MainWindow::on_Save_triggered()
{
    QFile file(file_path_);
      if(!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","file not open");
          return;
        }
      QTextStream out(&file);
      QString text = ui->CodeBox->toPlainText();
      out << text;
      file.flush();
      file.close();
}
void MainWindow::on_Open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
      QFile file(file_name);
      file_path_ = file_name;
      if(!file.open(QFile::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","file not open");
          return;
        }
      QTextStream in(&file);
      QString text = in.readAll();
      ui->CodeBox->setText(text);
      file.close();
}

void MainWindow::on_actionCompilar_triggered()
{
    std::string SourceCode;
        QString Err;

        SourceCode = ui->CodeBox->toPlainText().toStdString();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::ofstream lexfile;
            std::ofstream errfile;

            std::vector<std::string> Token;
            std::vector<std::string> Lexem;

            std::vector<std::vector<std::string>*> Contenedor;

            std::vector<std::string> OperadorArit = { "+", "-", "*", "/" , "%", "^" };
            std::vector<std::string> OperadorLog = { "&&", "||" , "!" };
            std::vector<std::string> Asig = { "=" };
            std::vector<std::string> OperadorRel = { "<", ">", "<=" , ">=" , "==" , "!=" };
            std::vector<std::string> ConstantesLog = { "true","false" };
            std::vector<std::string> Delim = { "." ,",", ";" , ":"};
            std::vector<std::string> Agrup = { "(",")","{" , "}","[","]" };
            std::vector<std::string> Bucle = { "for", "while" };
            std::vector<std::string> EstructurasCtrl = { "if", "else","switch","case","default" };
            std::vector<std::string> ProcFunc = { "procedure", "function" };
            std::vector<std::string> Var = { "var" };
            std::vector<std::string> VarType = { "int","float","string","bool" };
            std::vector<std::string> Main = { "main" };
            std::vector<std::string> Extra = { "print","read","return" };

            Contenedor.push_back(&OperadorArit);
            Contenedor.push_back(&OperadorLog);
            Contenedor.push_back(&Asig);
            Contenedor.push_back(&OperadorRel);
            Contenedor.push_back(&ConstantesLog);
            Contenedor.push_back(&Delim);
            Contenedor.push_back(&Agrup);
            Contenedor.push_back(&Bucle);
            Contenedor.push_back(&EstructurasCtrl);
            Contenedor.push_back(&ProcFunc);
            Contenedor.push_back(&Var);
            Contenedor.push_back(&VarType);
            Contenedor.push_back(&Main);
            Contenedor.push_back(&Extra);

            char SouceCodeChar[65536];
            char * pch;
            char* context = NULL;



            for(int i=0; i< SourceCode.size();i++){
                char temp = SourceCode[i];
                if((temp == '+') ||(temp == '-')||(temp == '*')||(temp == '/')||(temp == '%')||(temp == '^')||(temp == '=')||(temp == '<')||(temp == '>')||(temp == '!')||
                        (temp == ',')||(temp == ';')||(temp == ':')||(temp == '(')||(temp == ')')||(temp == '{')||(temp == '}')||(temp == '[')||(temp == ']')||(temp =='!'))
                {
                    SourceCode.insert(i+1," ");
                    SourceCode.insert(i," ");
                    i++;
                }

            }
            memset(SouceCodeChar, 0, 65536);
            memcpy(SouceCodeChar, SourceCode.c_str(), SourceCode.size());
            pch = strtok_s(SouceCodeChar, " \n", &context);
            while (pch != NULL)
            {

                Token.push_back(pch);
                pch = strtok_s(NULL, " \n", &context);
            }
            bool wordFound = false;
            int TokenSize = Token.size();
            int ContenedorActual = 0;
            for (int i = 0;i < TokenSize;i++)
            {
                ContenedorActual = 0;
                wordFound = false;
                for (auto itContenedor : Contenedor)
                {
                    for (auto itK : *itContenedor)
                    {
                        if (Token[i] == itK)
                        {
                            wordFound = true;
                            switch (ContenedorActual)
                            {

                            case _OperadorArit:
                                Lexem.push_back("OpArit");
                                break;
                            case _OperadorLog:
                                Lexem.push_back("OpLog");
                                break;
                            case _Asig:
                                Lexem.push_back("Asig");
                                break;
                            case _OperadorRel:
                                Lexem.push_back("OpRel");
                                break;
                            case _ConstantesLog:
                                Lexem.push_back("ConstLog");
                                break;
                            case _Delim:
                                Lexem.push_back("Delim");
                                break;
                            case _Agrup:
                                Lexem.push_back("Agrup");
                                break;
                            case _Bucle:
                                Lexem.push_back("Bucle");
                                break;
                            case _EstructurasCtrl:
                                Lexem.push_back("EstrCtrl");
                                break;
                            case _ProcFunc:
                                Lexem.push_back("ProcFunc");
                                break;
                            case _Var:
                                Lexem.push_back("VarDef");
                                break;
                            case _VarType:
                                Lexem.push_back("VarType");
                                break;
                            case _Main:
                                Lexem.push_back("MainDef");
                                break;
                            case _Extra:
                                Lexem.push_back("ExtraDef");
                                break;

                            default:
                                break;
                            }
                            break;
                        }
                    }
                    ContenedorActual++;
                    if (wordFound)
                        break;
                }
                if (!wordFound)
                    Lexem.push_back("Undefined");
            }

            for (int i = 0;i < TokenSize;i++)
            {
                if (Lexem[i] == "Undefined")
                {
                    if (isInteger(Token[i]))
                        Lexem[i] = "ConstInt";
                    else if (isFloat(Token[i]))
                        Lexem[i] = "ConstFloat";
                    else
                        Lexem[i] = "ERROR";
                }
            }
            for(int i =1; i< TokenSize-1;i++){

                if(Lexem[i] =="ERROR"){
                    if(isalpha(Token[i][0])) Lexem[i] = "ID";
                    if((Lexem[i-1] =="VarType" && Lexem[i+1] =="Asig")||(Lexem[i-1] =="VarDef" && Lexem[i+1] =="Asig")||(Lexem[i-1] =="VarDef" && Lexem[i+1] =="Delim")||(Lexem[i-1] =="Delim" && Lexem[i+1] =="Asig")) Lexem[i] = "ID";
                    if((Lexem[i-1] == "Delim") ||(Lexem[i+1] == "Delim")) Lexem[i] = "ID";
                }
                if(Lexem[i-1] =="ERROR"){
                    if((Lexem[i] == "Agrup" &&Token[i] == "[") &&(Lexem[i+2] == "Agrup" &&Token[i+2] == "]")) Lexem[i-1]="ID";
                    if((Lexem[i] == "Agrup" && Token[i] == "(")) Lexem[i-1] = "ID";
                }

            }
            for(int i=0;i<TokenSize;i++){
                if(Token[i] == "inc" || Token[i] =="dec") Lexem[i] = "Inc_Dec";
                if(Lexem[i] == "ERROR" && Token[i+1]=="=") Lexem[i] ="ID";
                if(Lexem[i] == "ID" && Token[i][1]== '"') Lexem[i] = "VarType";
            }


            lexfile.open("Lexemas.lex");
            errfile.open("Errores.err");

            int counter = 0;
            Err.push_back("Error list:");
            for (int i = 0;i < TokenSize; i++)
            {

                if (Lexem[i] != "ERROR"){
                    lexfile << counter << " " << Token[i] << "\t" << Lexem[i] << std::endl;
                }

                else{
                    errfile << counter << " " << Token[i] << "\t" << Lexem[i] << std::endl;
                    Err.push_back(QString::fromStdString("\n"+Lexem[i]+"\t"+Token[i]));
                }
                counter++;
            }

            lexfile.close();
            errfile.close();


            ui->CajaErrores->setText(Err);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        ASintactico.getTokens(Token,Lexem);
        ASintactico.checkSyntax();
        for(int i=0;i<ASintactico.Error.size();++i){
            Err.push_back(QString::fromStdString("\n"+ASintactico.Error[i]));
        }
        ui->CajaErrores->setText(Err);


}
