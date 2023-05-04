#include<bits/stdc++.h>
using namespace std;

class HashMap {
    public:

    class Node {
        public:
        string key;
        string value;

        Node(string k, string v){
            this->key = k;
            this->value = v;
        }
    };

    list<Node *> buckets[];

    HashMap(){

        this->buckets = new list[26];
        for (int i = 0; i < 26; i++)
            this->buckets[i] = new list;
    }
};

int main() {

    HashMap hm;

}