#ifndef EYETRACKER_H
#define EYETRACKER_H

#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <QDebug>
#include <QObject>
#include <QImage>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class EyeTracker : public QObject {
    Q_OBJECT
public:
    explicit EyeTracker(QObject *parent = 0);
    virtual ~EyeTracker();
    void stop() { isTracking = false; }

public slots:
    void start();

signals:
    void frameReady(QImage img);
    void blinkDetected();
    void finished();
    void log(QString msg);

private:
    const int kMinFace = 300;
    const int kMinEyes = 50;
    const int kFPS = 30;
    const std::string kWindowTitle = "Capture - Face detection";
    const std::string kFaceCascadePath = "./res/haarcascade_frontalface_alt.xml";
    const std::string kEyesCascadePath = "./res/haarcascade_eye_tree_eyeglasses.xml";

    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyesCascade;

    int numEyesCurr = 0;
    int numEyesPrev = 0;
    int numEyesHist = 0;

    bool isTracking = false;

    void msleep(int ms);
    void detectAndDisplay(cv::Mat& frame);
};

#endif // EYETRACKER_H
