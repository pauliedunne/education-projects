
//
//  Sugarscape.cpp
//  Viewport
//
//  Created by Paul Dunne
//  Sugarscape Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "QSFMLCanvas.h"
#include <QApplication>

#include <QObject>
#include <QWidget>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <QtCore>

#include "World.h"
#include "Growback.h"
#include "SeasonalGrowback.h"
#include "PollutionFormation.h"
#include "GarbageCollection.h"
#include "AgentMove.h"
#include "AgentCulture.h"
#include "AgentDeath.h"
#include "AgentDisease.h"
#include "Diffusion.h"
#include "AgentCombat.h"
#include "AgentReplacement.h"
#include "AgentMetabolism.h"
#include "AgentMating.h"
#include "AgentLoanPayments.h"
#include "AgentCredit.h"
#include "ViewPort.h"

#include <QTest>
#include <QDebug>
#include <QHash>
#include <QMessageBox>

// Possible TO-DO: Integrate ViewPort.cpp and Sugarscape.cpp
// Overlapping functionality calls from both classes

class Sugarscape : public QSFMLCanvas
{
private :
    int runningType = 0;
    QString filePath = QApplication::applicationDirPath();
    int agentBreakPoint = 0;
    int redBreakPoint;
    int blueBreakPoint;
    int sugarBreakPoint;
    int spiceBreakPoint;
    int agentRefreshTime = 1000;

public :
    /**
     * Constructor
     * @param Parent : Window we want to draw on
     * @param Position : Position of Window
     * @param Size : Size of Sugarscape Window
     * @param RunType : Default
     * @see Sugarscape
     * @exception none
     */
    Sugarscape(QWidget* Parent, const QPoint& Position, const QSize& Size, int RunType) : QSFMLCanvas(Parent, Position, Size)
    {
        runningType = RunType;
    }

    /**
     * Constructor
     * @param Parent : Window we want to draw on
     * @param Position : Position of Window
     * @param Size : Size of Sugarscape Window
     * @param RunType : Custom
     * @param path : Path to Config file
     * @see Sugarscape
     * @exception none
     */
    Sugarscape(QWidget* Parent, const QPoint& Position, const QSize& Size, int RunType, QString path) : QSFMLCanvas(Parent, Position, Size)
    {
        runningType = RunType;
        filePath = path;
    }

    World theWorld;
    ViewPort theGUI;
    bool isRunning = false;
    int ruleType = 0;

    /**
     Handles the Initialization of Sugarscape
     @returns nothing
     @exception void
     */
    void OnInit()
    {
        int dimension = 24;
        theWorld.init(dimension);
        theGUI.init(this,&theWorld,std::pair<int,int>(360, 360),std::pair<int,int>(1,1),theWorld.getSize());
        theWorld.sync();
        //theWorld.sanityCeck();

        Growback growback(&theWorld);
        SeasonalGrowback seasonalGrowback(&theWorld);
        AgentMove move(&theWorld);
        PollutionFormation pollForm(&theWorld);
        GarbageCollection gc(&theWorld);
        AgentCulture agentCulture(&theWorld);
        AgentDeath agentDeath(&theWorld);
        AgentDisease agentDisease(&theWorld);
        Diffusion diffusion(&theWorld);
        AgentCombat agentCombat(&theWorld);
        AgentReplacement agentReplacement(&theWorld);
        AgentMating agentMating(&theWorld);
        AgentMetabolism agentMetabolism(&theWorld);
        AgentCredit agentCredit(&theWorld);
        AgentLoanPayments agentLoanPayments(&theWorld);

        //!
        /*!
         Add the rules we are using here.
         */

        // Default Run
        if(getRunningType() == 0) {
            theWorld.addRule(&growback);
            theWorld.addRule(&move);
            theWorld.addRule(&agentMating);
            theWorld.addRule(&agentMetabolism);
            theWorld.addRule(&agentDeath);
        }
        // Custom Run
        if(getRunningType() == 1) {
            QSettings settings(filePath, QSettings::IniFormat);
            settings.beginGroup("Rules");
            const QStringList ck = settings.childKeys();
            QHash<QString, QString> rules;
            foreach (const QString &childKey, ck)
            rules.insert(childKey, settings.value(childKey).toString());
            settings.endGroup();

            //
            for(int i = 0; i < rules.size(); i++)
            {
                if(rules.value("AgentMovement") == "1") theWorld.addRule(&move);
                if(rules.value("AgentMating") == "1") theWorld.addRule(&agentMating);
                if(rules.value("AgentCombat") == "1") theWorld.addRule(&agentCombat);
                if(rules.value("AgentCulture") == "1") theWorld.addRule(&agentCulture);
                if(rules.value("AgentReplacement") == "1") theWorld.addRule(&agentReplacement);
                if(rules.value("AgentMetabolism") == "1") theWorld.addRule(&agentMetabolism);
                if(rules.value("AgentDeath") == "1") theWorld.addRule(&agentDeath);
                if(rules.value("Growback") == "1") theWorld.addRule(&growback);
                if(rules.value("SeasonalGrowback") == "1") theWorld.addRule(&seasonalGrowback);
                if(rules.value("PollutionFormation") == "1") theWorld.addRule(&pollForm);
                if(rules.value("Diffusion") == "1") theWorld.addRule(&diffusion);
                if(rules.value("GC") == "1") theWorld.addRule(&gc);
                if(rules.value("AgentCredit") == "1") theWorld.addRule(&agentCredit);
                if(rules.value("AgentLoanPayments") == "1") theWorld.addRule(&agentLoanPayments);
                if(rules.value("AgentDisease") == "1") theWorld.addRule(&agentDisease);
            }

//            // TO-DO - Finish Dynamic Rule Finding (Code created, but not fully implemented below)
//            QHash<QString, Action*> registeredRules = theWorld.returnRegisteredRules();

//            for(int i = 0; i < ck.size(); i++)
//            {
//                for(int j = 0; j < registeredRules.size(); j++)
//                {
//                    if(registeredRules.key(j) == ck[j])
//                    {
//                        theWorld.addRule(registeredRules.value(j));
//                    }
//                }
//            }

//            theWorld.registerRules("AgentMovement", &move);
//            theWorld.registerRules("AgentMating", &agentMating);
//            theWorld.registerRules("AgentCombat", &agentCombat);
//            theWorld.registerRules("AgentCulture", &agentCulture);
//            theWorld.registerRules("AgentReplacement", &agentReplacement);
//            theWorld.registerRules("AgentMetabolism", &agentMetabolism);
//            theWorld.registerRules("AgentDeath", &agentDeath);
//            theWorld.registerRules("Growback", &growback);
//            theWorld.registerRules("SeasonalGrowback", &seasonalGrowback);
//            theWorld.registerRules("PollutionFormation", &pollForm);
//            theWorld.registerRules("Diffusion", &diffusion);
//            theWorld.registerRules("GC", &gc);
//            theWorld.registerRules("AgentCredit", &agentCredit);
//            theWorld.registerRules("AgentLoanPayments", &agentLoanPayments);
//            theWorld.registerRules("AgentDisease", &agentDisease);

            settings.beginGroup("Custom");
            const QStringList childKeys = settings.childKeys();
            QHash<QString, QString> customSettings;
            foreach (const QString &childKey, childKeys)
            customSettings.insert(childKey, settings.value(childKey).toString());
            settings.endGroup();

            theWorld.setSize(customSettings.value("size").toInt());
            theWorld.setCultureCount(customSettings.value("cultureCount").toInt());
            theWorld.setDiseaseLength(customSettings.value("diseaseLenght").toInt());
            theWorld.setMaxVision(customSettings.value("maxVision").toInt());
            theWorld.setMinMetabolism(customSettings.value("minMetabolism").toInt());
            theWorld.setMaxMetabolism(customSettings.value("maxMetabolism").toInt());
            theWorld.setSugarGrowth(customSettings.value("sugarGrowth").toInt());
            theWorld.setSpiceGrowth(customSettings.value("spiceGrowth").toInt());
            theWorld.setMinAge(customSettings.value("minAge").toInt());
            theWorld.setMaxAge(customSettings.value("maxAge").toInt());
            theWorld.setDuration(customSettings.value("duration").toInt());
            theWorld.setRate(customSettings.value("rate").toInt());
            theWorld.setInitialSugarMin(customSettings.value("initialSugarMin").toInt());
            theWorld.setInitialSugarMax(customSettings.value("initialSugarMax").toInt());
            theWorld.setInitialSpiceMin(customSettings.value("initialSpiceMin").toInt());
            theWorld.setInitialSpiceMax(customSettings.value("initialSpiceMax").toInt());
            theWorld.setWinterRate(customSettings.value("winterRate").toInt());
            theWorld.setSeasonLength(customSettings.value("seasonLength").toInt());
            theWorld.setProduction(customSettings.value("production").toInt());
            theWorld.setConsumption(customSettings.value("consumption").toInt());
            theWorld.setCombatLimit(customSettings.value("combatLimit").toInt());
            theWorld.setImmunityLength(customSettings.value("immunityLength").toInt());
            theWorld.setInitialPopulationSize(customSettings.value("initialPopulationSize").toInt());
            theWorld.setPollutionRate(customSettings.value("pollutionRate").toInt());
            theWorld.setChildAmount(customSettings.value("childAmount").toInt());

            settings.beginGroup("Breakpoint");
            const QStringList breakKeys = settings.childKeys();
            QHash<QString, QString> breakSettings;
            foreach (const QString &childKey, breakKeys)
            breakSettings.insert(childKey, settings.value(childKey).toString());
            settings.endGroup();

            setAgentBP(breakSettings.value("agentBreakPoint").toInt());
            setRedBP(breakSettings.value("redBreakPoint").toInt());
            setBlueBP(breakSettings.value("blueBreakPoint").toInt());
            setSugarBP(breakSettings.value("blueBreakPoint").toInt());
            setSpiceBP(breakSettings.value("spiceBreakPoint").toInt());

            settings.beginGroup("Timer");
            const QStringList timeKey = settings.childKeys();
            QHash<QString, QString> timerSettings;
            foreach (const QString &childKey, timeKey)
            breakSettings.insert(childKey, settings.value(childKey).toString());
            settings.endGroup();

            setSimulationTimer(settings.value("Timer/simulationTime").toInt());
            qDebug() << getSimulationTimer();

        }

        this->clear();
        start();
    }

    // Setters

    /**
     Runs Sugarscape
     @returns Sugarscape
     @exception void
     */
    void run()
    {
        while(isRunning == true)
        {
            this->clear();
            theWorld.applyRules();
            theGUI.draw();
            this->display();
            if(getRunningType() == 1)
                checkBP();
            QTest::qWait(getSimulationTimer());
            //  theWorld.sanityCeck();


        }
    }

    /**
     Starts Sugarscape
     @returns Sugarscape
     @exception void
     */
    void start()
    {
        isRunning = true;
        run();
    }

    /**
     Runs Sugarscape
     @returns nothing
     @exception void
     */
    void stop()
    {
        isRunning = false;
        run();
        QTest::qWait(99999999);
    }

    /**
     Steps Through Sugarscape
     @returns nothing
     @exception void
     */
    void step()
    {
        this->clear();
        theWorld.applyRules();
        theGUI.draw();
        this->display();
        if(getRunningType() == 1)
            checkBP();
        QTest::qWait(99999999);
    }

    /**
     Resumes Sugarscape after Stop
     @returns Sugarscape
     @exception void
     */
    void resume()
    {
        isRunning = true;
        run();
    }


    // Getters

    /**
     Gets RunningType (Default/Custom)
     @returns runningType
     @exception void
     */
    int getRunningType() { return runningType; }

    /**
     Gets Path to Config File
     @returns filePath
     @exception void
     */
    QString getConfigFilePath() { return filePath; }

    QVector<int> getAC() { return theGUI.getAgentCount(); }
    QVector<int> getRC() { return theGUI.getRedCount(); }
    QVector<int> getBC() { return theGUI.getBlueCount(); }
    QVector<int> getSC() { return theGUI.getSugarCount(); }
    int getST() { return theGUI.getSteps(); }

    void setAgentBP(int n) { agentBreakPoint = n; }
    void setRedBP(int n) { redBreakPoint = n; }
    void setBlueBP(int n) { blueBreakPoint = n; }
    void setSugarBP(int n) { sugarBreakPoint = n; }
    void setSpiceBP(int n) { spiceBreakPoint = n; }

    void messageBox()
    {
        QMessageBox infoBox;
        infoBox.setText("We got to the breakpoint!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }

    void checkBP()
    {
        qDebug() << theGUI.getCurrentAgentCount() << " 1 " << agentBreakPoint;
        qDebug() << theGUI.getCurrentRedCount() << " 2 " << redBreakPoint;
        qDebug() << theGUI.getCurrentBlueCount() << " 3 " << blueBreakPoint;
        qDebug() << theGUI.getCurrentSugarCount() << " 4 " << sugarBreakPoint;
        qDebug() << theGUI.getCurrentSpiceCount() << " 5 " << spiceBreakPoint;
        if(theGUI.getCurrentAgentCount() == agentBreakPoint)
            messageBox();
        if(theGUI.getCurrentRedCount() == redBreakPoint)
            messageBox();
        if(theGUI.getCurrentBlueCount() == blueBreakPoint)
            messageBox();
        if(theGUI.getCurrentSugarCount() == sugarBreakPoint)
            messageBox();
    }

    /**
     Sets the time it takes to refresh Sugarscape, default is 1000ms (1 second)
     @param : simulationTime (n)
     @exception void
     */
    void setSimulationTimer(int n)
    {
        agentRefreshTime = n;
    }

    int getSimulationTimer()
    {
        return agentRefreshTime;
    }

};
