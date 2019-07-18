#include <QCoreApplication>
#include <QImage>
#include <QCommandLineParser>

#include "edgedetection.h"
#include "splitchannels.h"
#include "blur.h"

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString PATH(argv[1]);

    cout << argv[1] << endl;


    QImage inImage(PATH);
    cout << inImage.format() << endl;
    //inImage = inImage.convertToFormat(QImage::Format_RGB32);

    /*EdgeDetection * edge = new EdgeDetection(1,3,3);
    edge->apply(inImage);
    edge->saveResults(inImage,PATH);

    delete edge;*/

    /*SplitChannels * split = new SplitChannels(1,3,1);
    split->apply(inImage);
    split->saveResults(inImage,PATH);
    delete split;*/

    Blur * blur = new Blur(2,3,1);
    blur->apply(inImage);
    blur->saveResults(inImage,PATH);
    delete blur;

    return EXIT_SUCCESS;
}
