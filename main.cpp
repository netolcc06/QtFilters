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

    // Need to know whether the image is monochromatic or not
    bool monochromatic = isMonochromatic(inImage);

    // Instantiate filters specifying the radius size
    BaseFilter *edge = new EdgeDetection(4);
    BaseFilter *blur = new Blur(1);
    BaseFilter *split = new SplitChannels(1);

    // Struct created to keep track of filters
    BankFilter filters;

    // Register created filters in order to show them on the input menu
    filters.registerFilter(string("Edge detection"), edge);
    filters.registerFilter(string("Blur"), blur);
    filters.registerFilter(string("RGB Split"), split);

    // Shows the registered filters and applies some chosen filter to the image.
    filters.listFilters(inImage, monochromatic, PATH);

    // Deletes the BaseFilter pointers to avoid memory leak
    delete edge;
    delete blur;
    delete split;

    return EXIT_SUCCESS;
}
