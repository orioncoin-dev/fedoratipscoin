// Copyright (c) 2013-2015 The Fedoracoin developers

#ifndef SNAPWIDGET_H
#define SNAPWIDGET_H
#include "ui_snapwidget.h"
#include "addressbookpage.h"

#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/qcameraviewfinder.h>

class SnapWidget :public QDialog, public Ui::SnapWidget
{
    Q_OBJECT

    QCamera camera;
    QCameraViewfinder viewfinder;
    QCameraImageCapture imageCapture;

public:

    SnapWidget(QWidget* _parent);
    ~SnapWidget();
    void prepareMask();
    virtual void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent*);
    public slots:
    void on_cancelButton_clicked();
    void on_snapButton_clicked();


signals:
    void finished(QString s);

public:
    QString decodedString;

};
#endif // SNAPWIDGET_H
