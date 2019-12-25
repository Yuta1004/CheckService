#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>
#include <vector>

namespace yn0014 {

    namespace mystring {

        std::vector<std::string> split(std::string src, std::string splitter);

        std::string replace(std::string src, std::string target, std::string str);

        template <typename...Args>
        std::string format(const std::string &fmt, Args ... args)
        {
            size_t len = snprintf(nullptr, 0, fmt.c_str(), args ...);
            char *tmps = (char*)malloc(len+1);
            sprintf(tmps, fmt.c_str(), args ...);
            std::string retStr(tmps);
            free(tmps);
            return retStr;
        }

    }

}

#endif
