#ifndef BASEFILTER_H
#define BASEFILTER_H

#include <QImage>
#include <QString>
#include <iostream>

using namespace std;

class BaseFilter{
public:

    int weight;
    int neighbors;
    int radius;

    BaseFilter(int _radius):radius(_radius){

    }

    bool isMonochromatic(QImage & image){
        int format = image.format();
        if(format == 3 || format == 24 || format == 28)
            return true;
        return false;
    }

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

                //cout << totalWeight << endl;
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

    void saveResults(QImage & image, QString filename, int numberOfOutputImages){
        if(numberOfOutputImages==1){
            image.save(filename+"-filtered.png");
        }
        else if (numberOfOutputImages==3) {
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

    void printFilterParameters(){
        cout << "weight " << weight << endl;
        cout << "radius " << radius << endl;
    }
};

#endif // BASEFILTER_H
