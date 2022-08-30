#include<iostream>
#include <unordered_map>
#include<list>
#include<vector>
#include<queue>
#include<map>
#include <filesystem>
#include<stack>
#include <deque>
#include <utility>
#include<fstream>
#include <string>
#include<climits>
#include "Graph.h"

using namespace std;
string select;

void addedge(Graph project, string country, string country2, int length, int direction, int num) {
    bool con1 = false;
    bool con2 = false;
    bool con3 = true;
    for (int i = 0; i <= num; i++)
    {
        
        if (project.name[i]._Equal(country))
        {
            con1 = true;
        }
        if (project.name[i]._Equal(country2))
        {
            con2 = true;
        }
    }
    for (int i = 0; i <= num; i++)
    {
        
        for (auto a : project.al[i])
        {
            if (country._Equal(project.name[i]) && country2._Equal(project.name[a.first])) {
                con3 = false;
                break;
            }
        }
    }
    if (con1 == true && con2 == true && con3 == true) {
        if (direction == 1) {
            project.al[project.mp[country]].push_back(make_pair(project.mp[country2], length));
        }
        else {
            project.al[project.mp[country]].push_back(make_pair(project.mp[country2], length));
            project.al[project.mp[country2]].push_back(make_pair(project.mp[country], length));
        }
    }
    else if (con1 == false && con2 == false) {

        cout << "the name of country is wrong \n please enter valied country " << endl;
    }
    else if (con3 == false) {
        cout << "the edge is exist" << endl;
    }
}

int minimumDist(int dist[], bool Dset[],int num) /*A method to find the vertex with minimum distance which is not yet included in Dset*/
{
    int min = INT_MAX, index;                 /*initialize min with the maximum possible value as infinity does not exist */
    for (int v = 0; v < num; v++)
    {
        if (Dset[v] == false && dist[v] <= min)
        {
            min = dist[v];
            index = v;
        }
    }
    return index;
}

void printPath(vector<int> const& prev, map<string, int>mp, int i, int source)
{
    if (i < 0) {
        return;
    }
    printPath(prev,mp, prev[i], source);
    if (i != source) {
        cout << ", ";
    }
    for (auto a : mp)
    {
        if (i == a.second) {
            cout << a.first;
        }
    };
}
// A utility function to print the constructed distance
// array
void dijkstra(vector< pair<int, int>>* graph,map<string,int>mp,string country1,string country2, int vertices) {
    int start = mp[country1];
    int end = mp[country2];
    deque< pair<int, pair<int, int>>> track;
    int count = 0;
    int* dist = new int[vertices];
    bool* visited = new bool[vertices];
    vector<int> parent(vertices, -1);
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;

    }

    dist[start] = 0;
    for (int i = 0; i < vertices - 1; i++) {
        int u = minimumDist(dist, visited,vertices);
        visited[u] = true;


        for (vector<pair<int, int> > ::iterator it = graph[u].begin(); it != graph[u].end(); it++) {
            if (visited[it->first] == false && dist[u] != INT_MAX && dist[it->first] > dist[u] + it->second) {
                // cout << "second loop" << u << endl;
                dist[it->first] = dist[u] + it->second;
                parent[it->first] = u;
            }
        }

    }

    cout << "Path (" << country1 << " —> " << country2 << "): Minimum cost = " << dist[end] << ", Route = ["; printPath(parent,mp, end, start); cout << "]" << endl;



}

void saveinfile(Graph project, int num) {
    project.printgraph2(num);
    int counter = 0;
    string namefile;
    cout << "plese enter name of file : ";
    cin >> namefile;
    int x = namefile.find('.');
    if (x < 0)namefile += ".txt";
    ofstream file;
    file.open(namefile);
    file << num << endl;
    int i = 0;
    
    for (size_t i = 0; i < 50; i++)
    {
        if (project.name[i].empty()) {
            continue;
        }
         file << project.name[i] << " ";
    }
    file << endl;
    for (size_t i = 0; i < 50; i++)
    {
        if (project.name[i].empty()) {
            continue;
        }
        for (auto a : project.al[i])
        {
            file << project.name[i] << " " << project.name[a.first] << " " << a.second << " " << endl;
            counter++;
        }
        counter = 0;
    }
    ifstream filess;
    filess.open("names_of_file.txt");
    vector<string>v;
    string s;
    while (filess >> s)
    {
        v.push_back(s);
    }
    v.push_back(namefile);
    //////////////////////////////////////////////
    ofstream files;
    files.open("names_of_file.txt");
    for (auto a : v) {
        files << a << endl;
    }
}

void usefile(Graph project, int& num) {
    ifstream filess("names_of_file.txt");
    vector<string>v;
    string s;
    while (filess >> s)
    {
        v.push_back(s);
    }
    for (auto a : v) {
        cout << a << endl;
    }
    cout << "plese select file : ";
    cin >> select;
    int x = select.find('.');
    if (x < 0) select += ".txt";
    ifstream newfile(select);
    newfile >> num;

    for (int i = 0; i < num; i++) {
        newfile >> project.name[i];

        project.mp[project.name[i]] = i;
    }
    cout << num << endl;
    /*for (int i = 0; i < num; i++) {
        cout << name[i] << endl;
    }*/

    string n, m;
    int a;
    while (newfile >> n >> m >> a) {
        addedge(project, n, m, a, 1, num);
    }

}

void modified(Graph project , int num) {
    int x = 0;
    while (x != 3 && x != 12)
    {
        cout << endl;
        cout << "1-to delete vertices\n"
            << "2-to delete edges\n"
            << "3-to delete graph\n"
            << "4-to add the adge \n"
            << "5-to add the vertices  \n"
            << "6-to modifiy the length between two city\n"
            << "7-to modifiy the name of the city \n"
            << "8-to print graph \n"
            << "9-to know number of edges\n"
            << "10-to know number of vertics \n"
            << "11-to use algo \n"
            << "12-to save data\n"
            << "13-to exit\n\n";
        cin >> x;
        if (x == 1)
        {                                                        //to delete vertices 
            project.deletevertices(num);
            project.printgraph2(num);
            num--;
            
        }
        else if (x == 2)
        {                                                  //to delete edge
            pair<string, string > c;
            cout << "enter the frist city : ";
            cin >> c.first;
            cout << "enter the second city : ";
            cin >> c.second;
            bool con1 = false;
            bool con2 = false;
            bool con3 = false;
            for (int i = 0; i <= num; i++)
            {
                if (project.name[i]._Equal(c.first))
                {
                    con1 = true;
                }
                if (project.name[i]._Equal(c.second))
                {
                    con2 = true;
                }
            }
            for (int i = 0; i <= num; i++)
            {
                for (auto a : project.al[i])
                {
                    if (c.first._Equal(project.name[i]) && c.second._Equal(project.name[a.first]))
                    {
                        con3 = true;
                        break;
                    }
                }
            }
            if (con1 == true && con2 == true && con3 == true)
            {
                project.deleteedges(project.mp[c.first], project.mp[c.second], num);
                project.printgraph2(num );
            }
            else
            {
                cout << "the name of countries is wrong " << endl;
            }
        }
        else if (x == 3)
        {                                               // to delete graph
            project.deletegraph(num);
        }
        else if (x == 4)
        {                                                // to add edges
            string country1, country2;
            int len, dir;
            cout << "please enter country 1 : ";
            cin >> country1;
            do
            {
                cout << "please enter country 2 : ";
                cin >> country2;
            } while (country2 == country1);
            do
            {
                cout << "please enter the length between two cities : ";
                cin >> len;
            } while (len == 0);
            if (len < 0)
            {
                swap(country2, country1);
            }
            cout << "is the edge have two direction or one : ";
            cin >> dir;
            addedge(project, country1, country2, abs(len), dir, num);
            
            project.printgraph2(num);
        }
        else if (x == 5)
        {                                              //to add the vertices
            num++;
            project.addvertices(num);
            project.printgraph2(num );
        }
        else if (x == 6)                                        //to modifiy the length between two city
        {
            pair<string, string > c;
            cout << "enter the frist city : ";
            cin >> c.first;
            cout << "enter the second city : ";
            cin >> c.second;
            project.modifiylength(c, num);
        }
        else if (x == 7)                                                 // to modifiy the name of city 
        {
            string newname;
            string oldname;
            cout << "please enter the old name : ";
            cin >> oldname;
            cout << "please enter the new name : ";
            cin >> newname;
            project.modifiyname(oldname, newname, num);
            project.printgraph2(num);
        }
        else if (x == 8)                                 //to print graph
        {
        project.printgraph2(num);
        }
        else if (x == 9)                                 //to know number of edges
        {
            cout << "the number of edges = " << project.numofedges(num) << endl;
        }
        else if (x == 10)                                    //to know number of vertics
        {
            cout << "the number of vertices = " << num << endl;
        }
        else if (x == 11)                                    // to use algo 
        {
            string c1, c2;
            cout << "entr country1: ";
            cin >> c1;
            cout << "entr country2: ";
            cin >> c2;
            dijkstra(project.al, project.mp, c1, c2, num);
        }
        else if (x == 12)                      //to save
        {
            saveinfile(project, num);
        }
        else if (x == 13)
        {
            break;
        }
    }
}

int main() {
    Graph project;
    
    int num;
    cout << "plese enter '1' to to use gragh from file or '2' add new gragh  : ";
    int z;
    cin >> z;
    if (z == 1) {
        usefile(project,num);
        for (size_t i = 0; i < num; i++)
        {
            project.mp[project.name[i]] = i;
        }
    }
    else {
        cout << "please enter number of vertices : ";
        cin >> num;
        while (num <= 1)
        {
            cout << "please enter number bigger than 1 ";
            cin >> num;
        }

        cout << "please enter name of vertices : " << endl;
        for (int i = 0; i < num; i++)
        {
            cin >> project.name[i];
        }
        for (int i = 0; i < num; i++)
        {
            project.mp[project.name[i]] = i;
        }
        cout << "please enter edges between vertices and enter '0' to finish " << endl;
        int k = 2;
        while (k != 0) {
            string country1, country2;
            int len, dir;
            cout << "please enter country 1 : ";
            cin >> country1;
            cout << "please enter country 2 : ";
            cin >> country2;
            cout << "please enter the length between two cities : ";
            cin >> len;
            cout << "is the edge have two direction or one : ";
            cin >> dir;
            project.addedge(country1, country2, len, dir, num);
            cout << "the edge added successfully!! " << endl;
            cout << "to add another edge equal '1' and to exit equal '0' : ";
            cin >> k;
        }
    }
    
    project.printgraph2(num);
    modified(project, num);
    for (size_t i = 0; i < 50; i++)
    {
        if (project.name[i].empty()) {
            continue;
        }
        cout << project.name[i] << " ";
    }
    cout << endl;
    project.printgraph2(num);

}
