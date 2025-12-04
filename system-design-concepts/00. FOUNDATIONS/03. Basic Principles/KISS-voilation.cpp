#include <bits/stdc++.h>
using namespace std;

// complex function just to find max of 2 number
int findMax(int a, int b, bool checkEqual = false, bool allowNegative = true){
    if(!allowNegative && a < 0 && b < 0){
        cout << "Negative numbers are not allowed." << endl;
        return 0;
    }
    if(checkEqual && a == b){
        cout << "Both numbers are equal." << endl;
        return 0;
    }
    
    return a > b ? a : b;
};

int main()
{
    cout<<findMax(100, 20)<<endl;
    return 0;
}