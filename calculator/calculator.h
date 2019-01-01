#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QtWidgets>
#include <iostream>
#include <QString>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0); //Constructor
    ~Calculator(); // Destructor

private slots:
    void digit_pressed();
    void reset();
    void add();
    void minus();
    void calc();

private:
    QPushButton* __digits[10];
    QPushButton* __button_add;
    QPushButton* __button_minus;
    QPushButton* __button_reset;
    QPushButton* __button_calc;
    QLabel*      __screen;

    enum { NOT_DEF  = 0,
           ADD      = 1,
           MINUS    = 2};

    int a;
    int b;
    int action;

};
#endif //CALCULATOR_H