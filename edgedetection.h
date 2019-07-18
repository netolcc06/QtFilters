#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class EdgeDetection: public BaseFilter{

public:
    EdgeDetection(int _radius, int _numberOfInputChannels, int _numberOfOutputImages):
        BaseFilter(_radius, _numberOfInputChannels, _numberOfOutputImages){
        weight = 8;
        neighbors = -1;
    }
};

#endif // EDGEDETECTION_H
