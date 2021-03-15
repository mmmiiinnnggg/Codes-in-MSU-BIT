//Branches and bounds
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
const int INF = 100000; //infinity
const int MAX_N = 30; //maximum of matrix dimension
using namespace std;
int n; //matrix dimension
int cost[MAX_N][MAX_N]; //cost function

//structure Node describes a set of selected cities
struct Node
{
    bool visited[MAX_N]; //visited cities(yet)
    int s; //begin city
    int e; //end city
    int k; //number of passed cities
    int sumv; //length of current route
    int lb;//the objective function, which describes the minimum length of potential full path for the set of cities
    bool operator <(const Node &p)const
    {
        return p.lb < lb; // redefine the priority queue to push out the minimum instead of maximum
    }
};
priority_queue<Node> pq;
int low, up; //the lower and upper bounds
bool dfs_visited[MAX_N];// the list of visited cities serving for the DFS process

//Using greedy algorithm(in general it's DFS) to determine the first upper bound
int dfs(int u, int k, int l)//u - current city, k - target city, l - current length of route
{
    if (k == n) return l + cost[u][1];
    int minlen = INF, p;
    for (int i = 1; i <= n; i++)
    {
        if (!dfs_visited[i] && minlen > cost[u][i])
        {
            minlen = cost[u][i];
            p = i;
        }
    }
    dfs_visited[p] = true;
    return dfs(p, k + 1, l + minlen);
}

void get_up()//get the first upper bound
{
    dfs_visited[1] = true;
    up = dfs(1, 1, 0);
}

void get_low()//get the lower bound
{
    low = 0;
    //the sum of all minimums of each line
    for (int i = 1; i <= n; i++)
    {
        int tmpA[MAX_N];
        for (int j = 1; j <= n; j++)
        {
            tmpA[j] = cost[i][j];
        }
        sort(tmpA + 1, tmpA + 1 + n);//sort the array to pick up the minimum
        low += tmpA[1];
    }
}

//get the value of objective function, which consists of three parts:
//1.minimum FROM the end city and minimum TO the start city
//2.minimum FROM the each left city
//3.minimum TO the each left city
//We can easily prove that this is the minimum length of potential full route for the given set
int get_lb(Node p)
{
    int ret = p.sumv * 2;//The doubled length
    int min1 = INF, min2 = INF;
    //1.
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i] && min1 > cost[i][p.s])
        {
            min1 = cost[i][p.s];
        }
    }
    ret += min1;
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i] && min2 > cost[p.e][i])
        {
            min2 = cost[p.e][i];
        }
    }
    ret += min2;
    //2.3.
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i])
        {
            min1 = min2 = INF;
            for (int j = 1; j <= n; j++)
            {
                if (min1 > cost[i][j])
                    min1 = cost[i][j];
            }
            for (int j = 1; j <= n; j++)
            {
                if (min2 > cost[j][i])
                    min2 = cost[j][i];
            }
            ret += min1 + min2;
        }
    }
    return ret / 2;
}

int solve()
{
    get_up();
    get_low();
    //set up the start Node
    Node start;
    start.s = 1;//start city - 1
    start.e = 1;//end city - 1
    start.k = 1;
    for (int i = 1; i <= n; i++)
    {
        start.visited[i] = false;
    }
    start.visited[1] = true;
    start.sumv = 0;
    start.lb = low;//the first value of objective function - lower bound
    int res = INF;//res - the solution
    pq.push(start);//push the start into queue
    while (pq.size())
    {
        //pick up the minimum of the queue
        Node tmp = pq.top();pq.pop();
        if (tmp.k == n - 1)//if the number of visited cites is n-1
        {
            //find the left point
            int p;
            for (int i = 1; i <= n; i++)
            {
                if (!tmp.visited[i])
                {
                    p = i;
                    break;
                }
            }
            //ans = current length + from end city TO p + FROM p to start city
            int ans = tmp.sumv + cost[p][tmp.s] + cost[tmp.e][p];
            //if ans less than the minimum of all lb( because it's picked up from priority queue)
            //then receive it as solution
            if (ans <= tmp.lb)
            {
                res = min(ans, res);
                break;
            }
            //Else continue to find other solutions, and update upper bound
            else
            {
                up = min(up, ans);
                res = min(res, ans);
                continue;
            }
        }
        //If current visited cities less than n-1, then add new city to the set
        Node next;
        for (int i = 1; i <= n; i++)
        {
            if (!tmp.visited[i])
            {
                next.s = tmp.s;//does not the start city
                next.sumv = tmp.sumv + cost[tmp.e][i];//update current route length
                next.e = i;//update the end city
                next.k = tmp.k + 1;//update the number of visited cities
                for (int j = 1; j <= n; j++) next.visited[j] = tmp.visited[j];//no change for the previous visited cities
                next.visited[i] = true;//add new city to visited list

                next.lb = get_lb(next);//find the lb value for 'next' set
                if (next.lb > up) continue;//if lb greater than upper bound, then don't push into queue
                pq.push(next);//else push into queue
            }
        }
    }
    return res;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> cost[i][j];
            if (i == j)
            {
                cost[i][j] = INF;
            }
        }
    }
    cout << "The optimal route length is "<< solve() << endl;
    return 0;
}

/*The example from lecture:
5
100000 25 40 31 27
5 100000 17 30 25
19 15 100000 6 1
9 50 24 100000 6
22 8 7 10 100000
*/
