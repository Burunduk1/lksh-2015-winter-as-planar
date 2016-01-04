#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#define M_PI		3.14159265358979323846

using namespace std;

const double eps = 1e-7;

const int max_n = 10000, steps = 100;
bool found[max_n];
vector<int> g[max_n];
vector<int> cycle;
const double dist = 20;
double x[max_n], y[max_n];
int gr[max_n][max_n];


int main()
{
    //ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    freopen("graph_read.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m, k, a, b, n1;
    cin >> n >> m;
    cout << n <<endl;
    n1 = n;
    for (int i = 0; i < m ; i++){
        cin >> a >> b;
        //cout << a <<" " << b << endl;
        a--;
        b--;
        gr[a][b] = true;
        gr[b][a] = true;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> k;
    for (int i = 0; i < k; i++){
        cin >> a;
        for (int j = 0; j < a; j++){
            cin >> b;
            b--;
            if (i == 0)
                cycle.push_back(b);
            g[n].push_back(b);
            g[b].push_back(n);
        }
        n++;
    }
    double an = 0;
    for (int i = 0; i < cycle.size(); i++){
        x[cycle[i]] = dist * cos(an);
        y[cycle[i]] = dist * sin(an);
        found[cycle[i]] = true;
        an += 2 * M_PI / cycle.size();
    }
    for (int i = 0; i < n; i++)
        if (!found[i]){
            x[i] = 0;
            y[i] = 0;
        }
    for (int i = 0; i < steps; i++)
        for (int j = 0; j < n; j++)
            if (!found[j]){
                x[j] = 0;
                y[j] = 0;
                for (int k = 0; k < g[j].size(); k++){
                    x[j] += x[g[j][k]];
                    y[j] += y[g[j][k]];
                }
                x[j] /= g[j].size();
                y[j] /= g[j].size();
            }
    cout << fixed << setprecision(3);
    //cout << n1 << endl;
    for (int i = 0; i < n1; i++)
        cout << x[i] + 25 << " " << y[i] + 25 << endl;
    for (int i = 0; i < n1; i++){
        for (int j = 0; j < n1; j++)
            if (gr[i][j])
                cout << "1";
            else
                cout << "0";
        cout << endl;
    }
    return 0;
}
