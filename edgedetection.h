#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <iostream>
#include "basefilter.h"
using namespace std;

/**
 * @brief @EdgeDetection An edge detection filter created by inheriting BaseFilter class.
 * In order to create a new filter, you only need to specify its intrinsic parameters
 * in the setParameters function.
 */
class EdgeDetection: public BaseFilter{

public:
    EdgeDetection(int _radius):
        BaseFilter(_radius){
        weight = (2*radius+1)*(2*radius+1)-1;
        neighbors = -1;
    }

    /**
     * @brief setParameters The edge detection filter has -1 in mask pixels others than the central one
     * and weight = (2*_radius+1)*(2*_radius+1)-1 for the central one.
     */
    void setParameters(int _radius, int _weight) override{
        radius = _radius;
        weight = (2*_radius+1)*(2*_radius+1)-1;
        neighbors = -1;
    }

};

#endif // EDGEDETECTION_H
