#include <fstream>
#include <iostream>
#include "service_knocker.hpp"

#define convert_bool_to_ok(cond) ((cond) ? "OK" : "Failed")

using std::cout;
using std::cerr;
using std::endl;

bool knock(std::string url)
{
    yn0014::ServiceKnocker knocker(url);
    knocker.knock();
    return SUCCESS(knocker.getStatus());
}

int main(int argc, char* argv[])
{
    // 引数
    if(argc != 2) {
        cerr << "Usage : ./check_service <urlfile>" << endl;
        exit(1);
    }

    // ifstream初期化
    std::ifstream ifs(argv[1]);
    if(ifs.fail()) {
        cerr << "Failed to open file: [" << argv[1] << "]" << endl;
    }

    // 生存確認
    std::string url;
    while(getline(ifs, url)) {
        bool result = knock(url);
        cout << "- " << url << " : " << convert_bool_to_ok(result) << endl;
    }
}
