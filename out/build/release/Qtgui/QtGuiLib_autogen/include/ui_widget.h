/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnClear;
    QPushButton *btnStartAndStop;
    QChartView *graphicsView;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 586);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        btnClear = new QPushButton(Widget);
        btnClear->setObjectName("btnClear");

        gridLayout->addWidget(btnClear, 0, 0, 1, 1);

        btnStartAndStop = new QPushButton(Widget);
        btnStartAndStop->setObjectName("btnStartAndStop");

        gridLayout->addWidget(btnStartAndStop, 0, 1, 1, 1);

        graphicsView = new QChartView(Widget);
        graphicsView->setObjectName("graphicsView");

        gridLayout->addWidget(graphicsView, 1, 0, 1, 2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btnClear->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\346\233\262\347\272\277", nullptr));
        btnStartAndStop->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
