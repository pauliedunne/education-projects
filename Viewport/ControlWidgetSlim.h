//
//  ControlWidgetSlim.h
//  Viewport
//
//  Created by Paul Dunne
//  Sugarscape Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef CONTROLWIDGETSLIM_H
#define CONTROLWIDGETSLIM_H

#include <QMainWindow>
#include <QWidget>
#include <QCoreApplication>
#include <QThread>
#include <QSettings>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QTest>
#include "GraphPort.h"
#include "ControlWidget.h"

namespace Ui {
class ControlWidgetSlim;
}

class ControlWidgetSlim : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWidgetSlim(QWidget *parent = 0);
    ~ControlWidgetSlim();
    int steps = 0;
    QString configFilePath = "";
    bool customWindow();

private slots:
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
    void on_stepBtn_clicked();
    void on_resumeBtn_clicked();
    void on_finishBtn_clicked();
    void defaultRun();
    void defaultSetupInit();
    void on_setView_clicked();
    void on_restartBtn_clicked();
    void closeApp();
    void newApp();
    void aboutApp();

private:
    Ui::ControlWidgetSlim *ui;
};

#endif // CONTROLWIDGETSLIM_H
