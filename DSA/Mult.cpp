#include<iostream>
using namespace std;

int main(){

    unsigned long long int d = 4877543910;

    double a = 0.683;

     double prod= d*a;
    double frct = prod -(unsigned long long int)prod;

    double p = frct*1000;
    cout << (int)p;
}