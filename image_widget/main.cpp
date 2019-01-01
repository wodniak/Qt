#include <QtWidgets>
#include "image_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageWidget imagewidget ;
    imagewidget.show();
    return a.exec();
}