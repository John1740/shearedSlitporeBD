//
// Created by mhuels on 3/31/20.
//

#include "analysis.h"

CARTESIAN_COORDINATE getMinCoordinate(vector<CARTESIAN_COORDINATE> coordinateList){
    CARTESIAN_COORDINATE minCoordinate;
    for(int i=0; i < coordinateList.size(); i++){
        if(coordinateList[i].x < minCoordinate.x){
            minCoordinate.x = coordinateList[i].x;
        }
        if(coordinateList[i].y < minCoordinate.y){
            minCoordinate.y = coordinateList[i].y;
        }
        if(coordinateList[i].z < minCoordinate.z){
            minCoordinate.z = coordinateList[i].z;
        }
    }
    return minCoordinate;
}
