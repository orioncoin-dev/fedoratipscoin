// Copyright (c) 2013-2015 The Fedoracoin developers

#ifndef SNAPWIDGET_H
#define SNAPWIDGET_H
#include "ui_snapwidget.h"
#include "addressbookpage.h"

#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/qcameraviewfinder.h>

#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimedia/QMediaRecorder>
#include <QtCore/QScopedPointer>

namespace Ui { class SnapWidget; }

class SnapWidget :public QDialog, public Ui::SnapWidget
{
    Q_OBJECT
public:

    SnapWidget(QWidget* _parent);
    ~SnapWidget();
    virtual void closeEvent(QCloseEvent *event);
    public slots:
    void on_cancelButton_clicked();
    void on_snapButton_clicked();

signals:
    void finished(QString s);

public:
    QString decodedString;

private slots:
    void setCamera(const QCameraInfo &cameraInfo);

    void startCamera();
    void stopCamera();

    void record();
    void pause();
    void stop();
    void setMuted(bool);

    void toggleLock();
    void takeImage();
    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);

    void configureCaptureSettings();
    void configureVideoSettings();
    void configureImageSettings();

    void displayRecorderError();
    void displayCameraError();

    void updateCameraDevice(QAction *action);

    void updateCameraState(QCamera::State);
    void updateCaptureMode();
    void updateRecorderState(QMediaRecorder::State state);
    void setExposureCompensation(int index);

    void updateRecordTime();

    void processCapturedImage(int requestId, const QImage &img);
    void updateLockStatus(QCamera::LockStatus, QCamera::LockChangeReason);

    void displayViewfinder();
    void displayCapturedImage();

    void readyForCapture(bool ready);
    void imageSaved(int id, const QString &fileName);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::SnapWidget *ui;

    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    QImageEncoderSettings m_imageSettings;
    QAudioEncoderSettings m_audioSettings;
    QVideoEncoderSettings m_videoSettings;
    QString m_videoContainerFormat;
    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
};

#endif // SNAPWIDGET_H
