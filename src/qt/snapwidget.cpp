// Copyright (c) 2013-2015 The Fedoracoin developers

#include "snapwidget.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QDialog>
#include <QtMultimedia/QtMultimedia>
#else
#include <QtWidgets/QDesktopWidget>
#endif

#include <QtCore/QtGlobal>
#ifndef _isnan
inline bool _isnan(float v) {return qIsNaN(v);}
#endif

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>

#include "qimagesource.h"

SnapWidget::SnapWidget(QWidget* parent) : QDialog(parent, Qt::Widget| Qt::WindowStaysOnTopHint|  Qt::WindowCloseButtonHint)
{
    setupUi(this);
    this->setMinimumWidth(50);

//    camera = new QCamera;
//    QCameraViewfinder *viewfinder = new QCameraViewfinder(this);
//    viewfinder->show();
//    QCameraImageCapture *cap = new QCameraImageCapture(camera);
//    cap->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
//    camera->setViewfinder(viewfinder);
//    camera->setCaptureMode(QCamera::CaptureStillImage);

//    QObject::connect(cap, &QCameraImageCapture::imageCaptured, [=] (int id, QImage img) {
//      QByteArray buf;
//      QBuffer buffer(&buf);
//      buffer.open(QIODevice::WriteOnly);
//      img.save(&buffer, "PNG");
//    });

//    QObject::connect(cap, &QCameraImageCapture::readyForCaptureChanged, [=] (bool state) {
//      if(state == true) {
//        camera->searchAndLock();
//        cap->capture();
//        camera->unlock();
//        }
//    });

//    camera->start();
    show();
}

SnapWidget::~SnapWidget()
{

}

void SnapWidget::on_snapButton_clicked() 
{
    int _x, _y, _w, _h;
    _x = geometry().x();
    _y = geometry().y() + cancelButton->height();
    _w = geometry().width();
    _h = geometry().height() - cancelButton->height();
    QPixmap p;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {   
        p = screen->grabWindow(0, _x, _y, _w, _h);
        }
#else
    p = QPixmap::grabWindow(QApplication::desktop()->winId(), _x, _y, _w, _h);
#endif
    
    if (!p.isNull()) {
        QImage image = p.toImage();
//        Ref<Result> r;
//        MultiFormatReader* qrDecoder = new MultiFormatReader();
//        QImageLuminanceSource* lumImage = new QImageLuminanceSource(image);
//        Ref<LuminanceSource> imageRef(lumImage);
//        GlobalHistogramBinarizer* binarizer = new GlobalHistogramBinarizer(imageRef);
//        Ref<Binarizer> binarizerRef(binarizer);
//        BinaryBitmap* binaryBitmap = new BinaryBitmap(binarizerRef);
//        Ref<BinaryBitmap> binaryBitmapRef(binaryBitmap);
//        try {
//            r = qrDecoder->decode(binaryBitmapRef, DecodeHints::QR_CODE_HINT);
//        }
//        catch (Exception e) {
//            delete qrDecoder;
//            close();
//            return;
//        }
//
//        Ref<String> s = r->getText();
//        const std::string ss = s->getText(); 
//        decodedString = QString(ss.c_str());
//
//        delete qrDecoder;
    }
    this->close();
}

void SnapWidget::on_cancelButton_clicked() 
{
    this->close();
}

void SnapWidget::closeEvent(QCloseEvent *event)
{
    emit finished(decodedString);
}
