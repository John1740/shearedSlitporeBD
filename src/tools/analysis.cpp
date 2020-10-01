//
// Created by mhuels on 3/31/20.
//

#include "analysis.h"

REAL_C getMinCoordinate(vector<REAL_C> coordinateList){
    REAL_C minCoordinate;
    for(int i = 0; i < coordinateList.size(); i++){
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
