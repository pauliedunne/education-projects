//
//  ViewPort.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "ViewPort.h"

/**
 * Constructor
 * @param aWorld :World we want to draw
 * @param pix :number of pixels in window
 * @param start :starting location (upper left corner) of window
 * @param dim :dimensions of window
 * @see ViewPort
 * @exception none
 */
ViewPort::ViewPort()
    {
    }

void ViewPort::init(sf::RenderWindow * theWindow, World * aWorld, std::pair<int,int> pix, std::pair<int,int> start,int dim)

{
    window = theWindow;
    theWorld = aWorld;
    pixelCount = pix;
    startPosition = start;
    portDimension = dim;
    cellSize=pix.second/portDimension;
    int maxRadius=cellSize/2;
    AgentRepresentations = new sf::CircleShape[portDimension*portDimension];
    for (int i=0; i<portDimension*portDimension; ++i) {
            AgentRepresentations[i].setRadius(maxRadius);
            AgentRepresentations[i].setFillColor(sf::Color::Yellow);
            AgentRepresentations[i].setPosition((i/portDimension)*cellSize,(i%portDimension)*cellSize);
            //AgentRepresentations[i].setOrigin(maxRadius, -maxRadius);
    }
}

/**
 * destructor - delete array of shape pointers
 */
ViewPort::~ViewPort() { delete [] AgentRepresentations; }

/*!< Setters */


/**
 * Sets new start position (top left corner) for drawable area of lattice
 * @param newStart
 * @return new starting position
 * @exception none
 */
std::pair<int,int> ViewPort::setStartPositions(std::pair<int,int> newStart)
{
    std::pair<int,int> old=startPosition;
    startPosition=newStart;
    return old;
}

/**
 * Sets size of drawable area
 * @param newDim
 * @return old dimension size
 * @exception none
 */
int ViewPort::setSize(int newDim){
    int old=portDimension;
    portDimension=newDim;
    return old;
    
}

/**
 * Sets num of pixels in screen drawing area
 * @param newPixels
 * @return old pixel count
 * @exception none
 */
std::pair<int,int> ViewPort::setPixels(std::pair<int,int> newPixels)
{
    std::pair<int,int> old=pixelCount;
    pixelCount=newPixels;
    return old;
}

/**
 * Set Sugarscape Steps
 * @return nothing
 * @param int step
 * @exception none
 */
void ViewPort::setSteps(int steps) { totalSteps = steps; }

/**
 * Set Sugarscape Steps
 * @return nothing
 * @param int n
 * @exception none
 */
void ViewPort::setCurrentAgentCount(int n) { agentBP = n; }

/**
 * Set Sugarscape Steps
 * @return nothing
 * @param int n
 * @exception none
 */
void ViewPort::setCurrentRedCount(int n) { redBP = n; }

/**
 * Set Sugarscape Steps
 * @return nothing
 * @param int n
 * @exception none
 */
void ViewPort::setCurrentBlueCount(int n) { blueBP = n; }

/**
 * Set Sugarscape Steps
 * @return nothing
 * @param int n
 * @exception none
 */
void ViewPort::setCurrentSugarCount(int n) { sugarBP = n; }

/**
 * Set Sugarscape Steps
 * @return nothing
 * @param int n
 * @exception none
 */
void ViewPort::setCurrentSpiceCount(int n) { spiceBP = n; }


/*!< Getters */

/**
 * returns start position of lattice we are drawing (top-left corner)
 * @return startPosition
 * @exception none
 */
std::pair<int,int>  ViewPort::getStartPosition()
{
    return startPosition;
}

/**
 * Pixelcount of drawing area
 * @return PixelCount
 * @exception none
 */
std::pair<int,int>  ViewPort::getPixelCount()
{
    return pixelCount;
}

/**
 * returns number of Lattice locations we are drawing
 * @return portDimension
 * @exception none
 */
int                 ViewPort::getSize()
{
    return portDimension;
}


/**
 * Get Agent Count
 * @return agentVector
 * @exception none
 */
QVector<int> ViewPort::getAgentCount() { return agentVector; }

/**
 * Get Red Count
 * @return redVector
 * @exception none
 */
QVector<int> ViewPort::getRedCount() { return redVector; }

/**
 * Get Blue Count
 * @return blueVector
 * @exception none
 */
QVector<int> ViewPort::getBlueCount() { return blueVector; }

/**
 * Get Sugar Count
 * @return agentVector
 * @exception none
 */
QVector<int> ViewPort::getSugarCount() { return sugarVector; }

/**
 * Get Steps Count
 * @return totalSteps
 * @exception none
 */
int ViewPort::getSteps() { return totalSteps; }

/**
 * Gets Current Agent Count for Breakpoints
 * @return agentBP
 * @exception none
 */
int ViewPort::getCurrentAgentCount() { return agentBP; }

/**
 * Gets Current Red Count for Breakpoints
 * @return redBP
 * @exception none
 */
int ViewPort::getCurrentRedCount() { return redBP; }

/**
 * Gets Current Blue Count for Breakpoints
 * @return blueBP
 * @exception none
 */
int ViewPort::getCurrentBlueCount() { return blueBP; }

/**
 * Gets Current Sugar Count for Breakpoints
 * @return sugarBP
 * @exception none
 */
int ViewPort::getCurrentSugarCount() { return sugarBP; }

/**
 * Gets Current Spice Count for Breakpoints
 * @return spiceBP
 * @exception none
 */
int ViewPort::getCurrentSpiceCount() { return spiceBP; }

/*!< Draw Method */
/**
 * Draws lattice grid on screen
 * @return true
 * @exception none
 */
bool ViewPort::draw()
{
    // Local Count
    int agentCount = 0;
    int redCount = 0;
    int blueCount = 0;
    int sugarCount = 0;

    // Display grid
    std::pair<int,int> pos;
    Agent *theAgent = nullptr;

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMono.ttf"))
    {
        // error
    }

    // Draw the current step on Sugarscape
    sf::Text steps;
    steps.setFont(font);
    steps.setString("Steps:" + std::to_string(totalSteps));
    steps.setCharacterSize(12);
    steps.setColor(sf::Color::White);
    window->draw(steps);

    // Draws Agents and Sugar onto the Sugarscape (Lattice)
    for (int i=startPosition.first; i<portDimension; ++i) {
        for (int k=startPosition.second; k<portDimension; ++k) {
            pos={i,k};
            int radius=-1;
            Location *currLocation=theWorld->getLocation(pos);
            if (currLocation->hasAgent()) {
                agentCount++;
                theAgent=theWorld->getLocation(pos)->getAgent();
                radius=theAgent->getSugar();
                if (theAgent->getTribe()==affiliation::blue) {
                    blueCount++;
                    AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Blue);
                }
                else{
                    redCount++;
                    AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Red);
                }

            }
            else{
                radius=theWorld->getLocation(pos)->getSugar();
                AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Green);
                sugarCount++;
            }
            if (radius>cellSize/2) {
                radius=cellSize/2;
            }

            AgentRepresentations[i*portDimension+k].setRadius(radius);
            window->draw(AgentRepresentations[i*portDimension+k]);

        }
    }

    // Data for Graphs
    agentVector.push_back(agentCount);
    redVector.push_back(redCount);
    blueVector.push_back(blueCount);
    sugarVector.push_back(sugarCount);
    totalSteps += 1;

    // Data for Breakpoints
    setCurrentAgentCount(agentCount);
    setCurrentRedCount(redCount);
    setCurrentBlueCount(blueCount);
    setCurrentSugarCount(sugarCount);

//    std::cout << "Painted Count is: " << agentCount <<std::endl;
//    qDebug() << "-------------------------------";
//    qDebug() << "Total Agents: " << agentCount;
//    qDebug() << "Total Red: " << redCount;
//    qDebug() << "Total Blue: " << blueCount;
//    qDebug() << "Total Sugar: " << sugarCount;
//    qDebug() << "Total Steps: " << totalSteps;

    return true; 
}

