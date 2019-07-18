#ifndef SPLITCHANNELS_H
#define SPLITCHANNELS_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class SplitChannels: public BaseFilter{

public:
    SplitChannels(int _radius, int _numberOfInputChannels, int _numberOfOutputImages):
        BaseFilter(_radius, _numberOfInputChannels, _numberOfOutputImages){
        radius = 1;
        weight = 1;
        neighbors = 0;
    }
};

#endif // SPLITCHANNELS_H
