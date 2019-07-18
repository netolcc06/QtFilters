#ifndef BLUR_H
#define BLUR_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class Blur: public BaseFilter{

public:
    Blur(int _radius, int _numberOfInputChannels, int _numberOfOutputImages):
        BaseFilter(_radius, _numberOfInputChannels, _numberOfOutputImages){
        weight = 1;
        neighbors = 1;
    }
};

#endif // BLUR_H
