#pragma once
#include <iostream>
#include <map>
#include <vector>
#include<unordered_map>
#include <map>
#include <string>
using namespace std;

class Graph 
{
public:
    //static int num;
    string* name = new string[50];
    vector<pair<int, int>>* al = new vector<pair<int, int>>[50];
    map <string, int > mp;

    void addedge(string country, string country2, int length, int direction, int num);
    void deletegraph(int);
    void deletevertices(int);
    void deleteedges(int,int,int);
    void addvertices(int num);
    void modifiyname(string ,string,int);
    void modifiylength(pair<string, string > ,int);
    int numofedges(int );
    void printgraph(int );
    void printgraph2(int );
    
   


};

