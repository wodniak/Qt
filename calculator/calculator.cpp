#include "calculator.h"

/**
 * Constructor
 */
Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    //init calculator values
    a = 0;
    b = 0;
    action = NOT_DEF;

    //init digits
    for(int i=0; i<10; ++i)
    {
        __digits[i] = new QPushButton(QString::number(i));
    }

    //init actions
    __button_add    = new QPushButton(tr("+"));
    __button_minus  = new QPushButton(tr("-"));
    __button_reset  = new QPushButton(tr("C"));
    __button_calc   = new QPushButton(tr("="));
   
   //init screen
    __screen = new QLabel();
    __screen->setAlignment(Qt::AlignLeft);

    //init layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //add all to layout
    mainLayout->addWidget(__screen,0,0,1,6);
    mainLayout->addWidget(__button_reset,1,0);
    mainLayout->addWidget(__button_add,2,0);
    mainLayout->addWidget(__button_minus,3,0);
    mainLayout->addWidget(__button_calc,4,0);

    for(int i=0; i<10; ++i)
    {
        if(i==0)
            mainLayout->addWidget(__digits[i], 5, 2);    

        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(__digits[i], row, column);    
    }

    setLayout(mainLayout);
    setWindowTitle(tr("simple_calculator"));

    // Connect buttons with slots
    connect(__button_reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(__button_add, SIGNAL(clicked()), this, SLOT(add()));
    connect(__button_minus, SIGNAL(clicked()), this, SLOT(minus()));
    connect(__button_calc, SIGNAL(clicked()), this, SLOT(calc()));

    for(int i=0; i<10; ++i)
    {
        connect(__digits[i], SIGNAL(clicked()), this, SLOT(digit_pressed()));
    }
}

/**
 * Destructor
 */
Calculator::~Calculator()
{
   delete[] __digits;
   delete __button_add;
   delete __button_minus;
   delete __button_reset;
   delete __button_calc;
   delete __screen;
}

/**
 *  Get number from button
 */
void Calculator::digit_pressed()
{
    //check if sender is button
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(button)
    {
        int value = button->text().toInt();
        __screen->setText(__screen->text() + QString::number(value));
    }
    else
        std::cout << "button error\n";
}

/**
 *  Reset screen and all data
 */
void Calculator::reset()
{
    //check if sender is button
    QPushButton* reset = qobject_cast<QPushButton*>(sender());
    if(reset)
    {
        __screen->clear();

    }
    else
        std::cout << "reset error\n";
}

/**
 *  Indicate that you want to add values
 */
void Calculator::add()
{
    //check if sender is button
    QPushButton* add = qobject_cast<QPushButton*>(sender());
    if(add)
    {
        action = ADD;
        a = __screen->text().toInt();
        __screen->clear();

    }
    else
        std::cout << "add error\n";
}

/**
 *  Indicate that you want to substract values
 */
void Calculator::minus()
{
    //check if sender is button
    QPushButton* minus = qobject_cast<QPushButton*>(sender());
    if(minus)
    {
        action = MINUS;
        a = __screen->text().toInt();
        __screen->clear();
    }
    else
        std::cout << "add error\n";

}

/**
 *  Perform an action if defined
 */
void Calculator::calc()
{
    b = __screen->text().toInt();
    __screen->clear();
    switch(action)
    {
        case ADD:
            __screen->setText(QString::number(a+b));
            action = NOT_DEF;
            break;
        
        case MINUS:
            __screen->setText(QString::number(a-b));
            action = NOT_DEF;
            break;

        case NOT_DEF:
            std::cout << "Define action\n";
            break;
    }
}