//
// Created by mhuels on 5/18/20.
//

#ifndef SHEAREDSLITPOREBD_LAYERS_H
#define SHEAREDSLITPOREBD_LAYERS_H

#include "slit_pore_box.h"
#include "particle.h"

class LAYERS{
private:
    int numberOfLayers;
    double zMin;
    double layerThickness;
    vector<double> layerCenter;
    
public:
    LAYERS();
    LAYERS(const SLIT_PORE_BOX& simBox);
    
    //getter
    int getNumberOfLayers() const;
    double getZMin() const;
    double getLayerThickness() const;
    
    //setter
    void setNumberOfLayers(const SLIT_PORE_BOX& simBox);
    void setZMin(const SLIT_PORE_BOX& simBox);
    
    double calculateLayerThickness();
    vector<double> calculateLayerCenters();
    int tellLayerNumber(const PARTICLE& particle);
};


#endif //SHEAREDSLITPOREBD_LAYERS_H
