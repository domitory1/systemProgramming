#include <iostream>
#include <array>

using namespace std;

int main()
{
    char a[] = "taBle a*pLe AAe";

    std::cout << "Input string: " << a << std::endl;

    

    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        if (!isdigit(a[i])) {
            if (!ispunct(a[i])){
                if (!isblank(a[i])) {
                    std::cout << a[i] << std::endl;
                    a[i] = tolower
                }
                else {
                    std::cout << a[i] << std::endl;
                    a[i + 1] = toupper(a[i + 1]);
                }
            }
        }
    }

    std::cout << a << std::endl;
    
    return 0;
}

