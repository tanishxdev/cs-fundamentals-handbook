#include <bits/stdc++.h>
using namespace std;

// simple function just to find max of 2 number
int findMax(int a, int b){
    return a > b ? a : b;
};

int main()
{
    cout<<findMax(100, 200)<<endl;
    return 0;
}