#include <string>
#include <cassert>
#include "../net/util.hpp"

int main()
{
    yn0014::net::util::URLParser url1("https://example.com/path/to/doc");
    assert(url1.protocol == "https");
    assert(url1.host == "example.com");
    assert(url1.docpath == "/path/to/doc");

    yn0014::net::util::URLParser url2("https://example.com/");
    assert(url2.protocol == "https");
    assert(url2.host == "example.com");
    assert(url2.docpath == "/");

    yn0014::net::util::URLParser url3("https://example.com");
    assert(url3.protocol == "https");
    assert(url3.host == "example.com");
    assert(url3.docpath == "/");
}
