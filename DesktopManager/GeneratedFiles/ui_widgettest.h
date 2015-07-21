/********************************************************************************
** Form generated from reading UI file 'widgettest.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETTEST_H
#define UI_WIDGETTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetTestClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *widgetTestClass)
    {
        if (widgetTestClass->objectName().isEmpty())
            widgetTestClass->setObjectName(QStringLiteral("widgetTestClass"));
        widgetTestClass->resize(1350, 1035);
        centralWidget = new QWidget(widgetTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widgetTestClass->setCentralWidget(centralWidget);

        retranslateUi(widgetTestClass);

        QMetaObject::connectSlotsByName(widgetTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *widgetTestClass)
    {
        widgetTestClass->setWindowTitle(QApplication::translate("widgetTestClass", "widgetTest", 0));
    } // retranslateUi

};

namespace Ui {
    class widgetTestClass: public Ui_widgetTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETTEST_H
