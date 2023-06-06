#include <iostream>
#include<math.h>
using namespace std;
#define M 1000000000

typedef unsigned long long int Long;

int h1(Long phn,int size) {

    int part1 = phn % 1000;
    phn /= 1000;
    int part2 = phn % 1000;
    phn /= 1000;
    int part3 = phn % 1000;
    
    return (part1 + part2 + part3)%size;
}
unsigned int h2(unsigned long long int key, unsigned int hashSize) {
    const double A = 0.6180339887; // Constant A (golden ratio approximation)
    // cout << "A = " << A << endl;
    // cout << "K = " << key << endl;
    // cout << "K*A = " << (key * A )<< endl;
    double fractionalPart = (key * A) - floor(key * A);
    // cout << "Fract = " << fractionalPart << endl;
    unsigned int hash = floor(fractionalPart * hashSize);
    // cout << "Fract*M = " << fractionalPart * hashSize << endl;
    // cout << "Hash = " << hash<<endl;

    return hash%hashSize;
}

int main() {

    std::cout << "Sum of parts: " << h1(8329310531,100) << std::endl;
    std::cout << "Multiplicative Hash Function : " << h2(8329310531,100) << std::endl;

    std::cout << "Sum of parts: " << h1(9766016286,100) << std::endl;
    std::cout << "Multiplicative Hash Function : " << h2(9766016286,100) << std::endl;

    std::cout << "Sum of parts: " << h1(9860011087,100) << std::endl;
    std::cout << "Multiplicative Hash Function : " << h2(9860011087,100) << std::endl;

    std::cout << "Sum of parts: " << h1(9168569933,100) << std::endl;
    std::cout << "Multiplicative Hash Function : " << h2(9168569933,100) << std::endl;

    std::cout << "Sum of parts: " << h1(9168939933,100) << std::endl;
    std::cout << "Multiplicative Hash Function : " << h2(9168939933,100) << std::endl;
    
    return 0;
}
