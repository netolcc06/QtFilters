#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class EdgeDetection: public BaseFilter{

public:
    EdgeDetection(int _radius):
        BaseFilter(_radius){
        weight = (2*radius+1)*(2*radius+1)-1;
        neighbors = -1;
    }

    void setParameters(int _radius, int _weight){
        radius = _radius;
        weight = (2*_radius+1)*(2*_radius+1)-1;
        neighbors = -1;
    }

};

#endif // EDGEDETECTION_H
