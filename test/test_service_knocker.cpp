#include <cstdint>
#include <iostream>
#include "../service_knocker.hpp"

using std::cout;
using std::endl;

std::string getStatusMsg(int32_t stcode)
{
    if(success(stcode))
        return "200 OK";
    if(failed40x(stcode))
        return "40x Client Error";
    if(failed50x(stcode))
        return "50x Server Error";
    return "Unknown Error";
}

void knock(std::string url)
{
    yn0014::ServiceKnocker sknocker(url);
    sknocker.knock();

    std::string result = getStatusMsg(sknocker.getStatus());
    std::vector<std::string> resp = sknocker.getResp();

    cout << "Status: " << result << endl;
    cout << "Response:" << endl;
    for(auto line : resp)
        cout << line << endl;
    cout << endl;
}

int main()
{
    knock("http://www.yuge.ac.jp/subject/info");
    knock("https://github.com/Yuta1004");
}
