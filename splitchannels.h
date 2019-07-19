#ifndef SPLITCHANNELS_H
#define SPLITCHANNELS_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class SplitChannels: public BaseFilter{

public:
    SplitChannels(int _radius):
        BaseFilter(_radius){
        radius = 1;
        weight = 1;
        neighbors = 0;
    }

    void setParameters(int _radius, int _weight){
        radius = 1;
        weight = 1;
        neighbors = 0;
    }
};

#endif // SPLITCHANNELS_H
