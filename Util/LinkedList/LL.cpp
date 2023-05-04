#include <iostream>
using namespace std;

template <class T>
class ListNode {
    private:
        T data;
        ListNode<T> *next;

    public:
        ListNode(T x){
            data = x;
            next = NULL;
        }

    template <class> friend class List;
};

template <class T>
class List{
    private:
        ListNode<T> *head, *tail;
        int len;

    public:

        List(){
            head = tail = NULL;
            len = 0;
        }

        int size(){
            return len;
        }

        void push_back(T x) {

            ListNode<T> *new_node = new ListNode<T>(x);
            len++;
            if(tail == NULL){
                head = tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = tail->next;
            }
        }

        void push_front(T x) {

            ListNode<T> *new_node = new ListNode<T>(x);
            len++;
            if(head == NULL){
                head = tail = new_node;
            }
            else{
                new_node->next = head;
                head = new_node;
            }
        }

        void pop_back() {

            if(tail==NULL){
                cout << "pop_back() failed \n";
                return;
            }
            else if(head == tail){

                ListNode<T> *temp = tail;
                head = tail = NULL;
                delete temp;
            }

            else {

                ListNode<T> *newTail = head;
                while(newTail->next != tail)
                    newTail = newTail->next;

                tail = newTail;
                tail->next = NULL;
                delete newTail->next;
            }
            len--;
        }

        void pop_front() {

            if(head==NULL){
                cout << "pop_front() failed \n";
                return;
            }
            else if(head == tail){

                ListNode<T> *temp = head;
                head = tail = NULL;
                delete temp;
            }

            else {

                ListNode<T> *temp = head;
                head = head->next;
                delete temp;
            }
            len--;
        }

        void print(){

            ListNode<T> *t = head;
            cout << "LL : ";
            while(t!=NULL){
                cout << t->data << " ";
                t = t->next;
            }
            cout << endl;
        }
};

/*
int main(){

    List ll;

    int x;
    int ch;
    while(true){

        cout << "1-push_back()\n2-push_front()\n3-pop_back()\n4-pop_front()\n\n";
        cout << " ? ";
        cin >> ch;

        switch(ch){

            case 1:
                cout << "-> ";
                cin >> x;
                ll.print();
                ll.push_back(x);
                ll.print();
                break;
            case 2:
                cout << "-> ";
                cin >> x;
                ll.print();
                ll.push_front(x);
                ll.print();
                break;
            case 3:
                ll.print();
                ll.pop_back();
                ll.print();
                break;
            case 4:
                ll.print();
                ll.pop_front();
                ll.print();
                break;
            default:
                exit(0);
        }
    }
}

*/