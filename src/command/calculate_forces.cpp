#include "calculate_forces.h"

CALCULATE_FORCES::CALCULATE_FORCES()
{
    numberOfBoxes = 0;
    neighborMap.clear();
}

void CALCULATE_FORCES::doForSystem(SYSTEM_INTERFACE& sysIn)
{
    BOX_GEOMETRY* simBox = sysIn.simulationBox();
    double cutoffRadius = sysIn.getInteractionLengthScale();

    gridSize = floor(simBox->getDimensions().x / cutoffRadius);

    int gridSizeX = floor(simBox->getDimensions().x / cutoffRadius);
    int gridSizeY = floor(simBox->getDimensions().y / cutoffRadius);
    if(gridSizeX < gridSizeY){ //take smaller gridSize
        gridSize = gridSizeX;
    } else{
        gridSize = gridSizeY;
    }
    
    if(neighborMap.size() == 0 && numberOfBoxes == 0){
        initializeContainer();
    }

    initializeParticleIndexLists(sysIn);
    calculateForce(sysIn);

}

void CALCULATE_FORCES::initializeContainer()
{
    int mapIndex;
    numberOfBoxes = gridSize * gridSize;
    neighborMap.resize(4 * numberOfBoxes);  //only takes 4 neighbours into account

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
unsigned int CALCULATE_FORCES::getBoxIndexFromGridIndices(int i, int j)
{
    unsigned int boxIndex = (i + gridSize * gridSize) % gridSize + (j + gridSize * gridSize) % gridSize * gridSize;
    return boxIndex;
}

void CALCULATE_FORCES::initializeParticleIndexLists(SYSTEM_INTERFACE& sysIn)
{
    boxPositions = sysIn.getPositionList();
    simBox = sysIn.simulationBox();

    firstParticleIndexInBox.assign(numberOfBoxes, -1);
    nextParticleIndexInBoxOfParticleIndex.assign(boxPositions.size(), -1);

    for(int i = 0; i < boxPositions.size(); ++i){
        boxIndex = getBoxIndexForParticleIndex(i);

        nextParticleIndexInBoxOfParticleIndex[i] = firstParticleIndexInBox[boxIndex];
        firstParticleIndexInBox[boxIndex] = i;
    }
}

int CALCULATE_FORCES::getBoxIndexForParticleIndex(int i)
{
    int gridIndexX = getGridIndexX(i);
    int gridIndexY = getGridIndexY(i);
    return getBoxIndexFromGridIndices(gridIndexX, gridIndexY);
}

int CALCULATE_FORCES::getGridIndexX(int i)
{
    //+0.5*simBox.dimensions.x converts back to particle positions???
    double gridIndexX = floor((boxPositions[i].x + 0.5 * simBox->getDimensions().x) * gridSize / simBox->getDimensions().x);
    return (int)gridIndexX;
}

int CALCULATE_FORCES::getGridIndexY(int i)
{
    double gridIndexY =floor((boxPositions[i].y + 0.5 * simBox->getDimensions().y) * gridSize / simBox->getDimensions().y);
    return (int)gridIndexY;
}

void CALCULATE_FORCES::calculateForce(SYSTEM_INTERFACE& sysIn)
{
    //Particle-Particle Force: -------------------------------------
    for(boxIndex = 0; boxIndex < numberOfBoxes; ++boxIndex){       // 13 Alle Zellen durchgehen
        int i = firstParticleIndexInBox[boxIndex];           // Startelement waehlen
        while(i >= 0){                    // 14 Ausfuehrung ueber alle Teilchen in der jeweiligen Zelle
            int j = nextParticleIndexInBoxOfParticleIndex[i];     // Das erste Referenzelement aus der selben Zelle waehlen
            while(j >= 0){                  // 15 Auswertung mit den Teilchen in der selben Zelle
                sysIn.calculateInteractionForce(i, j);
                j = nextParticleIndexInBoxOfParticleIndex[j];
            }
            int firstBoxNeighborIndex = 4 * boxIndex;
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

