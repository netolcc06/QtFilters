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
    BaseFilter edge = EdgeDetection(4);
    BaseFilter blur = Blur(1);
    BaseFilter split = SplitChannels(1);
    //--edge.apply(inImage);
    //--edge.saveResults(inImage,PATH, 1);

    //map<QString, BaseFilter> filters;
    BankFilter filters;

    filters.registerFilter(string("Edge detection"), &edge);
    filters.registerFilter(string("Blur"), &blur);
    filters.registerFilter(string("RGB Split"), &split);

    filters.listFilters(inImage, monochromatic, PATH);
    //filters[filtername] = f;
    //filters.insert(std::make_pair(filtername, f));

    /*SplitChannels * split = new SplitChannels(1,3,1);
    split->apply(inImage);
    split->saveResults(inImage,PATH);
    delete split;*/

    /*Blur * blur = new Blur(3);
    blur->apply(inImage);
    blur->saveResults(inImage,PATH, 1);
    delete blur;*/

    return EXIT_SUCCESS;
}
