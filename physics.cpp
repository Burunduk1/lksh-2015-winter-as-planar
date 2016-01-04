#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef double ld;

const ld pi = 2 * acos(0);

const int ITERATION_COUNT = 600;
const ld DEC = 0.9;
const ld FACTOR = 1;
const ld MOVE_DIST = 0.01;
const ld GRAVITY = 3;
const ld TENSION = 3;
const ld NORM_LEN = 3;
const ld DIST = 10000;

struct Point{
    ld x, y;
    explicit Point(ld x1, ld y1)
    {
        x = x1;
        y = y1;
    }
    explicit Point()
    {
        x = 0;
        y = 0;
    }
    ld len()
    {
        return hypotl(x, y);
    }
};

Point randp()
{
    return Point(rand(), rand());
}

Point operator+(Point a, Point b)
{
    return Point(a.x + b.x, a.y + b.y);
}

Point operator-(Point a, Point b)
{
    return Point(a.x - b.x, a.y - b.y);
}

Point operator*(Point a, ld d)
{
    return Point(a.x * d, a.y * d);
}

Point operator/(Point a, ld d)
{
    return Point(a.x / d, a.y / d);
}

ld dist(Point a, Point b)
{
    return hypotl(a.x - b.x, a.y - b.y);
}

Point point_force(Point a, Point b)
{
    Point f;
    f = b - a;
    f = f / f.len();
    f = f * GRAVITY * (1 / (dist(a, b)));
    return f;
}

Point edge_force(Point a, Point b)
{
    Point f;
    f = b - a;
    f = f / f.len();
//    if (dist(a, b) > NORM_LEN)
    f = f * TENSION * (dist(a, b) - NORM_LEN);
//    else
//        f = Point();
    return f;

}

vector<vector<int> > tr;
vector<Point> p;
vector<Point> v;

int main()
{
    srand(time(0));
    freopen("input.txt", "r", stdin);
    freopen("visualizer/july.AS/graph_read.txt", "w", stdout);
    int n, m, i, j, a, b;
    scanf("%i %i", &n, &m);
    p.resize(n);
    tr.resize(n);
    v.resize(n);
    for (i = 0; i < m; i++)
    {
        scanf("%i %i", &a, &b);
        a--;
        b--;
        tr[a].push_back(b);
        tr[b].push_back(a);
    }
    vector<ld> gr(n);
    for (i = 0; i < n; i++)
        gr[i] = i * pi / n;
    random_shuffle(gr.begin(), gr.end());
    for (i = 0; i < n; i++)
    {
        p[i] = Point(DIST * cos(gr[i]), DIST * sin(gr[i]));
//        cout << p[i].x << ' ' << p[i].y << endl;
    }

//    for (i = 0; i < n; i++)
//    {
//        printf("%f %f\n", p[i].x, p[i].y);
//    }
//    ld fctr = FACTOR;
    for (int iter = 0; iter < ITERATION_COUNT; iter++)
    {
//        fctr *= DEC;
        Point cntr = Point(0, 0);
        for (i = 0; i < n; i++)
        {
            Point force = Point();
//            force = force / force.len() * fctr;
            for (j = 0; j < n; j++)
                if (i != j)
                {
                    force = force + point_force(p[i], p[j]);
                }
            for (int v : tr[i])
            {
                force = force + edge_force(p[i], p[v]);
            }
            v[i] = v[i] + (force * MOVE_DIST);
            v[i] = v[i] * DEC;
            p[i] = p[i] + v[i];
        }
        for (i = 0; i < n; i++)
        {
            cntr = cntr + p[i];
        }
        cntr = cntr / n;
        for (i = 0; i < n; i++)
        {
            p[i] = p[i] - cntr;
        }
        for (i = 0; i < n; i++)
        {
            cerr << p[i].x << ' ' << p[i].y << endl;
        }
        cerr << endl;
    }
    for (i = 0; i < n; i++)
    {
        cerr << p[i].x << ' ' << p[i].y << endl;
    }
    cerr << endl;
    ld mx, my, bx, by;
    mx = p[0].x;
    my = p[0].y;
    bx = p[0].x;
    by = p[0].y;
    for (i = 1; i < n; i++)
    {
        mx = min(mx, p[i].x);
        my = min(my, p[i].y);
        bx = max(bx, p[i].x);
        by = max(bx, p[i].y);
    }
    printf("%i\n", n);
    for (i = 0; i < n; i++)
    {
        printf("%f %f\n", ((p[i].x - mx + 2) * 200) / (bx - mx + 2) + 20, ((p[i].y - my + 2) * 200) / (by - my + 2) + 20);
    }
    int mt[n][n];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mt[i][j] = 0;
        }
        for (auto w : tr[i])
            mt[i][w] = 1, mt[w][i] = 1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%i ", mt[i][j]);
        }
        printf("\n");
    }
    return 0;
}
