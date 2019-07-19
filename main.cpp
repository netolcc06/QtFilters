#include <QCoreApplication>
#include <QImage>
#include <QCommandLineParser>

#include "edgedetection.h"
#include "splitchannels.h"
#include "blur.h"
#include "bankfilter.h"

#include <iostream>
#include <string>
using namespace std;

#include <map>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString PATH(argv[1]);

    cout << argv[1] << endl;

    QImage inImage(PATH);
    bool monochromatic = isMonochromatic(inImage);

    /*cout << "This is an Image App" << endl;
    while(true){
        cout << "Available filters" << endl;
        cout << "1. Blur"<< endl;
    }*/
    //cout << inImage.format() << endl;
    //inImage = inImage.convertToFormat(QImage::Format_RGB32);

    //EdgeDetection edge(1);
    //edge.apply(inImage);
    //edge.saveResults(inImage,PATH, 1);

    //while(true){
    //    cout <<
    //}
    BaseFilter *edge = new EdgeDetection(4);
    BaseFilter *blur = new Blur(1);
    BaseFilter *split = new SplitChannels(1);
    //--edge.apply(inImage);
    //--edge.saveResults(inImage,PATH, 1);

    //map<QString, BaseFilter> filters;
    BankFilter filters;

    filters.registerFilter(string("Edge detection"), edge);
    filters.registerFilter(string("Blur"), blur);
    filters.registerFilter(string("RGB Split"), split);

    filters.listFilters(inImage, monochromatic, PATH);

    delete edge;
    delete blur;
    delete split;

    return EXIT_SUCCESS;
}
