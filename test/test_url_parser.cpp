#include <string>
#include <cassert>
#include "../url_parser.h"

int main()
{
    yn0014::URLParser url("https://example.com/path/to/doc");
    assert(url.protocol == "https");
    assert(url.host == "example.com");
    assert(url.docpath == "/path/to/doc");
}
