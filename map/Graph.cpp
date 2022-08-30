#include "Graph.h"
#include<fstream>
#include<climits>



void Graph::addedge(string country, string country2, int length, int direction, int num) {
    bool con1 = false;
    bool con2 = false;
    bool con3 = true;
    for (int i = 0; i < 50; i++)
    {
        if (name[i].empty()) {
            continue;
        }
        if (name[i]._Equal(country))
        {
            con1 = true;
        }
        if (name[i]._Equal(country2))
        {
            con2 = true;
        }
    }
    for (int i = 0; i < 50; i++)
    {
        if (name[i].empty()) {
            continue;
        }
        for (auto a : al[i])
        {
            if (country._Equal(name[i]) && country2._Equal(name[a.first])) {
                con3 = false;
                break;
            }
        }
    }
    if (con1 == true && con2 == true && con3 == true) {
        if (direction == 1) {
            al[mp[country]].push_back(make_pair(mp[country2], length));
        }
        else {
            al[mp[country]].push_back(make_pair(mp[country2], length));
            al[mp[country2]].push_back(make_pair(mp[country], length));
        }
    }
    else if (con1 == false && con2 == false || con1 == false && con2 == true || con1 == true && con2 == false) {

        cout << "the name of country is wrong \n please enter valied country " << endl;
    }
    else if (con3 == false) {
        cout << "the edge is exist" << endl;
    }

}

void Graph::deletegraph(int num) {
    for (int i = 0; i <= num; i++)
    {
        al[i].clear();
    }
}

void Graph::deletevertices( int num) {

    cout << "please enter the verices : ";
    string n;
    cin >> n;

    bool con = false;
    for (int i = 0; i <= num; i++)
    {
        if (name[i] == n) {
            con = true;
        }
    }
    if (con == true)
    {
        int counter = 0, index = 0;
        pair<int, int >* t = new pair<int, int >[counter];
        for (int i = 0; i <= num; i++)
        {
            for (auto a : al[i])
            {
                if (a.first == mp[n]) {
                    t[counter].first = i;
                    t[counter].second = index;
                    counter++;
                }
                if (i == mp[n]) {
                    al[i].clear();
                }
                index++;
            }
            index = 0;
        }
        for (int i = 0; i < counter; i++)
        {
            al[t[i].first].erase(al[t[i].first].begin() + t[i].second);
        }
        for (size_t i = 0; i < num; i++)
        {
            if (mp[name[i]] == mp[n]) {
                name[i].erase();
                mp.erase(name[i]);
                break;
            }
        }

    }
    else
    {
        cout << "the name is invalied !! " << endl;
    }
}

void Graph::deleteedges(int frist, int second, int num) {
    int index = 0, input=0;
    for (int i = 0; i <= num; i++)
    {
        for (auto a : al[i]) {
            if (a.first == second && i == frist)
            {
                input = index;
            }
            index++;
        }
        index = 0;
    }
    al[frist].erase(al[frist].begin() + input);
}

void Graph::addvertices(int num) {
    cout << "please enter the name of vertices : ";
    cin >> name[num];
    mp[name[num]] = num;
    cout << "please enter at least on adge from this vertices : " << endl;
    int v = 2;
    while (v != 0) {
        int dir, len;
        string country2;
        cout << "please enter country 2 : ";
        cin >> country2;
        cout << "please enter the length between two cities : ";
        cin >> len;
        cout << "is the edge have two direction or one : ";
        cin >> dir;
        addedge(name[num], country2, len, dir, num);
        cout << "the edge added " << endl;
        cout << "to add another edge equal '1' and to exit equal '0' : ";
        cin >> v;
    }
}

void Graph::modifiyname(string oldname, string newname,int num) {
    bool con = false;
    bool con2 = false;
    for (int i = 0; i <= num; i++)
    {
        if (name[i] == oldname)
        {
            con = true;
        }
    }
    for (int i = 0; i <= num; i++)
    {
        if (name[i] == newname)
        {
            con2 = true;
        }
    }
    if (con == true && con2 == false)
    {
        int r;
        r = mp[oldname];
        name[r] = newname;
        mp[newname] = r;
    }
    else
    {
        cout << "the name is invalied " << endl;
    }
}

int Graph::numofedges(int num) {
    int seq = 0;
    for (int i = 0; i <= num; i++)
    {
        for (auto a : al[i])
        {
            seq++;
        }
    }
    return seq;
}

void Graph::modifiylength(pair<string, string > c,int num) {
    int len, dir;
    bool con1 = false;
    bool con2 = false;
    bool con3 = true;

    pair<int, int >t;
    
    t.first = mp[c.first];
    t.second =mp[c.second];

    for (int i = 0; i <= num; i++)
    {
        if (name[i]._Equal(c.first))
        {
            con1 = true;
        }
        if (name[i]._Equal(c.second))
        {
            con2 = true;
        }
    }


    for (size_t i = 0; i < num; i++)
    {
        for (auto a :al[i]) {
            if (t.second == i) {
                for (size_t j = 0; j < num; j++)
                {
                    for (auto a : al[j]) {
                        if (t.first == j) {
                            con3 = false;
                        }
                    }
                }
            }
        }
    }

    cout << "please enter the new lentgh : ";
    cin >> len;

    if (con1 == true && con2 == true && con3 == false) {
        deleteedges(mp[c.first], mp[c.second], num);
        deleteedges(mp[c.second], mp[c.first], num);
        addedge(c.first, c.second, len, 2, num);
        // addedge(project, c.second, c.first, len, 1, num);
    }
    else if (con1 == true && con2 == true)
    {
        deleteedges(mp[c.first], mp[c.second], num);
        //deleteedges(project.al, project.mp[c.first], project.mp[c.second], num);
        addedge( c.first, c.second, len, 1, num);
    }
    else
    {
        cout << "the name of countries is wrong " << endl;
    }
    cout << "the edge modified " << endl;
    printgraph2(num);
}

void Graph::printgraph(int num) {
    int counter = 0;
    for (int i = 0; i <= num; i++)
    {
        for (auto a : al[i])
        {
            cout << i << " " << a.first << " " << a.second << " " << endl;
            counter++;
        }
        counter = 0;
    }
}

void Graph::printgraph2(int num) {
    int counter = 0;
    for (int i = 0; i <= num; i++)
    {
        for (auto a : al[i])
        {
            cout << name[i] << " " << name[a.first] << " " << a.second << " " << endl;
            counter++;
        }
        counter = 0;
    }
}



