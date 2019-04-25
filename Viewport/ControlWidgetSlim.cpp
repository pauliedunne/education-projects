
//
//  ControlWidgetSlim.cpp
//  Viewport
//
//  Created by Paul Dunne
//  Sugarscape Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "ControlWidgetSlim.h"
#include "ui_ControlWidgetSlim.h"
#include "Sugarscape.cpp"

Sugarscape* SugarSlim;

ControlWidgetSlim::ControlWidgetSlim(QWidget *parent) : QMainWindow(parent), ui(new Ui::ControlWidgetSlim)
{
    ui->setupUi(this);
    defaultSetupInit();
    connect(ui->newAction, SIGNAL(triggered()),this,SLOT(newApp()));
    connect(ui->closeAction, SIGNAL(triggered()),this,SLOT(closeApp()));
    connect(ui->actionAbout, SIGNAL(triggered()),this,SLOT(aboutApp()));
}

ControlWidgetSlim::~ControlWidgetSlim()
{
    delete ui;
}

void ControlWidgetSlim::closeApp()
{
    QApplication::closeAllWindows();
}

void ControlWidgetSlim::aboutApp()
{
    QMessageBox aboutBox;


    aboutBox.setText("<b>Viewport 1.0.0</b><br><br>"
                     "Visualization and Prototyping tool for Sugarscape<br><br>"
                     "Viewport maintained and updated by Paul Dunne<br>"
                     "<b>Contact: </b>pauliedunne@hotmail.com<br>"
                     "<b>Website: </b>pauliedunne.com<br><br>"
                     "Sugarscape Copyright (c) 2015 Joseph P Kehoe. All rights reserved.<br>"
                     "<b>Contact: </b>Joseph.Kehoe@itcarlow.ie");
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.exec();
}

/**
 * Restarts Viewport application in Default mode
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::newApp()
{
    ControlWidgetSlim* ControlSlimView = new ControlWidgetSlim();
    ControlSlimView->setWindowTitle("Viewport");
    ControlSlimView->setMinimumSize(425, 500);
    ControlSlimView->setMaximumSize(425, 500);
    ControlSlimView->show();
    this->close();
}

/**
 * Starts the desired Sugarscape Run type
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::on_startBtn_clicked()
{
    if(ui->compactView->isChecked() == true)
    {
        ui->startBtn->setEnabled(false);
        ui->restartBtn->setEnabled(true);
        ui->stopBtn->setEnabled(true);
        defaultRun();
    }
}

/**
 * Stops Sugarscape
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::on_stopBtn_clicked()
{
    ui->stopBtn->setEnabled(false);
    ui->stepBtn->setEnabled(true);
    ui->resumeBtn->setEnabled(true);
    ui->finishBtn->setEnabled(true);
    SugarSlim->stop();
}

/**
 * Step through Sugarscape steps per click
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::on_stepBtn_clicked()
{
    SugarSlim->step();
}

/**
 * Resume executing Sugarscape
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::on_resumeBtn_clicked()
{
    ui->stepBtn->setEnabled(false);
    ui->resumeBtn->setEnabled(false);
    ui->stopBtn->setEnabled(true);
    ui->finishBtn->setEnabled(false);
    SugarSlim->resume();
}

/**
 * Finishes the current Sugarscape
 * @return GraphPort
 * @exception none
 */
void ControlWidgetSlim::on_finishBtn_clicked()
{
    GraphPort graphDialog;
    qDebug() << SugarSlim->getST();
    graphDialog.setData(SugarSlim->getAC(),SugarSlim->getRC(), SugarSlim->getBC(), SugarSlim->getSC(), SugarSlim->getST());
    graphDialog.setupPlot();
    graphDialog.setModal(true);
    graphDialog.exec();

}

/**
 * Restarts the desired Sugarscape Run type
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::on_restartBtn_clicked()
{
    this->setEnabled(false);
    QTest::qWait(1000);
    this->setEnabled(true);
    ui->finishBtn->setEnabled(false);
    on_startBtn_clicked();
}

/**
 * Default run of Sugarscape with Default Rules & Settings
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::defaultRun()    // Default Setup
{
    SugarSlim = new Sugarscape(this, QPoint(25, 100), QSize(375, 375), 0);
    SugarSlim->show();
}

/**
 * Default GUI Setup for Viewport
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::defaultSetupInit()
{
    ui->restartBtn->setEnabled(false);
    ui->stopBtn->setEnabled(false);
    ui->stepBtn->setEnabled(false);
    ui->resumeBtn->setEnabled(false);
    ui->finishBtn->setEnabled(false);

    // View Values
    ui->compactView->setChecked(true);
    ui->advancedView->setChecked(false);
}

/**
 * Changes Viewport from Simple to Advanced
 * @return nothing
 * @exception none
 */
void ControlWidgetSlim::on_setView_clicked()
{
    if(ui->advancedView->isChecked())
    {
        ControlWidget* ControlView = new ControlWidget();
        ControlView->setWindowTitle("Viewport");
        ControlView->setMinimumSize(850, 600);
        ControlView->setMaximumSize(850, 600);
        ControlView->show();
        this->close();
    }
    else
    {
        QMessageBox viewChange;
        viewChange.setText("Unable to change views,\nPlease Select Advanced View!");
        viewChange.setIcon(QMessageBox::Information);
        viewChange.exec();
        return;
    }
}

