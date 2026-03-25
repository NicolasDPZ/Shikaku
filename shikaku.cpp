#include <iostream>
#include <random>
using namespace std;

int main()
{
    cout << "cuando el shikaku esta en * esta vacio" << endl;
    cout << "que tan grande es tu shikaku?" << endl;
    int shikaku;
    cin >> shikaku;
    cout<< endl;


    for (int i = 0; i < shikaku; i++)
    {
        for (int j = 0; j < shikaku; j++)
        {
            cout << " * ";
        }
        cout << endl;
    }

    
return 0;
}
