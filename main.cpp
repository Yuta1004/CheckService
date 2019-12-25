#include <fstream>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char* argv[])
{
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
}
