// Implements Minimum Spanning Tree to build roads
// Implements Djikstra's Algorithm for travelling along road network in least possible time

#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;
typedef int num;
typedef struct Junction junction;
typedef struct Road* road;
typedef struct Store store; // for Comparing roads
typedef struct DJ dj;
typedef struct DJPQ djpq;
struct Junction{
    num traffictime = -1;
    road ro = nullptr;
    num visit = 0;
};
struct Road{
    num idone;
    num idtwo;
    num buildtime;
    num traveltime;
    road oner;
};
struct compare{
    bool operator()(const road & rhs, const road & lhs)
    {
        return lhs->buildtime < rhs->buildtime;
    }
};
struct Store{
    num small = -1;
    num big = -1;
};
struct DJ{
    num id = -1;
    num time = INT32_MAX;
    num previd = -1;
};
struct DJPQ{
    num time = INT32_MAX; //pass
    num previd = -1;
    num tprint = INT32_MAX; // reach
};
struct totaltime{
    bool operator()(const dj & a, const dj & b)
    {
        return a.time > b.time;
    }
};
junction j[1000000]; //Initially allocates large number of junctions the limits of the Problem
num v, e, q, s, mimp = 0, m = INT32_MAX;
void addRoad(num x, num y, num w, num z) // adds road to junction.ro pointer
{
    auto *a = new Road;
    a->idone = x; // id one is always the junction to which road is being added
    a->idtwo = y;
    a->buildtime = w;
    a->traveltime = z;
    a->oner = j[x].ro;
    j[x].ro = a;
    auto *b = new Road;
    b->idone = y;
    b->idtwo = x;
    b->buildtime = w;
    b->traveltime = z;
    b->oner = j[y].ro;
    j[y].ro = b;
}
void delRoad(num x, num y)
{
    road trav;
    road temp;
    trav = j[x].ro;
    if(trav->idtwo != y){
        while(trav->oner->idtwo != y)
        {
            trav = trav->oner;
        }
        temp = trav->oner;
        trav->oner = temp->oner;
        free(temp);
    } else {
        temp = trav;
        j[x].ro = temp->oner;
        free(temp);
    }
    trav = j[y].ro;
    if(trav->idtwo != x){
        while(trav->oner->idtwo != x)
        {
            trav = trav->oner;
        }
        temp = trav->oner;
        trav->oner = temp->oner;
        free(temp);
    } else {
        temp = trav;
        j[y].ro = temp->oner;
        free(temp);
    }
}
bool comparetworoads(store a, store b)
{
    if(a.small != b.small)
    {
        return a.small < b.small;
    }
    return a.big < b.big;
}
void printmst(store k[], num sum)
{
    sort(k, k+v-1, comparetworoads);
    int t = 0;
    while(k[t].big == -1)
    {
        t++;

    }
    if(t > 0)
    {
        cout << -1 << endl;
        return;
    }
    cout << v - (1+t) << ' ';
    cout << sum;
    for(int i = 0; i < v-1; i++)
    {
        if(k[i].big != -1){
            cout << ' ' << k[i].small << ' ' << k[i].big;
        }
    }
    cout << endl;
}
void mst()
{
    priority_queue <road , vector<road>, compare> pq;
    road ro = j[m].ro;
    store k[v];
    num sum = 0;
    num n = 0;
    if(!ro)
    {
        cout << -1 << endl;
        return;
    }
    while(ro)
    {
        pq.push(ro);
        ro = ro->oner;
    }
    j[m].visit = mimp;
    while (!pq.empty())
    {
        ro = pq.top();
        pq.pop();
        if(j[ro->idtwo].visit != mimp)
        {
            sum = sum + ro->buildtime;
            if(ro->idone < ro->idtwo)
            {
                k[n].big = ro->idtwo;
                k[n].small = ro->idone;
            } else{
                k[n].small = ro->idtwo;
                k[n].big = ro->idone;
            }
            n++;
            j[ro->idtwo].visit = mimp;
            ro = j[ro->idtwo].ro;
            while(ro)
            {
                pq.push(ro);
                ro = ro->oner;
            }
        }
    }
    printmst(k, sum);
}
bool compareid(dj a, dj b)
{
    return a.id < b.id;
}
num findroadtime(num idone, num idtwo)
{
    road ro = j[idone].ro;
    while(ro->idtwo != idtwo)
    {
        ro = ro->oner;
    }
    return ro->traveltime;
}
num gettime(djpq stor[], num x, num y)
{
    stack <num> g;
    g.push(y);
    num i = y;
    num t = 0;
    while(stor[i].previd != -1)
    {
        g.push(stor[i].previd);
        i = stor[i].previd;
    }
    while(!g.empty())
    {
        int a = g.top();
        g.pop();
        if(g.empty())
        {
            break;
        }
        int b = g.top();
        t = t + findroadtime(a, b);
        if(!t%j[b].traffictime)
        {
            t =t + t%j[b].traffictime;
        }
    }
    return t;
}
void djiprint(num y, djpq stor[], num time, num count)
{
    djpq tempst = stor[y];
    if(tempst.previd != -1)
    {
        count++;
        djiprint(stor[y].previd, stor, time, count);
        cout << ' ' << y ;
    }
    else if(tempst.time != INT32_MAX)
    {
        cout << time << ' ' << count << ' ';
        cout << y;
    }
    else
    {
        cout << -1;
    }
}

void djt(num x, num y)
{
    priority_queue<dj, vector<dj>, totaltime> pq;
    djpq stor[1000000];
    num t = 0;
    num addt = 0; //reach
    num passt = 0; //pass
    road ro = j[x].ro;
    stor[x].time = 0;
    stor[x].tprint = 0;
    dj temppq;
    djpq tempst;
    while(ro)
    {
        temppq.id = ro->idtwo;
        if (!ro->traveltime%j[ro->idtwo].traffictime)
        {
            temppq.time = ro->traveltime;
        } else{
            temppq.time  = ro->traveltime + j[ro->idtwo].traffictime - ro->traveltime%j[ro->idtwo].traffictime;
        }
        temppq.previd = x;
        stor[ro->idtwo].previd = x;
        stor[ro->idtwo].time = temppq.time;
        stor->tprint = ro->traveltime;
        pq.push(temppq);
        ro = ro->oner;
    }
    while (!pq.empty())
    {
        temppq = pq.top();
        pq.pop();
        if(j[temppq.id].visit != mimp)
        {
            j[temppq.id].visit = mimp;
            ro = j[temppq.id].ro;
            t = stor[ro->idone].time;
            while(ro)
            {
                addt = ro->traveltime;
                addt = addt + t;
                if(!addt%j[ro->idtwo].traffictime)
                {
                    passt = addt + (j[ro->idtwo].traffictime-addt%j[ro->idtwo].traffictime);
                }
                else
                {
                    passt = addt;
                }
                if(stor[ro->idtwo].time > passt)
                {
                    stor[ro->idtwo].time = passt;
                    stor[ro->idtwo].tprint = addt;
                    stor[ro->idtwo].previd = ro->idone;
                    temppq.id = ro->idtwo;
                    temppq.time = passt;
                    temppq.previd = ro->idone;
                    pq.push(temppq);
                }
                ro = ro->oner;
            }
        }
    }
    t = gettime(stor, x, y);
    djiprint(y, stor, t, 1);
}

// Main Function

int main() {
    num x, y, w, z;
    cin >> v >> e; // No. of prime junctions, no. of proposed roads
    if(v != 0)
    {
        cin >> x >> y; // Junction ID, Traffic light time
        if(m > x)
            m = x;
        j[x].traffictime = y;
    }
    for (num i = 1; i < v; i++)
    {
        cin >> x >> y;
        if (m > x) // find min x
            m = x;
        j[x].traffictime = y;
    }
    for (num j = 0; j < e; j++)
    {
        cin >> x >> y >> w >> z; // Junction ID1, Junction ID2, build time, traverse time
        addRoad(x, y, w, z);
    }
    cin >> q; // Operation code
    for(int i = 0; i < q; i++)
    {
        cin >> z;
        if (z == 1) // Add Junction
        {
            cin >> x >> y;
            if (m > x)
                m = x;
            j[x].traffictime = y;
            v++;
        } else if (z == 2) // Add road
        {
            cin >> x >> y >> w >> z;
            addRoad(x, y, w, z);
            z = 2;
        } else if (z == 3) // Demolish road
        {
            cin >> x >> y;
            delRoad(x, y);
        } else if (z == 4) // Print Minimum Spanning tree
        {
            mimp++;
            mst();
        } else if(z == 5) // Quick Travel
        {
            cin >> x >> y;
            mimp++;
            djt( x, y);
            cout<<endl;
        }
    }
}