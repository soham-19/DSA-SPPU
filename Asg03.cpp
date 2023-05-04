#include<bits/stdc++.h>
#include "Util/LinkedList/LL.cpp"

using namespace std;

#define N 26
class Node{

    public:
        string key;
        string value;

        Node(string k, string v){
            key = k;
            value = v;
        }
};

class HashMap {

    public:
        List<string> buckets[N];

        HashMap() {
            cout << "Dict-Map created successfully";
        }

        int HashFunction(string key){
            return key[0] - 'a';
        }

        void put(string key, string value){

            int bi = HashFunction(key);
             
        }
                
};

int main(){

    HashMap hm;

    List<int> ll;
    ll.push_back(1);
    ll.print();
    return 0;
}