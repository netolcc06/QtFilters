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

/**
 * @brief The BankFilter class three main purposes:
 * I) To register the custom created filters in order to save them for future computations.
 * II) To present a menu with the available filters and treating the user input.
 * III) Apply the desired filter to the source image and save the results.
 */
class BankFilter{

public:
    BankFilter(){}

    /**
     * @brief registerFilter Registers the filter by inserting it into a map<string, BaseFilter*>.
     * @param _filtername Key of the map.
     * @param _f Filter to be inserted.
     */
    void registerFilter(string _filtername, BaseFilter * _f){
        filters.insert(std::make_pair(_filtername, _f));
    }

    /**
     * @brief listFilters Lists the available filters and treats the input.
     * @param image Input image
     * @param monochromatic Tells whether the input image is monochromatic or not.
     * @param PATH Path to the input image.
     */
    void listFilters(QImage & image, bool monochromatic, QString PATH){
        std::map<string, BaseFilter*>::iterator it = filters.begin();
        std::vector<string> options;
        std::vector<BaseFilter*> fOptions;
        int pos = 0;

        cout << "This is an Image App\n" << endl;
        cout << "Available filters" << endl;

        while(it != filters.end()){
            if(!(monochromatic && it->first == "RGB Split")){
                cout<< pos << ". " << it->first << endl;
                pos++;
                options.push_back(it->first);
                fOptions.push_back(it->second);
            }
            it++;
        }

        cout << "\nType the selected filter number: ";
        unsigned int filterOpt = 0, radius = 0, weight = 0;
        cin >> filterOpt;
        if(filterOpt >= options.size()){
            cout << "You need to choose a valid option" << endl;
            cout << "GOOD BYE BLUE SKY" << endl;
            return;
        }
        cout << "\nSelected Filter: " << options[filterOpt] << endl;
        cout << "Type the " << options[filterOpt] << " radius: ";
        cin >> radius;
        cout << "Type the " << options[filterOpt] << " weight: ";
        cin >> weight;

        fOptions[filterOpt]->setParameters(radius, weight);
        fOptions[filterOpt]->apply(image);
        int numberOfOutputImages = (options[filterOpt] == "RGB Split")? 3 : 1;
        fOptions[filterOpt]->saveResults(image,PATH,numberOfOutputImages);

        cout << "\nImage file processed successfully!" << endl;
    }

private:
    map<string, BaseFilter*> filters;
};

#endif // BANKFILTER_H
