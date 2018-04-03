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

#include <QtMultimedia/QMediaMetaData>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPalette>

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>

#include "qimagesource.h"

SnapWidget::SnapWidget(QWidget* parent) : QDialog(parent, Qt::Widget| Qt::WindowStaysOnTopHint|  Qt::WindowCloseButtonHint)
{
    setupUi(this);

    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        ui->menuDevices->addAction(videoDeviceAction);
    }

    connect(videoDevicesGroup, &QActionGroup::triggered, this, &SnapWidget::updateCameraDevice);
    connect(ui->captureWidget, &QTabWidget::currentChanged, this, &SnapWidget::updateCaptureMode);

    setCamera(QCameraInfo::defaultCamera());


//    QCameraViewfinder *viewfinder = new QCameraViewfinder(this);
//    viewfinder->show();
//    QCameraImageCapture *cap = new QCameraImageCapture(camera);
//    cap->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
//    camera->setViewfinder(viewfinder);
//    camera->setCaptureMode(QCamera::CaptureStillImage);
//
//    QObject::connect(cap, &QCameraImageCapture::imageCaptured, [=] (int id, QImage img) {
//      QByteArray buf;
//      QBuffer buffer(&buf);
//      buffer.open(QIODevice::WriteOnly);
//      img.save(&buffer, "PNG");
//    });
//
//    QObject::connect(cap, &QCameraImageCapture::readyForCaptureChanged, [=] (bool state) {
//      if(state == true) {
//        camera->searchAndLock();
//        cap->capture();
//        camera->unlock();
//        }
//    });

    show();
}

SnapWidget::~SnapWidget()
{

}

void SnapWidget::on_snapButton_clicked() 
{
//    int _x, _y, _w, _h;
//    _x = geometry().x();
//    _y = geometry().y() + cancelButton->height();
//    _w = geometry().width();
//    _h = geometry().height() - cancelButton->height();
//    QPixmap p;
//#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
//    QScreen *screen = QGuiApplication::primaryScreen();
//    if (screen) {   
//        p = screen->grabWindow(0, _x, _y, _w, _h);
//        }
//#else
//    p = QPixmap::grabWindow(QApplication::desktop()->winId(), _x, _y, _w, _h);
//#endif
//    
//    if (!p.isNull()) {
//        QImage image = p.toImage();
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
//    }

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

void SnapWidget::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &SnapWidget::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &SnapWidget::displayCameraError);

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &SnapWidget::updateRecorderState);

    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &SnapWidget::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &SnapWidget::displayRecorderError);

    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

    connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this, &SnapWidget::setExposureCompensation);

    m_camera->setViewfinder(ui->viewfinder);

    updateCameraState(m_camera->state());
    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &SnapWidget::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &SnapWidget::processCapturedImage);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &SnapWidget::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &SnapWidget::displayCaptureError);

    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &SnapWidget::updateLockStatus);

    ui->captureWidget->setTabEnabled(0, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
    ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    updateCaptureMode();
    m_camera->start();
}

void SnapWidget::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        m_camera->searchAndLock();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (m_camera->captureMode() == QCamera::CaptureStillImage) {
            takeImage();
        } else {
            if (m_mediaRecorder->state() == QMediaRecorder::RecordingState)
                stop();
            else
                record();
        }
        event->accept();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void SnapWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        m_camera->unlock();
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}

void SnapWidget::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
    ui->statusbar->showMessage(str);
}

void SnapWidget::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayCapturedImage();
    QTimer::singleShot(4000, this, &SnapWidget::displayViewfinder);
}

void SnapWidget::configureCaptureSettings()
{
    switch (m_camera->captureMode()) {
    case QCamera::CaptureStillImage:
        configureImageSettings();
        break;
    case QCamera::CaptureVideo:
        configureVideoSettings();
        break;
    default:
        break;
    }
}

void SnapWidget::configureVideoSettings()
{
    VideoSettings settingsDialog(m_mediaRecorder.data());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    settingsDialog.setAudioSettings(m_audioSettings);
    settingsDialog.setVideoSettings(m_videoSettings);
    settingsDialog.setFormat(m_videoContainerFormat);

    if (settingsDialog.exec()) {
        m_audioSettings = settingsDialog.audioSettings();
        m_videoSettings = settingsDialog.videoSettings();
        m_videoContainerFormat = settingsDialog.format();

        m_mediaRecorder->setEncodingSettings(
                    m_audioSettings,
                    m_videoSettings,
                    m_videoContainerFormat);
    }
}

void SnapWidget::configureImageSettings()
{
    ImageSettings settingsDialog(m_imageCapture.data());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    settingsDialog.setImageSettings(m_imageSettings);

    if (settingsDialog.exec()) {
        m_imageSettings = settingsDialog.imageSettings();
        m_imageCapture->setEncodingSettings(m_imageSettings);
    }
}

void SnapWidget::record()
{
    m_mediaRecorder->record();
    updateRecordTime();
}

void SnapWidget::pause()
{
    m_mediaRecorder->pause();
}

void SnapWidget::stop()
{
    m_mediaRecorder->stop();
}

void SnapWidget::setMuted(bool muted)
{
    m_mediaRecorder->setMuted(muted);
}

void SnapWidget::toggleLock()
{
    switch (m_camera->lockStatus()) {
    case QCamera::Searching:
    case QCamera::Locked:
        m_camera->unlock();
        break;
    case QCamera::Unlocked:
        m_camera->searchAndLock();
    }
}

void SnapWidget::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
        ui->statusbar->showMessage(tr("Focusing..."));
        ui->lockButton->setText(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
        ui->lockButton->setText(tr("Unlock"));
        ui->statusbar->showMessage(tr("Focused"), 2000);
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
        ui->lockButton->setText(tr("Focus"));
        if (reason == QCamera::LockFailed)
            ui->statusbar->showMessage(tr("Focus Failed"), 2000);
    }

    QPalette palette = ui->lockButton->palette();
    palette.setColor(QPalette::ButtonText, indicationColor);
    ui->lockButton->setPalette(palette);
}

void SnapWidget::takeImage()
{
    m_isCapturingImage = true;
    m_imageCapture->capture();
}

void SnapWidget::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void SnapWidget::startCamera()
{
    m_camera->start();
}

void SnapWidget::stopCamera()
{
    m_camera->stop();
}

void SnapWidget::updateCaptureMode()
{
    int tabIndex = ui->captureWidget->currentIndex();
    QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;

    if (m_camera->isCaptureModeSupported(captureMode))
        m_camera->setCaptureMode(captureMode);
}

void SnapWidget::updateCameraState(QCamera::State state)
{
    switch (state) {
    case QCamera::ActiveState:
        ui->actionStartCamera->setEnabled(false);
        ui->actionStopCamera->setEnabled(true);
        ui->captureWidget->setEnabled(true);
        ui->actionSettings->setEnabled(true);
        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        ui->actionStartCamera->setEnabled(true);
        ui->actionStopCamera->setEnabled(false);
        ui->captureWidget->setEnabled(false);
        ui->actionSettings->setEnabled(false);
    }
}

void SnapWidget::updateRecorderState(QMediaRecorder::State state)
{
    switch (state) {
    case QMediaRecorder::StoppedState:
        ui->recordButton->setEnabled(true);
        ui->pauseButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        break;
    case QMediaRecorder::PausedState:
        ui->recordButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        break;
    case QMediaRecorder::RecordingState:
        ui->recordButton->setEnabled(false);
        ui->pauseButton->setEnabled(true);
        ui->stopButton->setEnabled(true);
        break;
    }
}

void SnapWidget::setExposureCompensation(int index)
{
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void SnapWidget::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void SnapWidget::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void SnapWidget::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void SnapWidget::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void SnapWidget::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void SnapWidget::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}

void SnapWidget::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    ui->statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));

    m_isCapturingImage = false;
    if (m_applicationExiting)
        close();
}

void SnapWidget::closeEvent(QCloseEvent *event)
{
    if (m_isCapturingImage) {
        setEnabled(false);
        m_applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}

