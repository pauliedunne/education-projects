//
//  ControlWidget.h
//  Viewport
//
//  Created by Paul Dunne
//  Sugarscape Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

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
#include "qcustomplot.h"


namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT
    QThread sugarThread;

public:
    explicit ControlWidget(QWidget *parent = 0);
    ~ControlWidget();

private:
    Ui::ControlWidget *ui;
    int steps = 0;
    QString configFilePath = "";

private slots:
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
    void on_stepBtn_clicked();
    void on_resumeBtn_clicked();
    void on_addRules_clicked();
    void on_removeRules_clicked();
    void on_restartSugarscape_clicked();
    void defaultRun();
    void customRun();
    void on_LaticeSlider_sliderMoved(int position);
    void on_AgentCountSlider_sliderMoved(int position);
    void on_MinAgeSlider_sliderMoved(int position);
    void on_MaxAgeSlider_sliderMoved(int position);
    void on_SugarGrowthSlider_sliderMoved(int position);
    void on_MinSugarSlider_sliderMoved(int position);
    void on_MaxSugarSlider_sliderMoved(int position);
    void on_MinMetabSlider_sliderMoved(int position);
    void on_MaxMetabSlider_sliderMoved(int position);
    void on_saveSettings_clicked();
    void on_MaxVisionSlider_sliderMoved(int position);
    void on_ChildAmountSlider_sliderMoved(int position);
    void on_SpiceGrowthSlider_sliderMoved(int position);
    void on_MinSpiceSlider_sliderMoved(int position);
    void on_MaxSpiceSlider_sliderMoved(int position);
    void on_MinSpiceMetabSlider_sliderMoved(int position);
    void on_MaxSpiceMetabSlider_sliderMoved(int position);
    void on_DurationSlider_sliderMoved(int position);
    void on_RateSlider_sliderMoved(int position);
    void on_ProductionSlider_sliderMoved(int position);
    void on_ConsumptionSlider_sliderMoved(int position);
    void on_PollutionRateSlider_sliderMoved(int position);
    void on_CombatLimitSlider_sliderMoved(int position);
    void on_SeasonLengthSlider_sliderMoved(int position);
    void on_CultureCountSlider_sliderMoved(int position);
    void on_DiseaseLengthSlider_sliderMoved(int position);
    void on_WinterRateSlider_sliderMoved(int position);
    void on_ImmunityLengthSlider_sliderMoved(int position);
    void on_InitialPopSizeSlider_sliderMoved(int position);
    void defaultSetupInit();
    void on_customSettings_clicked();
    void ruleBoxInit();
    void on_defaultSettings_clicked();
    void on_configFileDialogue_clicked();
    void on_setConfigFilePath_clicked();
    void on_finishBtn_clicked();

    void closeSugarscape();
    void on_acBreak_clicked(bool checked);
    void on_redBreak_clicked(bool checked);
    void on_blueBreak_clicked(bool checked);
    void on_sugarBreak_clicked(bool checked);
    void on_spiceBreak_clicked(bool checked);
    void on_initBreakPoints_clicked();
};

#endif // CONTROLWIDGET_H
