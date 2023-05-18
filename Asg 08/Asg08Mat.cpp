#include<iostream>
using namespace std;
#define M 20

class Graph{

    int V;
    int matrix[M][M];
    string cities[M];

    public:

    Graph(int v){
        this->V = v;
        clearGraph();
        cout << "Graph of " << v << " has been created.\n";
        setCities();
        createGraph();
    }

    void clearGraph(){
        for (int i = 0; i < M;i++){
            for (int j = 0; j < M;j++){
                matrix[i][j] = 0;
            }
        }
    }

    void setCities(){
        for (int i = 0; i < V;i++){
            cout << "Enter name of city number " << i + 1 << " : ";
            cin >> cities[i];
        }
        cout << "Cities stored successfully...\n";
    }

    void printGraph(){
        if(V==0)
            return;

        cout << "Cities are : \n";
        for (int i = 0; i < V;i++){
            cout << i + 1 << " : " << cities[i] << endl;
        }

        cout << "\n   "<<1 << " ";
        for (int i = 1; i < V;i++){
            cout << i + 1 << " ";
        }

        cout << "\n ---------\n";
        for (int i = 0; i < V;i++){
            cout << i + 1 << "| ";
            for (int j = 0; j < V;j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void createGraph(){

        for (int i = 0; i < V;i++){
            for (int j = i+1; i <V-1;j++){
                add(j,i);
            }
        }
    }

    void add(int i, int j) {

        cout << "Is there flight b/w " << cities[j] << " and " << cities[i] << " ? ";

        bool flight;
        cin >> flight;

        if(flight){
            cout << "Enter fuel required : ";
            cin >> matrix[j][i];
            matrix[i][j] = matrix[j][i];
        }
    }

    void addAVertex(){

        if(V==M){
            cout << "Memory full.\nCan't add more airports.\n";
            return;
        }
        V++;

        cout << "Enter name of city number " << V << " : ";
        cin >> cities[V-1];
        cout << "Airport created\n";

        for (int i = 0; i < V-1;i++){
            add(V - 1, i);
        }
    }

    void checkConnectivity(){
        for (int i = 0; i < V;i++){
            int j;
            for (j = 0; j < V;j++){
                if(matrix[i][j] !=0){
                    break;
                }
            }
            if(j==V){
                cout << "Graph is disconnected\n";
                return;
            }
        }
        cout << "Graph is Connected\n";
    }
};

int main(){

    int v;
    cout << "Enter the initial size of Map : ";
    cin >> v;
    v = abs(v);

    bool graphExists = false;

    Graph *g = NULL;

    while(true){

        cout << "       * AirPort System *\n\n";
        cout << "1-create graph\n";
        cout << "2-add new airport\n";
        cout << "3-display\n";
        cout << "4-check connecitivity\n";
        cout << "5-exit\n";

        cout << "Select your option : ";

        int ch;
        cin >> ch;

        switch(ch){
            case 1:
                if(!graphExists){
                    g = new Graph(v);
                    graphExists = true;
                } else{
                    cout << "Graph alredy exists.\n";
                }
                break;

            case 2:
                if(graphExists){
                    g->addAVertex();
                } else {
                    cout << "Graph has not been created yet.\n";
                }
                break;

            case 3:
                if(graphExists) {
                    g->printGraph();
                } else {
                    cout << "Graph has not been created yet.\n";
                }
                break;

            case 4:
                if(graphExists){
                    g->checkConnectivity();
                } else {
                    cout << "Graph has not been created yet.\n";
                }
                break;
            case 5:
                cout << "T E R M I N A T I N G\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}