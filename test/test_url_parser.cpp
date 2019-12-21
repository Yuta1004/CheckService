#include <string>
#include <cassert>
#include "../net/util.hpp"

int main()
{
    yn0014::net::util::URLParser url("https://example.com/path/to/doc");
    assert(url.protocol == "https");
    assert(url.host == "example.com");
    assert(url.docpath == "/path/to/doc");
}
