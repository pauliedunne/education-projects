//
//  ViewPort.h
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__ViewPort__
#define __SugarScape__ViewPort__

#include <iostream>
#include <algorithm>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <QtGui>
#include <QVector>
#include <QPainter>

#include "Location.h"
#include "World.h"


/*!  \class  ViewPort
 \brief Window that draws section of simulation space
 
 Draws a section of the grid on the screen. Draws from (startX,startY) to
 (startX+portDimension,startY+portDimension).
 Uses (PixelX,pixelY) pixels
 */

class ViewPort{
private:
 	sf::RenderWindow * window;
	World *theWorld;
	std::pair<int,int> pixelCount;
    std::pair<int,int> startPosition;
    int portDimension;
    int cellSize;
    sf::CircleShape *AgentRepresentations;
  //  QPainter *AgentRepresentations;
    QVector<int>        agentVector;
    QVector<int>        redVector;
    QVector<int>        blueVector;
    QVector<int>        sugarVector;
    int                 totalSteps = 0;

    // Break Point Variables
    int agentBP = 0;
    int redBP = 0;
    int blueBP = 0;
    int sugarBP = 0;
    int spiceBP = 0;
    
public:
    /*!< Constructor */
    ViewPort();
    ~ViewPort();
    void init(sf::RenderWindow *, World *, std::pair<int,int>, std::pair<int,int>,int dim=20);
    /*!< Draw Method */
    bool draw();
    
    /*!< Setters */
    std::pair<int,int>  setStartPositions(std::pair<int,int>);
    int                 setSize(int);
    std::pair<int,int>  setPixels(std::pair<int,int>);
    
    /*!< Getters */
    std::pair<int,int>  getStartPosition();
    std::pair<int,int>  getPixelCount();
    int                 getSize();

    QVector<int> getAgentCount();
    QVector<int> getRedCount();
    QVector<int> getBlueCount();
    QVector<int> getSugarCount();
    int getSteps();
    void setSteps(int steps);

    void setCurrentAgentCount(int n);
    void setCurrentRedCount(int n);
    void setCurrentBlueCount(int n);
    void setCurrentSugarCount(int n);
    void setCurrentSpiceCount(int n);

    int getCurrentAgentCount();
    int getCurrentRedCount();
    int getCurrentBlueCount();
    int getCurrentSugarCount();
    int getCurrentSpiceCount();

};





#endif /* defined(__SugarScape__ViewPort__) */
