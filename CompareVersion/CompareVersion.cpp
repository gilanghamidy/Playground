#include <iostream>

extern "C" int compareVersion(char* version1, char* version2);

int main()
{
    char vers1[] = "1.01.4546",
         vers2[] = "1.001";

    auto res = compareVersion(vers1, vers2);

    std::cout << "Ret: " << res << std::endl;

    return 0;
}