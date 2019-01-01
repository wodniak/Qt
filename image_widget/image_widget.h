#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QString>
#include <QDebug>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = 0); //Constructor
    ~ImageWidget(); // Destructor

private slots:
    void loadImg();
    void deleteImg();
    void makeHistogram();

private:
    QPixmap*     _image;         //to load an image
    QLabel*      _imgLabel;      //to show image
    QLabel*      _histLabel;      //to show histogram
    QLineEdit*   _imgName;
    QPushButton* _buttonDelete;    
    QPushButton* _buttonLoad;    
    QPushButton* _buttonHistOrdinary;
    QPushButton* _buttonHistCumulative;


    QString      _path;
};

#endif //IMAGEWIDGET_H