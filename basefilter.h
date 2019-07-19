#ifndef BASEFILTER_H
#define BASEFILTER_H

#include <QImage>
#include <QString>
#include <iostream>

using namespace std;

/**
 * @brief isMonochromatic Takes an image as input and returns true if it contains only 1 color channel.
 * Returns false in case the image has more than 1 color channel.
 */
bool isMonochromatic(QImage & image){
    int format = image.format();
    if(format == 3 || format == 24 || format == 28)
        return true;
    return false;
}

/**
 * @brief BaseFilter The BaseFilter follows the specification which defines a filter with a radius and a weight
 * to the central pixel of the mask.
 * In order to generalize the idea, there is a new variable called neighbors. In the original
 * implementation, mask pixels other than the central one had 1 as standard value. With this
 * variable one can create new filters with custom values for the central pixel neighbors.
 * The Edge Detection was created to demonstrate how important is this generalization.
 */
class BaseFilter{
public:

    int weight = 0;
    int neighbors = 0;
    int radius = 0;

    /**
     * Basic constructor: you need only to specify the filter radius.
     * The other variables weight and neighbors should be set according to
     * the filter behaviour you expect. This can be done at their constructors
     * or using the setParameters function (see below).
     */
    BaseFilter(int _radius):radius(_radius){

    }

    // Copy constructor
    BaseFilter(const BaseFilter &rhs){
        this->weight = rhs.weight;
        this->radius = rhs.radius;
        this->neighbors = rhs.neighbors;
    }

    // Assignment implementation
    BaseFilter &operator=(BaseFilter &rhs){
        this->weight = rhs.weight;
        this->radius = rhs.radius;
        this->neighbors = rhs.neighbors;

        return *this;
    }

    // Virtual destructor in order to be inherited.
    virtual ~BaseFilter(){}

    void setRadius(int _radius){
        radius = _radius;
    }

    void setWeight(int _weight){
        weight = _weight;
    }

    /**
     * @brief setParameters Virtual function required to be implemented for the new filters.
     * When you inherit BaseFilter, you create a new filter by specifying custom radius, weights
     * and neighbors for your particular case.
     */
    virtual void setParameters(int _radius, int _weight)=0;

    /**
     * @brief apply Applies the specified filter to the image.
     * Results are shown inplace.
     * Monochromatic and polychromatic cases are treated separately.
     */
    void apply(QImage & image){
        QImage copy(image);

        bool monochromatic = isMonochromatic(image);
        for(int i=0; i<image.height();i++){
            for(int j=0; j<image.width(); j++){
                int sumR = 0, sumG = 0, sumB = 0, gray = 0;
                int totalWeight = 0;
                int validPixels = 0;

                for(int k = i-radius; k <= i+radius; k++){
                    for(int l = j-radius; l <= j+radius; l++){
                        if(k >= 0 && k<image.height() && l >=0 && l<image.width()){
                            int factor = (k==i && l==j)? weight : neighbors;

                            if(monochromatic){
                                gray += copy.pixelIndex(l,k)*factor;
                            }
                            else {
                                QRgb color = copy.pixel(l,k);
                                sumR += qRed(color)*factor;
                                sumG += qGreen(color)*factor;
                                sumB += qBlue(color)*factor;
                            }

                            totalWeight+=factor;
                            validPixels++;
                        }
                    }
                }

                /**
                 * The test totalWeight == 0 is used to prevent divisions by zero.
                 * By doing that, one could implement filter which sum of all weights is equal to zero.
                 * An example of such case is the edge detection filter with radius = 1, weight = 8 and neighbors = -1.
                 */
                if(totalWeight == 0)
                    totalWeight = 1;
                if(monochromatic){
                    image.setPixel(j,i,std::max(0,std::min(gray/totalWeight,255)));
                }
                else{
                    sumR = std::max(0,std::min(sumR/totalWeight,255));
                    sumG = std::max(0,std::min(sumG/totalWeight,255));
                    sumB = std::max(0,std::min(sumB/totalWeight,255));
                    QRgb newColor = qRgb(sumR,sumG,sumB);
                    image.setPixel(j,i,newColor);
                }
            }
        }
   }

    /**
     * @brief saveResults It saves the filter output at the same directory of the input image.
     * @param numberOfOutputImages is necessary because of the Split RGB filter.
     * When this filter is chosen, the output has three images. For all the other cases,
     * the result is a single image.
     */
    void saveResults(QImage & image, QString filename, int numberOfOutputImages){
        if(numberOfOutputImages==1){
            image.save(filename+"-filtered.png");
        }
        else if (numberOfOutputImages==3) {
            // Outputs the color channels in three separate images.
            QImage red(image.size(), image.format()), green(image.size(), image.format()), blue(image.size(), image.format());
            for(int i=0; i<image.height(); i++){
                for(int j = 0; j<image.width(); j++){
                    QRgb color = image.pixel(j,i);
                    red.setPixel(j,i, qRgb(qRed(color),0,0));
                    green.setPixel(j,i, qRgb(0,qGreen(color),0));
                    blue.setPixel(j,i, qRgb(0,0,qBlue(color)));
                }
            }
            red.save(filename+"-RED.png");
            green.save(filename+"-GREEN.png");
            blue.save(filename+"-BLUE.png");
        }
        else{
            cout << "You may choose 1 for a single image result or 3 for splitting channels"<< endl;
            cout << "You cannot split channels if you are dealing with monochromatic inputs" << endl;
        }
    }

    // For debug purposes.
    void printFilterParameters(){
        cout << "weight " << weight << endl;
        cout << "radius " << radius << endl;
    }
};

#endif // BASEFILTER_H
