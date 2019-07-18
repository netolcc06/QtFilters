#ifndef BLUR_H
#define BLUR_H

#include <iostream>
#include "basefilter.h"
using namespace std;

class Blur: public BaseFilter{

public:
    Blur(int _radius):
        BaseFilter(_radius){
        weight = 1;
        neighbors = 1;
    }
};

#endif // BLUR_H
