#include "image_widget.h"

using cv::Mat, cv::Point, cv::Scalar, cv::namedWindow;

/*
 *  Init all component widgets
 */
ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    //init image window
    _imgLabel = new QLabel();      
    _imgLabel->setAlignment(Qt::AlignLeft);
    
    _histLabel = new QLabel();
    _histLabel->setAlignment(Qt::AlignLeft);

    //init buttons
    _buttonLoad             = new QPushButton(tr("Load image"));
    _buttonDelete           = new QPushButton(tr("Delete image"));
    _buttonHistOrdinary     = new QPushButton(tr("Ordinary"));
    _buttonHistCumulative   = new QPushButton(tr("Cumulative"));

    //init text window
    _imgName = new QLineEdit(); 

    //init layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(_imgLabel, 4,1,70,70);
    mainLayout->addWidget(_histLabel, 4,50,50,60);
    mainLayout->addWidget(_imgName, 1,2,1,15);
    mainLayout->addWidget(_buttonLoad, 1,1);
    mainLayout->addWidget(_buttonDelete, 2,1);
    mainLayout->addWidget(_buttonHistOrdinary, 1,20);
    mainLayout->addWidget(_buttonHistCumulative, 1,21);

    setLayout(mainLayout);
    setWindowTitle(tr("Image Widget"));

    //setup connections
    connect(_buttonLoad, SIGNAL(clicked()), this, SLOT(loadImg()));         //pressing loading button
    connect(_buttonDelete, SIGNAL(clicked()), this, SLOT(deleteImg()));     //pressing delete button
    connect(_buttonHistOrdinary, SIGNAL(clicked()), this, SLOT(makeHistogram()));
}

/**
 *  Only free memory 
 */ 
ImageWidget::~ImageWidget()
{

}

/**
 *   Invoked when Load Image Button is pressed
 *   Read path to image from lineEdit and show it in label
 */ 
void ImageWidget::loadImg()
{
    //check sender
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(button != NULL);

    //get path from input field
    _path = _imgName->text();
    qDebug() << "Loading image from path: " << _path;

    //TODO: check path exist?

    //load image
    _image = new QPixmap(_path);
    _imgLabel->setPixmap(_image->scaled(600,600,
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation));
    qDebug() << "Image loaded successfully";
}

/**
 *  Invoked when Delete Image Button is pressed
 *  Unload image and display text
 */ 
void ImageWidget::deleteImg()
{
    _imgLabel->clear();
    _imgLabel->setText(tr("empty"));
    
    _histLabel->clear();
    _histLabel->setText(tr("empty"));
    
}

/**
 *  Invoked when Delete Image Button is pressed
 *  Makes 3 channel histogram
 *  Shows each channel and combined histogram
 */
void ImageWidget::makeHistogram()
{
	Mat src;
	src = cv::imread(_path.toStdString().c_str(), 1);    //QString -> C++11 string -> c string

	// Separate the image in 3 places ( B, G and R )
	std::vector<cv::Mat> bgr_planes;
	split(src, bgr_planes);

	// Establish the number of bins
	int histSize = 256;

	// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, Mat());

	// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	//threshold
	threshold(bgr_planes[0], bgr_planes[0], 130, 255, 0);
	threshold(bgr_planes[2], bgr_planes[2], 160, 255, 0);

	// Display
    //convert Mat -> QImage -> pixmap
    _histLabel->setPixmap(QPixmap::fromImage(QImage(histImage.data,
                                                    histImage.cols,
                                                    histImage.rows,
                                                    histImage.step,
                                                    QImage::Format_RGB888).scaled(400,400,
                                                                                  Qt::KeepAspectRatio,
                                                                                  Qt::SmoothTransformation)));
}
