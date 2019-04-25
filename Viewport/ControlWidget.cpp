//
//  ControlWidget.cpp
//  Viewport
//
//  Created by Paul Dunne
//  Sugarscape Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "ControlWidget.h"
#include "ui_ControlWidget.h"
#include "Sugarscape.cpp"

Sugarscape* SugarView;

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ControlWidget)
{
    ui->setupUi(this);
    defaultSetupInit();
}

void ControlWidget::closeSugarscape()
{
    sugarThread.isFinished();
    QApplication::closeAllWindows();
}

ControlWidget::~ControlWidget()
{
    delete ui;
    delete SugarView;
}

/**
 * Starts the desired Sugarscape Run type
 * @return nothing
 * @exception none
 */
void ControlWidget::on_startBtn_clicked()
{
    // Default Run
    if(ui->defaultSettings->isChecked() == true)
    {
        ui->startBtn->setEnabled(false);
        ui->restartSugarscape->setEnabled(true);
        ui->stopBtn->setEnabled(true);
        defaultRun();
    }
    // Custom Run
    else if(ui->customSettings->isChecked() == true)
    {
        // Custom needs a config file, so check if there is one
        if(ui->configFilePathBox->text() == "")
        {
            QMessageBox infoBox;
            infoBox.setText("No config selected\n\nPlease add a config file!");
            infoBox.setIcon(QMessageBox::Warning);
            infoBox.exec();

            return;
        }
        else
        {
            ui->startBtn->setEnabled(false);
            ui->restartSugarscape->setEnabled(true);
            ui->stopBtn->setEnabled(true);
            customRun();
        }
    }
}

/**
 * Stops Sugarscape
 * @return nothing
 * @exception none
 */
void ControlWidget::on_stopBtn_clicked()
{
    ui->consoleLog->append(QTime::currentTime().toString() + ": Stopping Sugarscape");
    ui->stopBtn->setEnabled(false);
    ui->stepBtn->setEnabled(true);
    ui->resumeBtn->setEnabled(true);
    ui->finishBtn->setEnabled(true);
    SugarView->stop();
}

/**
 * Step through Sugarscape steps per click
 * @return nothing
 * @exception none
 */
void ControlWidget::on_stepBtn_clicked()
{
    ui->consoleLog->append(QTime::currentTime().toString() + ": Stepping through Sugarscape");
    SugarView->step();
}

/**
 * Resume executing Sugarscape
 * @return nothing
 * @exception none
 */
void ControlWidget::on_resumeBtn_clicked()
{
    ui->consoleLog->append(QTime::currentTime().toString() + ": Resuming Sugarscape");
    ui->stepBtn->setEnabled(false);
    ui->resumeBtn->setEnabled(false);
    ui->stopBtn->setEnabled(true);
    ui->finishBtn->setEnabled(false);
    SugarView->resume();
}

/**
 * Finishes the current Sugarscape
 * @return GraphPort
 * @exception none
 */
void ControlWidget::on_finishBtn_clicked()
{
    // Custom Run needs a Config file, checks before finish
    if(ui->customSettings->isChecked())
    {
        if(configFilePath == "")
        {
            QMessageBox configError;
            configError.setText("Unable to Finish\nCustom Simulation is On\nPlease add a config file!");
            configError.setIcon(QMessageBox::Warning);
            configError.exec();
            return;
        }
    }

    ui->consoleLog->append(QTime::currentTime().toString() + ": Finishing Sugarscape");
    // Creates GraphPort window that will use QCustomPlot
    GraphPort graphDialog;
   // qDebug() << SugarView->getST();
    // Get and Set the data
    graphDialog.setData(SugarView->getAC(),SugarView->getRC(), SugarView->getBC(), SugarView->getSC(), SugarView->getST());
    graphDialog.setupPlot();
    graphDialog.setModal(true);
    graphDialog.exec();

}

/**
 * Restarts the desired Sugarscape Run type
 * @return nothing
 * @exception none
 */
void ControlWidget::on_restartSugarscape_clicked()
{
    // Sets a wait timer so user cannot spam restart
    this->setEnabled(false);
    QTest::qWait(1000);
    this->setEnabled(true);
    ui->finishBtn->setEnabled(false);
    ui->consoleLog->append(QTime::currentTime().toString() + " Restarting Sugarscape");
    on_startBtn_clicked();
}

/**
 * Default run of Sugarscape with Default Rules & Settings
 * @return nothing
 * @exception none
 */
void ControlWidget::defaultRun()    // Default Setup
{
    ui->consoleLog->append(QTime::currentTime().toString() + " Starting Default Sugarscape");
    SugarView = new Sugarscape(this, QPoint(450, 90), QSize(375, 375), 0);
    SugarView->show();
}

/**
 * Custom run of Sugarscape with Custom User Rules & Settings
 * @return nothing
 * @exception none
 */
void ControlWidget::customRun()     // Custom Setup
{
    ui->consoleLog->append(QTime::currentTime().toString() + " Starting Custom Sugarscape");
    SugarView = new Sugarscape(this, QPoint(450, 90), QSize(375, 375), 1, configFilePath);
    SugarView->show();
}

/**
 * Initializes breakpoint parameters on the Sugarscape
 * @return nothing
 * @exception none
 */
void ControlWidget::on_initBreakPoints_clicked()
{
    ui->saveSettings->click();
}

/**
 * Opens FileDialogue to find INI file
 * @return nothing
 * @exception none
 */
void ControlWidget::on_configFileDialogue_clicked()
{
    configFilePath = QFileDialog::getOpenFileName(this, tr("Open INI File"), ".", "INI FIles (*.ini)");
    ui->configFilePathBox->setText(configFilePath);
}

/**
 * Calls and Populates Rule ComboBox
 * @return nothing
 * @exception none
 */
void ControlWidget::on_setConfigFilePath_clicked()
{
    // Takes Rules from Config file and stores in hash table
    QSettings settings(configFilePath, QSettings::IniFormat);

    ui->ChildAmountBox->setText(settings.value("Custom/childAmount").toString());
    ui->CombatLimitBox->setText(settings.value("Custom/combatLimit").toString());
    ui->ConsumptionBox->setText(settings.value("Custom/consumption").toString());
    ui->CultureCountBox->setText(settings.value("Custom/cultureCount").toString());
    ui->DiseaseLengthBox->setText(settings.value("Custom/Custom/diseaseLenght").toString());
    ui->DurationBox->setText(settings.value("Custom/duration").toString());
    ui->ImmunityLengthBox->setText(settings.value("Custom/immunityLength").toString());
    ui->AgentCountBox->setText(settings.value("Custom/initialPopulation").toString());
    ui->InitialPopSizeBox->setText(settings.value("Custom/initialPopulationSize").toString());
    ui->MaxSpiceBox->setText(settings.value("Custom/initialSpiceMax").toString());
    ui->MinSpiceBox->setText(settings.value("Custom/initialSpiceMin").toString());
    ui->MaxSugarBox->setText(settings.value("Custom/initialSugarMax").toString());
    ui->MinSugarBox->setText(settings.value("Custom/initialSugarMin").toString());
    ui->MaxAgeBox->setText(settings.value("Custom/maxAge").toString());
    ui->MaxMetabBox->setText(settings.value("Custom/maxMetabolism").toString());
    ui->MaxVisonBox->setText(settings.value("Custom/maxVision").toString());
    ui->MinAgeBox->setText(settings.value("Custom/minAge").toString());
    ui->MinMetabBox->setText(settings.value("Custom/minMetabolism").toString());
    ui->PollutionRateBox->setText(settings.value("Custom/pollutionRate").toString());
    ui->ProductionBox->setText(settings.value("Custom/production").toString());
    ui->RateBox->setText(settings.value("Custom/rate").toString());
    ui->SeasonLengthBox->setText(settings.value("Custom/seasonLength").toString());
    ui->LaticeSizeBox->setText(settings.value("Custom/size").toString());
    ui->SpiceGrowthBox->setText(settings.value("Custom/spiceGrowth").toString());
    ui->SugarGrowthBox->setText(settings.value("Custom/sugarGrowth").toString());
    ui->WinterRateBox->setText(settings.value("Custom/winterRate").toString());

    ruleBoxInit();
}

/**
 * Sets Rule ComboBox data
 * @return nothing
 * @exception none
 */
void ControlWidget::ruleBoxInit()
{
    // Gets the contents from the config file
    QSettings settings(configFilePath, QSettings::IniFormat);
    settings.beginGroup("Rules");
    const QStringList childKeys = settings.childKeys();
    // Saves contents to a Hash table
    QHash<QString, QString> rules;
    foreach (const QString &childKey, childKeys)
    rules.insert(childKey, settings.value(childKey).toString());
    settings.endGroup();

    // Populates Rule ComboBox
    for(int r = 0; r < rules.count(); r++)
        ui->pendingRuleList->addItem(childKeys[r]);

    QMessageBox infoBox;
    infoBox.setText("Settings Successfully Loaded");
    infoBox.setIcon(QMessageBox::Information);
    infoBox.exec();
}

/**
 * Adds rules to custom rule list ComboBox
 * @return nothing
 * @exception none
 */
void ControlWidget::on_addRules_clicked()
{
    if(ui->pendingRuleList->currentText() != "")
        ui->acceptedRuleList->addItem(ui->pendingRuleList->currentText());
        ui->pendingRuleList->removeItem(ui->pendingRuleList->currentIndex());
}

/**
 * Removes rules from custom rule list ComboBox
 * @return nothing
 * @exception none
 */
void ControlWidget::on_removeRules_clicked()
{
    if(ui->acceptedRuleList->currentText() != "")
        ui->pendingRuleList->addItem(ui->acceptedRuleList->currentText());
        ui->acceptedRuleList->removeItem(ui->acceptedRuleList->currentIndex());
}

/**
 * Takes user data and edits INI file with resulting data
 * @return nothing
 * @exception none
 */
void ControlWidget::on_saveSettings_clicked()
{
    // Checks Custom Config is Set
    if(configFilePath == "")
    {
        QMessageBox configError;
        configError.setText("Unable to Save!\n\nPlease add a config file");
        configError.setIcon(QMessageBox::Warning);
        configError.exec();
        return;
    }

    // Takes Rules from Config file and stores in hash table
    QSettings settings(configFilePath, QSettings::IniFormat);
    settings.beginGroup("Rules");
    const QStringList childKeys = settings.childKeys();
    QHash<QString, QString> rules;
    foreach (const QString &childKey, childKeys)
    rules.insert(childKey, settings.value(childKey).toString());
    settings.endGroup();

    if(ui->customSettings->isChecked())
    {
        // Make added rules true in config file
        for(int i = 0; i < ui->acceptedRuleList->count(); i++)
            for(int j = 0; j < childKeys.size(); j++)
                if(ui->acceptedRuleList->itemText(i) == childKeys[j])
                    settings.setValue("Rules/" + ui->acceptedRuleList->itemText(i), "1");
        // Make un-added rules false in config file
        for(int i = 0; i < ui->pendingRuleList->count(); i++)
            for(int j = 0; j < childKeys.size(); j++)
                if(ui->pendingRuleList->itemText(i) == childKeys[j])
                    settings.setValue("Rules/" + ui->pendingRuleList->itemText(i), "0");

        settings.setValue("Custom/childAmount", ui->ChildAmountBox->text());
        settings.setValue("Custom/combatLimit", ui->CombatLimitBox->text());
        settings.setValue("Custom/consumption", ui->ConsumptionBox->text());
        settings.setValue("Custom/cultureCount", ui->CultureCountBox->text());
        settings.setValue("Custom/diseaseLenght", ui->DiseaseLengthBox->text());
        settings.setValue("Custom/duration", ui->DurationBox->text());
        settings.setValue("Custom/immunityLength", ui->ImmunityLengthBox->text());
        settings.setValue("Custom/initialPopulation", ui->AgentCountBox->text());
        settings.setValue("Custom/initialPopulationSize", ui->InitialPopSizeBox->text());
        settings.setValue("Custom/initialSpiceMax", ui->MaxSpiceBox->text());
        settings.setValue("Custom/initialSpiceMin", ui->MinSpiceBox->text());
        settings.setValue("Custom/initialSugarMax", ui->MaxSugarBox->text());
        settings.setValue("Custom/initialSugarMin", ui->MinSugarBox->text());
        settings.setValue("Custom/maxAge", ui->MaxAgeBox->text());
        settings.setValue("Custom/maxMetabolism", ui->MaxMetabBox->text());
        settings.setValue("Custom/maxVision", ui->MaxVisonBox->text());
        settings.setValue("Custom/minAge", ui->MinAgeBox->text());
        settings.setValue("Custom/minMetabolism", ui->MinMetabBox->text());
        settings.setValue("Custom/pollutionRate", ui->PollutionRateBox->text());
        settings.setValue("Custom/production", ui->ProductionBox->text());
        settings.setValue("Custom/rate", ui->RateBox->text());
        settings.setValue("Custom/seasonLength", ui->SeasonLengthBox->text());
        settings.setValue("Custom/size", ui->LaticeSizeBox->text());
        settings.setValue("Custom/spiceGrowth", ui->SpiceGrowthBox->text());
        settings.setValue("Custom/sugarGrowth", ui->SugarGrowthBox->text());
        settings.setValue("Custom/winterRate", ui->WinterRateBox->text());

        settings.setValue("Timer/simulationTime", ui->simSpeedBox->text());

        if(ui->acbp->text() != "")
            settings.setValue("Breakpoint/agentBreakPoint", ui->acbp->text());
        else { settings.setValue("Breakpoint/agentBreakPoint", "0"); }

        if(ui->redbp->text() != "")
            settings.setValue("Breakpoint/redBreakPoint", ui->redbp->text());
        else { settings.setValue("Breakpoint/redBreakPoint", "0"); }

        if(ui->bluebp->text() != "")
            settings.setValue("Breakpoint/blueBreakPoint", ui->bluebp->text());
        else { settings.setValue("Breakpoint/blueBreakPoint", "0"); }

        if(ui->sugarbp->text() != "")
            settings.setValue("Breakpoint/sugarBreakPoint", ui->sugarbp->text());
        else { settings.setValue("Breakpoint/sugarBreakPoint", "0"); }

        if(ui->spicebp->text() != "")
            settings.setValue("Breakpoint/spiceBreakPoint", ui->spicebp->text());
        else { settings.setValue("Breakpoint/spiceBreakPoint", "0"); }


        QMessageBox successBox;
        successBox.setText("Settings Successfully Saved!");
        successBox.setIcon(QMessageBox::Information);
        successBox.exec();
    }
    else
    {
        ui->consoleLog->append("WARNING: Cannot Save to Default!");
        QMessageBox defaultError;
        defaultError.setText("Cannot Save Default Settings!");
        defaultError.setIcon(QMessageBox::Warning);
        defaultError.exec();
        return;
    }
}

/**
 * Default GUI Setup for Viewport
 * @return nothing
 * @exception none
 */
void ControlWidget::defaultSetupInit()
{
    ui->IntermediateSettings->setEnabled(false);
    ui->BasicSettings->setEnabled(false);
    ui->AdvancedSettings->setEnabled(false);
    ui->RuleSettings->setEnabled(false);
    ui->breakpointSettings->setEnabled(false);
    ui->restartSugarscape->setEnabled(false);
    ui->stopBtn->setEnabled(false);
    ui->stepBtn->setEnabled(false);
    ui->resumeBtn->setEnabled(false);
    ui->finishBtn->setEnabled(false);

    // Settings Values
    ui->defaultSettings->setChecked(true);
    ui->customSettings->setChecked(false);

    // Break Points
    ui->acbp->setEnabled(false);
    ui->redbp->setEnabled(false);
    ui->bluebp->setEnabled(false);
    ui->sugarbp->setEnabled(false);
    ui->spicebp->setEnabled(false);

    // Basic Settings
    ui->LaticeSizeBox->setText("24"), ui->LaticeSlider->setSliderPosition(24);
    ui->AgentCountBox->setText("200"), ui->AgentCountSlider->setSliderPosition(200);
    ui->MinAgeBox->setText("10"), ui->MinAgeSlider->setSliderPosition(10);
    ui->MaxAgeBox->setText("60"), ui->MaxAgeSlider->setSliderPosition(60);
    ui->SugarGrowthBox->setText("10"), ui->SugarGrowthSlider->setSliderPosition(10);
    ui->MinSugarBox->setText("5"), ui->MinSugarSlider->setSliderPosition(5);
    ui->MaxSugarBox->setText("25"), ui->MaxSugarSlider->setSliderPosition(25);
    ui->MinMetabBox->setText("4"), ui->MinMetabSlider->setSliderPosition(4);
    ui->MaxMetabBox->setText("10"), ui->MaxMetabSlider->setSliderPosition(10);
    ui->MaxVisonBox->setText("6"), ui->MaxVisionSlider->setSliderPosition(6);
    ui->ChildAmountBox->setText("4"), ui->ChildAmountSlider->setSliderPosition(4);
    ui->simSpeedBox->setText("1000"), ui->simSpeedSlider->setSliderPosition(1000);

    // Intermediate Settings
    ui->SpiceGrowthBox->setText("10"), ui->SpiceGrowthSlider->setSliderPosition(10);
    ui->MinSpiceBox->setText("5"), ui->MinSpiceSlider->setSliderPosition(5);
    ui->MaxSpiceBox->setText("25"), ui->MaxSpiceSlider->setSliderPosition(25);
    ui->MinSpiceMetabBox->setText("0"), ui->MinSpiceMetabSlider->setSliderPosition(0);
    ui->MaxSpiceMetabBox->setText("0"), ui->MaxSpiceMetabSlider->setSliderPosition(0);
    ui->DurationBox->setText("10"), ui->DurationSlider->setSliderPosition(10);
    ui->RateBox->setText("3"), ui->RateSlider->setSliderPosition(3);
    ui->ProductionBox->setText("2"), ui->ProductionSlider->setSliderPosition(2);
    ui->ConsumptionBox->setText("2"), ui->ConsumptionSlider->setSliderPosition(2);

    // Advanced Settings
    ui->CultureCountBox->setText("20"), ui->CultureCountSlider->setSliderPosition(20);
    ui->DiseaseLengthBox->setText("5"), ui->DiseaseLengthSlider->setSliderPosition(5);
    ui->WinterRateBox->setText("3"), ui->WinterRateSlider->setSliderPosition(3);
    ui->ImmunityLengthBox->setText("30"), ui->ImmunityLengthSlider->setSliderPosition(30);
    ui->InitialPopSizeBox->setText("50"), ui->InitialPopSizeSlider->setSliderPosition(50);
    ui->CombatLimitBox->setText("6"), ui->CombatLimitSlider->setSliderPosition(6);
    ui->SeasonLengthBox->setText("15"), ui->SeasonLengthSlider->setSliderPosition(15);
    ui->PollutionRateBox->setText("2"), ui->PollutionRateSlider->setSliderPosition(2);
}

void ControlWidget::on_customSettings_clicked()
{
    ui->IntermediateSettings->setEnabled(true);
    ui->BasicSettings->setEnabled(true);
    ui->AdvancedSettings->setEnabled(true);
    ui->RuleSettings->setEnabled(true);
    ui->breakpointSettings->setEnabled(true);
}

void ControlWidget::on_defaultSettings_clicked()
{
    ui->IntermediateSettings->setEnabled(false);
    ui->BasicSettings->setEnabled(false);
    ui->AdvancedSettings->setEnabled(false);
    ui->RuleSettings->setEnabled(false);
    ui->breakpointSettings->setEnabled(false);
}

// Sliders for the Custom Settings Data
void ControlWidget::on_LaticeSlider_sliderMoved(int position)
{
    ui->LaticeSizeBox->setText(QString::number(position));
}

void ControlWidget::on_AgentCountSlider_sliderMoved(int position)
{
    ui->AgentCountBox->setText(QString::number(position));
}

void ControlWidget::on_MinAgeSlider_sliderMoved(int position)
{
    ui->MinAgeBox->setText(QString::number(position));
}

void ControlWidget::on_MaxAgeSlider_sliderMoved(int position)
{
    ui->MaxAgeBox->setText(QString::number(position));
}

void ControlWidget::on_SugarGrowthSlider_sliderMoved(int position)
{
    ui->SugarGrowthBox->setText(QString::number(position));
}

void ControlWidget::on_MinSugarSlider_sliderMoved(int position)
{
    ui->MinSugarBox->setText(QString::number(position));
}

void ControlWidget::on_MaxSugarSlider_sliderMoved(int position)
{
    ui->MaxSugarBox->setText(QString::number(position));
}

void ControlWidget::on_MinMetabSlider_sliderMoved(int position)
{
    ui->MinMetabBox->setText(QString::number(position));
}

void ControlWidget::on_MaxMetabSlider_sliderMoved(int position)
{
    ui->MaxMetabBox->setText(QString::number(position));
}

void ControlWidget::on_MaxVisionSlider_sliderMoved(int position)
{
    ui->MaxVisonBox->setText(QString::number(position));
}

void ControlWidget::on_ChildAmountSlider_sliderMoved(int position)
{
    ui->ChildAmountBox->setText(QString::number(position));
}

void ControlWidget::on_SpiceGrowthSlider_sliderMoved(int position)
{
    ui->SpiceGrowthBox->setText(QString::number(position));
}

void ControlWidget::on_MinSpiceSlider_sliderMoved(int position)
{
    ui->MinSpiceBox->setText(QString::number(position));
}

void ControlWidget::on_MaxSpiceSlider_sliderMoved(int position)
{
    ui->MaxSpiceBox->setText(QString::number(position));
}

void ControlWidget::on_MinSpiceMetabSlider_sliderMoved(int position)
{
    ui->MinSpiceMetabBox->setText(QString::number(position));
}

void ControlWidget::on_MaxSpiceMetabSlider_sliderMoved(int position)
{
    ui->MaxSpiceMetabBox->setText(QString::number(position));
}

void ControlWidget::on_DurationSlider_sliderMoved(int position)
{
    ui->DurationBox->setText(QString::number(position));
}

void ControlWidget::on_RateSlider_sliderMoved(int position)
{
    ui->RateBox->setText(QString::number(position));
}

void ControlWidget::on_ProductionSlider_sliderMoved(int position)
{
    ui->ProductionBox->setText(QString::number(position));
}

void ControlWidget::on_ConsumptionSlider_sliderMoved(int position)
{
    ui->ConsumptionBox->setText(QString::number(position));
}

void ControlWidget::on_PollutionRateSlider_sliderMoved(int position)
{
    ui->PollutionRateBox->setText(QString::number(position));
}

void ControlWidget::on_CombatLimitSlider_sliderMoved(int position)
{
    ui->CombatLimitBox->setText(QString::number(position));
}

void ControlWidget::on_SeasonLengthSlider_sliderMoved(int position)
{
    ui->SeasonLengthBox->setText(QString::number(position));
}

void ControlWidget::on_CultureCountSlider_sliderMoved(int position)
{
    ui->CultureCountBox->setText(QString::number(position));
}

void ControlWidget::on_DiseaseLengthSlider_sliderMoved(int position)
{
    ui->DiseaseLengthBox->setText(QString::number(position));
}

void ControlWidget::on_WinterRateSlider_sliderMoved(int position)
{
    ui->WinterRateBox->setText(QString::number(position));
}

void ControlWidget::on_ImmunityLengthSlider_sliderMoved(int position)
{
    ui->ImmunityLengthBox->setText(QString::number(position));
}

void ControlWidget::on_InitialPopSizeSlider_sliderMoved(int position)
{
    ui->InitialPopSizeBox->setText(QString::number(position));
}

// Breakpoint Checkboxes to enable/disable breakpoints
void ControlWidget::on_acBreak_clicked(bool checked)
{
    if(checked)
        ui->acbp->setEnabled(true);
    else
        ui->acbp->setEnabled(false);
}

void ControlWidget::on_redBreak_clicked(bool checked)
{
    if(checked)
        ui->redbp->setEnabled(true);
    else
        ui->redbp->setEnabled(false);
}

void ControlWidget::on_blueBreak_clicked(bool checked)
{
    if(checked)
        ui->bluebp->setEnabled(true);
    else
        ui->bluebp->setEnabled(false);
}

void ControlWidget::on_sugarBreak_clicked(bool checked)
{
    if(checked)
        ui->sugarbp->setEnabled(true);
    else
        ui->sugarbp->setEnabled(false);
}

void ControlWidget::on_spiceBreak_clicked(bool checked)
{
    if(checked)
        ui->spicebp->setEnabled(true);
    else
        ui->spicebp->setEnabled(false);
}
