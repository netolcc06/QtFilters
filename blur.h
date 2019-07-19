#ifndef BLUR_H
#define BLUR_H

#include <iostream>
#include "basefilter.h"
using namespace std;

/**
 * @brief Blur A blur filter created by inheriting BaseFilter class.
 * In order to create a new filter, you only need to specify its intrinsic parameters
 * in the setParameters function.
 */
class Blur: public BaseFilter{

public:
    Blur(int _radius):
        BaseFilter(_radius){
        weight = 1;
        neighbors = 1;
    }

    /**
     * @brief setParameters In order to keep the same behavious as the previous implementation,
     * neighbors are set to 1.
     */
    void setParameters(int _radius, int _weight)override{
        radius = _radius;
        weight = _weight;
        neighbors = 1;
    }

};

#endif // BLUR_H
