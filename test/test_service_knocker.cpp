#include <iostream>
#include "../service_knocker.hpp"

using std::cout;
using std::endl;

int main()
{
    yn0014::ServiceKnocker sknocker("http://www.yuge.ac.jp/subject/info");
    sknocker.knock();
}
