#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include "service_knocker.hpp"
#include "net/util.hpp"

#define convert_bool_to_ok(cond) ((cond) ? "OK" : "Failed")

using std::cout;
using std::cerr;
using std::endl;

int failedCnt = 0;

bool knock(std::string url)
{
    // サービスアクセス
    yn0014::ServiceKnocker knocker(url);
    knocker.knock();

    // リダイレクト確認
    int32_t result = knocker.getStatus();
    if(redirect30x(result)) {
        std::string newURL = yn0014::net::util::getRedirectURL(knocker.getResp());
        cout << "redirect..." << endl;
        cout << "   " << url << " -> " << newURL << endl;
        return knock(newURL);
    }
    return result;
}

void outResult(std::string url, bool result)
{
    cout << "- " << url << " : " << (result ? "OK" : "NG") << endl;
}

void outResultPretty(std::string url, bool result)
{
    if(result) {
        printf("- \033[1m\033[32mOK\033[0m : %s\n", url.c_str());
    } else {
        printf("- \033[1m\033[31mFailed\033[0m : %s\n", url.c_str());
        ++ failedCnt;
    }
}

int main(int argc, char* argv[])
{
    bool pretty = false;

    // オプション
    for(int32_t idx = 0; idx < argc; ++ idx) {
        if(strncmp(argv[idx], "-p", 2) == 0) {
            pretty = true;
            for(int32_t rpidx = idx; rpidx < argc-1; ++ rpidx)
                argv[rpidx] = argv[rpidx+1];
            argv[argc--] = NULL;
        }
    }

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
        if(pretty)
            outResultPretty(url, result);
        else
            outResult(url, result);
    }

    exit(failedCnt > 0);
}
