#include "calculate_forces.h"

CALCULATE_FORCES::CALCULATE_FORCES(){
    numberOfBoxes = 0;
    neighborMap.clear();
}

void CALCULATE_FORCES::doForSystem(SYSTEM_INTERFACE& sysIn){
    BOX_GEOMETRY* simBox = sysIn.simulationBox();
    double cutoffRadius = sysIn.getInteractionLengthScale();

//    gridSize = floor(simBox->getDimensions().x / cutoffRadius);

    int gridSizeX = floor(simBox->getDimensions().x / cutoffRadius);
    int gridSizeY = floor(simBox->getDimensions().y / cutoffRadius);
    if(gridSizeX < gridSizeY){ //take smaller gridSize
        gridSize = gridSizeX;
    }
    else{
        gridSize = gridSizeY;
    }

    if(neighborMap.size() == 0 && numberOfBoxes == 0){
        initializeContainer();
    }

    initializeParticleIndexLists(sysIn);
    calculateForce(sysIn);
}

//Initialize numberOfBoxes (based on cutoff radius) and neighborMap.
//Each box (B) has eight neighbors (in 2D), four on one side (type A) and four on the other (type C):
//   2 | C   A   A
//   1 | C   B   A
//   0 | C   C   A
// _______________
// j/i | 0   1   2
//Here, neighbor relationships are treated one-way-directional, meaning that if box A is a neighbor of box B,
//box B is not a neighbor of box A. This way, all neighbor relationships are covered:
//All boxes of type A are neighbors of box B and box B is a neighbor of all boxes of type C.
void CALCULATE_FORCES::initializeContainer(){
    int mapIndex;
    numberOfBoxes = gridSize * gridSize;
    neighborMap.resize(4 * numberOfBoxes);

    for(int i = 0; i < gridSize; ++i){
        for(int j = 0; j < gridSize; ++j){
            mapIndex = getBoxIndexFromGridIndices(i, j) * 4;

            neighborMap[mapIndex] = getBoxIndexFromGridIndices(i + 1, j);

            neighborMap[mapIndex + 1] = getBoxIndexFromGridIndices(i + 1, j - 1);

            neighborMap[mapIndex + 2] = getBoxIndexFromGridIndices(i + 1, j + 1);

            neighborMap[mapIndex + 3] = getBoxIndexFromGridIndices(i, j + 1);
        }
    }
}

//Converts grid indices (i,j) into box index for a quadratic grid (i_max = j_max =: gridSize) in a zig-zag shape.
//For example (4x4 grid):
//   3 | 12  13  14  15
//   2 |  8   9  10  11
//   1 |  4   5   6   7
//   0 |  0   1   2   3
//_____________________
// j/i |  0   1   2   3
//
//Negative indices up to -gridSize^2 are allowed (i=j=-16 in the example).
unsigned int CALCULATE_FORCES::getBoxIndexFromGridIndices(int i, int j){
    unsigned int boxIndex = (i + gridSize * gridSize) % gridSize + (j + gridSize * gridSize) % gridSize * gridSize;
    return boxIndex;
}

//Initialize index lists firstParticleIndexInBox and nextParticleIndexInBoxOfParticleIndex.
//The last called particle per box during initialization will be the first particle in that box.
//This particle will point to the next particle via nextParticleIndexInBoxOfParticleIndex and so on.
//The last particle in each box will point to nothing (particleIndex = -1).
void CALCULATE_FORCES::initializeParticleIndexLists(SYSTEM_INTERFACE& sysIn){
    boxPositions = sysIn.getPositionList();
    simBox = sysIn.simulationBox();

    //reset both lists
    firstParticleIndexInBox.assign(numberOfBoxes, -1);
    nextParticleIndexInBoxOfParticleIndex.assign(boxPositions.size(), -1);

    for(int particleIndex = 0; particleIndex < boxPositions.size(); ++particleIndex){
        boxIndex = getBoxIndexForParticleIndex(particleIndex);

        //make current 1st particle to my next particle
        nextParticleIndexInBoxOfParticleIndex[particleIndex] = firstParticleIndexInBox[boxIndex];
        //make me new 1st particle in my box
        firstParticleIndexInBox[boxIndex] = particleIndex;
    }
}

int CALCULATE_FORCES::getBoxIndexForParticleIndex(int particleIndex){
    int gridIndexX = getGridIndexXForParticleIndex(particleIndex);
    int gridIndexY = getGridIndexYForParticleIndex(particleIndex);
    return getBoxIndexFromGridIndices(gridIndexX, gridIndexY);
}

int CALCULATE_FORCES::getGridIndexXForParticleIndex(int particleIndex){
    //+0.5*simBox.dimensions.x converts back to particle positions???
    double scaledX = boxPositions[particleIndex].x / simBox->getDimensions().x * gridSize;
    double offset = 0.5 * gridSize;
    int gridIndexX = (int)floor(scaledX + offset);
    return gridIndexX;
}

int CALCULATE_FORCES::getGridIndexYForParticleIndex(int particleIndex){
    double scaledY = boxPositions[particleIndex].y / simBox->getDimensions().y * gridSize;
    double offset = 0.5 * gridSize;
    int gridIndexY = (int)floor(scaledY + offset);
    return gridIndexY;
}

void CALCULATE_FORCES::calculateForce(SYSTEM_INTERFACE& sysIn){
    //Particle-Particle Force: -------------------------------------
    for(boxIndex = 0; boxIndex < numberOfBoxes; ++boxIndex){       // 13 Alle Zellen durchgehen
        int i = firstParticleIndexInBox[boxIndex];           // Startelement waehlen
        while(i >= 0){                    // 14 Ausfuehrung ueber alle Teilchen in der jeweiligen Zelle
            int j = nextParticleIndexInBoxOfParticleIndex[i];     // Das erste Referenzelement aus der selben Zelle waehlen
            while(j >= 0){                  // 15 Auswertung mit den Teilchen in der selben Zelle
                sysIn.calculateInteractionForce(i, j);
                j = nextParticleIndexInBoxOfParticleIndex[j];
            }
            int firstBoxNeighborIndex = 4 * boxIndex;   //create conversion functions boxIndex <-> neighborIndex
            for(int nextNeighbor = 0; nextNeighbor < 4; ++nextNeighbor){
                int neighborBoxIndex = neighborMap[firstBoxNeighborIndex + nextNeighbor];
                j = firstParticleIndexInBox[neighborBoxIndex];         // Das erste Referenzelement aus der benachbarten Zelle waehlen
                while(j >= 0){                   // 17 Auswertung mit den Teilchen in der benachbarten Zelle
                    sysIn.calculateInteractionForce(i, j);
                    j = nextParticleIndexInBoxOfParticleIndex[j];
                }
            }
            i = nextParticleIndexInBoxOfParticleIndex[i];
        }
    }

    // Exernal Force:--------------------------------------------

    for(int i = 0; i < boxPositions.size(); ++i){
        sysIn.calculateExternalForce(i);
    }
}

