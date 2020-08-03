#include "slit_pore_box.h"
#include <boost/format.hpp>
#include <fstream>
#include <experimental/filesystem>
namespace fs = experimental::filesystem;
namespace bo = boost;

SLIT_PORE_BOX::SLIT_PORE_BOX(){
    setLengthAndDWall(1., D_WALL);
}

SLIT_PORE_BOX::SLIT_PORE_BOX(REAL_C dimensionsIn){
    setDimensions(dimensionsIn);
}

SLIT_PORE_BOX::SLIT_PORE_BOX(double volume, double dWallIN){
    setVolumeAndDWall(volume, dWallIN);
}

void SLIT_PORE_BOX::setDwall(double dWallIn){
    dimensions.z = dWallIn;
    setVolume();
}

void SLIT_PORE_BOX::setDimensions(REAL_C dimensionsIn){
    dimensions = dimensionsIn;
    setVolume();
}

void SLIT_PORE_BOX::setLengthAndDWall(double lengthIN, double dWallIN){
    dimensions.x = lengthIN;
    dimensions.y = dimensions.x;
    setDwall(dWallIN);
    setVolume();
}

void SLIT_PORE_BOX::setVolumeAndDWall(double volumeIN, double dWallIN){
    volume = volumeIN;
    dimensions.z = dWallIN;
    dimensions.x = sqrt(volume / dimensions.z); //A = V/Z, X=Y=sqrt(A)
    dimensions.y = dimensions.x;
}

double SLIT_PORE_BOX::getVolume() const{
    return volume;
}

void SLIT_PORE_BOX::setVolume(){
    volume = dimensions.x * dimensions.y * dimensions.z;
}

REAL_C SLIT_PORE_BOX::getDimensions() const{
    return dimensions;
}

//Converts coordinates x and y into the scope [-L/2,+L/2] (periodic boundary conditions),
//where L is the dimension dx or dy respectively.
REAL_C SLIT_PORE_BOX::convertToBoxPosition(REAL_C &positionIN){
    REAL_C boxPosition;
    //x  = X*L + r (x=positionIN.x, X to be integer, L=dimension.x, r to be remainder ([0,L])
    //x' = x - round( x / L ) * L  (x'=boxPosition.x)
    //x' = r - round( r / L ) * L  (r/L is element [0,1] and so either rounded to 0 or 1)
    //x' = r   , if r <  L/2       (rounded half away from zero)
    //   = r-L , if r >= L/2
    boxPosition.x = positionIN.x - round(positionIN.x / dimensions.x) * dimensions.x;
    boxPosition.y = positionIN.y - round(positionIN.y / dimensions.y) * dimensions.y;
    boxPosition.z = positionIN.z;

    return boxPosition;
}

REAL_C SLIT_PORE_BOX::getOrigin() const{
    return origin;
}

void SLIT_PORE_BOX::setOrigin(REAL_C origin){
    this->origin = origin;
}

ostream& operator<<(ostream& os, const SLIT_PORE_BOX& simBox){
    const char* fmt = "% 2.5f\t";
    os << "ITEM: BOX BOUNDS xx yy zz\n";
    os << bo::format(fmt) % (simBox.getOrigin().x - simBox.getDimensions().x / 2);
    os << bo::format(fmt) % (simBox.getOrigin().x + simBox.getDimensions().x / 2);
    os << '\n';
    os << bo::format(fmt) % (simBox.getOrigin().y - simBox.getDimensions().y / 2);
    os << bo::format(fmt) % (simBox.getOrigin().y + simBox.getDimensions().y / 2);
    os << '\n';
    os << bo::format(fmt) % (simBox.getOrigin().z - simBox.getDimensions().z / 2);
    os << bo::format(fmt) % (simBox.getOrigin().z + simBox.getDimensions().z / 2);
    os << '\n';
    return os;
}

SLIT_PORE_BOX& SLIT_PORE_BOX::readFromFile(string filename){
    //check for existance
    if(fs::exists(filename) == false){
        cout << filename << " is missing!" << endl;
        exit(0);
    }
    
    ifstream f;
    f.open(filename.c_str());
    double c1, c2;  //containers
    string line;
    bool success = false;
    while(getline(f, line)){
        if(line.find("BOX BOUNDS xx yy zz") != string::npos){
            f >> c1 >> c2;
            dimensions.x = c2 - c1;
            origin.x = (c1 + c2) / 2;
            f >> c1 >> c2;
            dimensions.y = c2 - c1;
            origin.y = (c1 + c2) / 2;
            f >> c1 >> c2;
            dimensions.z = c2 - c1;
            origin.z = (c1 + c2) / 2;
            setVolume();
            success = true;
        }
    }
    f.close();
    if(!success || volume <= 0){
        cout << "Simulation box boundaries within " + filename + " not valid. Please set accordingly with:" << endl;
        cout << "ITEM: BOX BOUNDS xx yy zz\nxMin xMax\nyMin yMax\nzMin zMax" << endl;
        exit(0);
    }
    return *this;
}
