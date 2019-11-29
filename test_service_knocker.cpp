#include <iostream>
#include "service_knocker.h"

using std::cout;
using std::endl;

int main()
{
    cout << "Create Instance" << endl;
    yn0014::ServiceKnocker sknocker(std::string("google.com"));
}
