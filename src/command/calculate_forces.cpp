#include "calculate_forces.h"

CALCULATE_FORCES::CALCULATE_FORCES()
{
    numberOfBoxes = 0;
    neighborMap.clear();
}

void CALCULATE_FORCES::doForSystem ( SYSTEM_INTERFACE& sysIn )
{
    BOX_GEOMETRY* simBox = sysIn.simulationBox();
    double rcIn = sysIn.getInteractionLengthScale();

    gridSize = floor ( simBox->getDimensions().x / rcIn );

    int gridSizex = floor ( simBox->getDimensions().x / rcIn );
    int gridSizey = floor ( simBox->getDimensions().y / rcIn );
    if ( gridSizex < gridSizey ) {
        gridSize = gridSizex;
    } else {
        gridSize = gridSizey;
    }

    
    
    if ( neighborMap.size() == 0 && numberOfBoxes == 0 ) {
        initializeContainer();
    }

    initializeParticleIndexLists ( sysIn );
    calculateForce ( sysIn );

}

void CALCULATE_FORCES::initializeContainer()
{
    int mapIndex;
    numberOfBoxes = gridSize * gridSize;    // Anzahl der Zellen
    neighborMap.resize ( 4 * numberOfBoxes );

    for ( int i = 0; i < gridSize; ++i ) {
        for ( int j = 0; j < gridSize; ++j ) {
            mapIndex = getBoxIndexFromGridIndizies ( i, j ) * 4;

            neighborMap[mapIndex] = getBoxIndexFromGridIndizies ( i + 1, j );

            neighborMap[mapIndex + 1] = getBoxIndexFromGridIndizies ( i + 1, j - 1 );

            neighborMap[mapIndex + 2] = getBoxIndexFromGridIndizies ( i + 1, j + 1 );

            neighborMap[mapIndex + 3] = getBoxIndexFromGridIndizies ( i, j + 1 );

        }
    }
}

unsigned int CALCULATE_FORCES::getBoxIndexFromGridIndizies ( int i, int j )
{
    unsigned int tmpBoxIndex = ( i + gridSize * gridSize ) % gridSize + ( j + gridSize * gridSize ) % gridSize * gridSize;
    return tmpBoxIndex;
}

void CALCULATE_FORCES::initializeParticleIndexLists ( SYSTEM_INTERFACE& sysIn )
{
    boxPositions = sysIn.getPositionList();
    simBox = sysIn.simulationBox();

    firstParticleIndexInBox.assign ( numberOfBoxes, -1 );
    nextParticleIndexInBoxOfParticleIndex.assign ( boxPositions.size(), -1 );

    for ( int i = 0; i < boxPositions.size(); ++i ) {
        boxIndex = getBoxIndexForParticleIndex ( i );

        nextParticleIndexInBoxOfParticleIndex[i] = firstParticleIndexInBox[boxIndex];
        firstParticleIndexInBox[boxIndex] = i;
    }
}

int CALCULATE_FORCES::getBoxIndexForParticleIndex ( int i )
{
    return getBoxIndexFromGridIndizies ( getGridIndexX ( i ), getGridIndexY ( i ) );
}

int CALCULATE_FORCES::getGridIndexX ( int i )
{
    return ( int ) floor ( ( boxPositions[i].x + 0.5 * simBox->getDimensions().x ) * gridSize / simBox->getDimensions().x ) ;
}

int CALCULATE_FORCES::getGridIndexY ( int i )
{
    return ( int ) floor ( ( boxPositions[i].y + 0.5 * simBox->getDimensions().y ) * gridSize / simBox->getDimensions().y );
}

void CALCULATE_FORCES::calculateForce ( SYSTEM_INTERFACE& sysIn )
{
    //Particle-Particle Force: -------------------------------------
    for ( boxIndex = 0; boxIndex < numberOfBoxes; ++boxIndex ) {       // 13 Alle Zellen durchgehen
        int i = firstParticleIndexInBox[boxIndex];           // Startelement waehlen
        while ( i >= 0 ) {                    // 14 Ausfuehrung ueber alle Teilchen in der jeweiligen Zelle
            int j = nextParticleIndexInBoxOfParticleIndex[i];     // Das erste Referenzelement aus der selben Zelle waehlen
            while ( j >= 0 ) {                  // 15 Auswertung mit den Teilchen in der selben Zelle
                sysIn.calculateInteractionForce ( i, j );
                j = nextParticleIndexInBoxOfParticleIndex[j];
            }
            int firstBoxNeighborIndex = 4 * boxIndex;
            for ( int nextNeighbor = 0; nextNeighbor < 4; ++nextNeighbor ) {
                int neighborBoxIndex = neighborMap[firstBoxNeighborIndex + nextNeighbor];
                j = firstParticleIndexInBox[neighborBoxIndex];         // Das erste Referenzelement aus der benachbarten Zelle waehlen
                while ( j >= 0 ) {                   // 17 Auswertung mit den Teilchen in der benachbarten Zelle
                    sysIn.calculateInteractionForce ( i, j );
                    j = nextParticleIndexInBoxOfParticleIndex[j];
                }
            }
            i = nextParticleIndexInBoxOfParticleIndex[i];
        }
    }


// Exernal Force:--------------------------------------------

    for ( int i = 0; i < boxPositions.size(); ++i ) {
        sysIn.calculateExternalForce ( i );
    }
}

