#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include "url_parser.h"

using std::cout;
using std::cerr;
using std::endl;

std::vector<std::string> split(std::string src, std::string splitter);

yn0014::URLParser::URLParser(std::string url)
{
    // URLFormat =  <protocol>://<host>/<docpath>

    // <protocol>
    std::vector<std::string> protocol_host = split(url, "://");
    protocol = protocol_host[0];
    if(protocol.size() == 0) {
        cerr << "Bad URL Format : " << protocol << endl;
        exit(1);
    }

    // <host>
    std::vector<std::string> host_docpath = split(protocol_host[1], "/");
    host = host_docpath[0];

    // <docpah>
    size_t pro_host_len = protocol.size() + host.size() + 3;
    docpath = url.replace(url.begin(), url.begin()+pro_host_len, "");
}


std::vector<std::string> split(std::string src, std::string splitter)
{
    // string -> const char *
    const char *csrc = src.c_str();
    const char *cspl = splitter.c_str();
    size_t csrc_len = src.size();
    size_t cspl_len = splitter.size();

    // split処理に使う
    uint32_t old_idx = 0;
    std::vector<std::string> ret_list;
    char *tmp_str = (char*)malloc(csrc_len+1);

    // ret_listに文字列を登録するラムダ式
    auto add_str = [&](const char *s, uint32_t s_idx, size_t len){
        strncpy(tmp_str, s+s_idx, len);
        tmp_str[len] = '\0';
        ret_list.emplace_back(tmp_str);
    };

    // split処理
    for(uint32_t idx = 0; idx < (uint32_t)(csrc_len-cspl_len); ++ idx) {
        if(strncmp(csrc+idx, cspl, cspl_len) == 0) {
            add_str(csrc, old_idx, idx-old_idx);
            idx += cspl_len;
            old_idx = idx;
        }
    }
    add_str(csrc, old_idx, csrc_len-old_idx);

    // 後処理
    free(tmp_str);
    return ret_list;
}

