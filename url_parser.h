#ifndef URLPRSER_H
#define URLPARSER_H

#include <string>

namespace yn0014 {

struct URLParser {

    std::string protocol;
    std::string host;
    std::string docpath;
    URLParser(std::string url);

};

}


#endif