#ifndef SPLITCHANNELS_H
#define SPLITCHANNELS_H

#include <iostream>
#include "basefilter.h"
using namespace std;

/**
 * @brief SplitChannels A split channels detection filter created by inheriting BaseFilter class.
 * In order to create a new filter, you only need to specify its intrinsic parameters
 * in the setParameters function.
 */
class SplitChannels: public BaseFilter{

public:
    SplitChannels(int _radius):
        BaseFilter(_radius){
        radius = 1;
        weight = 1;
        neighbors = 0;
    }

    /**
     * @brief setParameters Since you only want to split the channels, the parameters for this filter
     * are not intended to change the source image. That said, even if you try to specify
     * wrong values for them, this function keeps them with their original and correct values.
     */
    void setParameters(int _radius, int _weight)override{
        radius = 1;
        weight = 1;
        neighbors = 0;
    }
};

#endif // SPLITCHANNELS_H
