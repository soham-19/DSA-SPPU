#include <iostream>
using namespace std;

class ListNode {
    private:
        int data;
        ListNode *next;

    public:
        ListNode(int x){
            data = x;
            next = NULL;
        }

    friend class List;
};

class List{
    private:
        ListNode *head, *tail;
        int len;

    public:

        List(){
            head = tail = NULL;
            len = 0;
        }

        int size(){
            return len;
        }

        void push_back(int x) {

            ListNode *new_node = new ListNode(x);
            len++;
            if(tail == NULL){
                head = tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = tail->next;
            }
        }

        void push_front(int x) {

            ListNode *new_node = new ListNode(x);
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

                ListNode *temp = tail;
                head = tail = NULL;
                delete temp;
            }

            else {

                ListNode *newTail = head;
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

                ListNode *temp = head;
                head = tail = NULL;
                delete temp;
            }

            else {

                ListNode *temp = head;
                head = head->next;
                delete temp;
            }
            len--;
        }

        void print(){

            ListNode *t = head;
            cout << "LL : ";
            while(t!=NULL){
                cout << t->data << " ";
                t = t->next;
            }
            cout << endl;
        }
};


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
