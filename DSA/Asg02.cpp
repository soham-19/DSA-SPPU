#include<iostream>
#include<math.h>
using namespace std;
typedef unsigned long long int Long;
/*
Consider the telephone book database of N clients. Make use of a hash table implementation to quickly look up a client's telephone number. Make use of two collision handeling techniques and compare them using number of comparisions required to find a set of telephone numbers.
*/

class Info{
    private:
        string name;
        Long phn;
        int weight;

    public:
        Info(string name = "", Long phn = 0) {
            this->name = name;
            this->phn = phn;

            this->weight = 0;
            for(char i : this->name) {
                this->weight += (int)i;
            }
        }
        friend class HashMap;
};

class HashMap{
    private:
        Info *table;
        int r;
        int M;

        bool exceeded(int i) {
            return i >= M;
        }

        int base(Info obj) {
            return obj.weight % M;
        }

        int doubleHash(Info obj) {
            return r - obj.weight % r;
        }



    public:
        int size;
        HashMap(int M){
            this->M = M;
            table = new Info[M];
            r = 37;
            size = 0;
            cout << "HashTable of size " << M << " has been created successfully.\n";
        }

        bool isEmpty(){
            return size == 0;
        }

        void printMap() {
            cout << "--------------------------------\n";
            cout << "index\tname\tphone\n";
            cout << "--------------------------------\n";
            for (int i = 0; i < M; i++){
                cout << i << '\t' << (table[i].name==""?"null":table[i].name) << '\t' << table[i].phn << "\n";
                cout << "--------------------------------\n";
            }
        }

        int hash(Info key) {

            int idx = base(key);
            int index = idx;

            if(table[index].name == "") {
                return index;
            }
            else {
                cout << "hi";
                int i = 1;
                while(table[index].name != "" ){

                    if(i > (M-1)/2){
                        cout << "No room for insertion\n";
                        return -1;
                    }
                    index = idx + i++ * doubleHash(key);
                    if(exceeded(index))
                        index = 0;
                }
                return index;
            }

        }

        void put(Info key) {
            int x = hash(key);
            if(x!= -1){
                table[x] = key;
                cout << "Insertion successfull !\n";
                size++;
            }
        }

        bool containsKey(Info key) {
            return hash(key) != -1;
        }
};

int main(int argc, char const *argv[])
{
        HashMap *hm = new HashMap(0);
        
        int x;
        cout << "   *** HASHMAP ***\n\n";

        while(true) {

            cout << "Select Operatin\n";
            cout << "1. put()\n";
            cout << "2. get()\n";
            cout << "3. containsKey()\n";
            cout << "4. remove()\n";
            cout << "5. print()\n";
            cout << "6. rehash()\n";
            cout << "-1. exit()\n";
            cout << "--> ";
            cin >> x;

            switch(x) {

                case -1:
                    cout << "T E R M I N A T I N G\n";
                    return 0;
                case 1:
                    cout << "Enter name : ";
                    cin >> name;
                    cout << "Enter number : ";
                    cin >> n;
                    hm.put(Info(name, num));
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    hm->printMap();
                    break;
                case 6:
                    cout << "Enter new size ";
                    cin >> n;
                    int currentSize = hm->size;
                    Info[currentSize] arr;
                    for (int i = 0; i < hm->M; i++) {
                        arr[i] = hm.remove()
                    }
                        }
        }
        return 0;
}
