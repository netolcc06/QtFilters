#ifndef BANKFILTER_H
#define BANKFILTER_H

#include <QString>
#include <QImage>
#include <string>
#include <map>
#include <iostream>
#include <iterator>

#include "basefilter.h"
#include "blur.h"
#include "edgedetection.h"
#include "splitchannels.h"

using namespace std;

class BankFilter{

public:
    BankFilter(){}
    void registerFilter(string _filtername, BaseFilter * _f){
        filters.insert(std::make_pair(_filtername, _f));
    }

    void listFilters(QImage & image, bool monochromatic, QString PATH){
        std::map<string, BaseFilter*>::iterator it = filters.begin();
        std::vector<string> options;
        std::vector<BaseFilter*> fOptions;
        int pos = 0;
        while(it != filters.end()){
            if(!(monochromatic && it->first == "RGB Split")){
                cout<< pos << ". " << it->first << endl;
                pos++;
                options.push_back(it->first);
                fOptions.push_back(it->second);
            }
            it++;
        }

        cout << "Type the selected filter number: ";
        unsigned int filterOpt = 0, radius = 0, weight = 0;
        cin >> filterOpt;
        cout << "Selected Filter: " << options[filterOpt] << endl;
        cout << "Type the " << options[filterOpt] << " radius ";
        cin >> radius;
        cout << "Type the " << options[filterOpt] << " weight ";
        cin >> weight;

        cout << "---------------" << endl;
        cout << "options[filterOpt] = " << options[filterOpt] << endl;
        string key = options[filterOpt];

        fOptions[filterOpt]->setParameters(radius, weight);
        fOptions[filterOpt]->printFilterParameters();
        fOptions[filterOpt]->apply(image);
        int numberOfOutputImages = (options[filterOpt] == "RGB Split")? 3 : 1;
        fOptions[filterOpt]->saveResults(image,PATH,numberOfOutputImages);
    }

    void run(){

    }

private:
    map<string, BaseFilter*> filters;
};

#endif // BANKFILTER_H
