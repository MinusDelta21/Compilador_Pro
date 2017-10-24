/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *New;
    QAction *Open;
    QAction *actionCompilar;
    QAction *Save;
    QAction *Save_As;
    QWidget *centralWidget;
    QTextEdit *CodeBox;
    QTextEdit *CajaErrores;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuBuild;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(956, 591);
        New = new QAction(MainWindow);
        New->setObjectName(QStringLiteral("New"));
        Open = new QAction(MainWindow);
        Open->setObjectName(QStringLiteral("Open"));
        Open->setEnabled(true);
        actionCompilar = new QAction(MainWindow);
        actionCompilar->setObjectName(QStringLiteral("actionCompilar"));
        Save = new QAction(MainWindow);
        Save->setObjectName(QStringLiteral("Save"));
        Save->setEnabled(true);
        Save_As = new QAction(MainWindow);
        Save_As->setObjectName(QStringLiteral("Save_As"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CodeBox = new QTextEdit(centralWidget);
        CodeBox->setObjectName(QStringLiteral("CodeBox"));
        CodeBox->setGeometry(QRect(10, 10, 931, 341));
        CajaErrores = new QTextEdit(centralWidget);
        CajaErrores->setObjectName(QStringLiteral("CajaErrores"));
        CajaErrores->setEnabled(true);
        CajaErrores->setGeometry(QRect(10, 380, 931, 141));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 956, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QStringLiteral("menuBuild"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuFile->addAction(New);
        menuFile->addAction(Open);
        menuFile->addSeparator();
        menuFile->addAction(Save);
        menuFile->addAction(Save_As);
        menuBuild->addAction(actionCompilar);
        mainToolBar->addAction(New);
        mainToolBar->addAction(Open);
        mainToolBar->addAction(actionCompilar);
        mainToolBar->addAction(Save);
        mainToolBar->addAction(Save_As);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        New->setText(QApplication::translate("MainWindow", "New", nullptr));
        Open->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionCompilar->setText(QApplication::translate("MainWindow", "Compile", nullptr));
#ifndef QT_NO_SHORTCUT
        actionCompilar->setShortcut(QApplication::translate("MainWindow", "Ctrl+F5", nullptr));
#endif // QT_NO_SHORTCUT
        Save->setText(QApplication::translate("MainWindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        Save_As->setText(QApplication::translate("MainWindow", "Save As", nullptr));
#ifndef QT_NO_SHORTCUT
        Save_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuBuild->setTitle(QApplication::translate("MainWindow", "Build", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
