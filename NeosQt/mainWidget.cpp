#include <QtWidgets>
#include <QProcess>
#include "mainWidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
   button_ = new QPushButton(tr("Push Me!"));
   textBrowser_ = new QTextBrowser();
    process_ = new QProcess();

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,0,0);
   mainLayout->addWidget(textBrowser_,1,0);
   setLayout(mainLayout);
   setWindowTitle(tr("Connecting buttons to processes.."));

    // Connect the Buttons "released" signal to MainWidget's onButtonReleased method.
    connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
    connect(process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));

}

// Destructor
MainWidget::~MainWidget()
{
   delete button_;
   delete textBrowser_;
   delete process_;
}


//handler for pressing button
void MainWidget::onButtonReleased()    
{
    textBrowser_->clear();
    textBrowser_->append(tr("Running command:"));
    std::cout << "button\n";
    // Set up our process to write to stdout and run our command
    process_->setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
    process_->start(tr("ls -alh $HOME/Desktop")); // Start the program
    if(process_->waitForStarted())
        std::cout << "process started\n";
}


// Handler for Process output
// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MainWidget::onCaptureProcessOutput()
{
    textBrowser_->append(tr("CLICKED"));
    // Determine whether the object that sent the signal was a pointer to a process
    QProcess* process = qobject_cast<QProcess*>(sender());
    // If so, append the output to the textbrowser
    if (process)
        textBrowser_->append(process_->readAllStandardOutput());
}
