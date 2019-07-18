#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class EdgeDetection: public BaseFilter{

public:
    EdgeDetection(int _radius):
        BaseFilter(_radius){
        weight = 8;
        neighbors = -1;
    }
};

#endif // EDGEDETECTION_H
