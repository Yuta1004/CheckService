#include <string>
#include <vector>
#include <cstring>
#include "mystring.h"

std::vector<std::string> yn0014::mystring::split(std::string src, std::string splitter)
{
    // string -> const char *
    const char *csrc = src.c_str();
    const char *cspl = splitter.c_str();
    size_t csrc_len = src.size();
    size_t cspl_len = splitter.size();

    // 入力検証
    if(csrc_len <= 0 || cspl_len <= 0)
        return std::vector<std::string>(0);

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

