#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <iostream>

//forward declarations
class QPushButton;
class QTextBrowser;
class QProcess;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor

private slots:
    void onButtonReleased();    //handler for pressing button
    void onCaptureProcessOutput(); // Handler for Process output

private:
   QPushButton* button_;
   QTextBrowser* textBrowser_;
   QProcess* process_;
};

#endif // MAINWIDGET_H