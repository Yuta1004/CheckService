#include <cstdint>
#include <iostream>
#include "../service_knocker.hpp"

using std::cout;
using std::endl;

std::string getStatusMsg(int32_t stcode)
{
    if(SUCCESS(stcode))
        return "200 OK";
    if(FAILED40x(stcode))
        return "40x Client Error";
    if(FAILED50x(stcode))
        return "50x Server Error";
    return "Unknown Error";
}

int main()
{
    yn0014::ServiceKnocker sknocker("http://www.yuge.ac.jp/subject/info");
    sknocker.knock();

    std::string result = getStatusMsg(sknocker.getStatus());
    std::vector<std::string> resp = sknocker.getResp();

    cout << "Status: " << result << endl;
    cout << "Response:" << endl;
    for(auto line : resp)
        cout << line << endl;
}
