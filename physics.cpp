#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

typedef double ld;

const int ITERATION_COUNT = 200;
const ld DEC = 0.9;
const ld MOVE_DIST = 0.1;
const ld GRAVITY = -4;
const ld TENSION = 3;
const ld NORM_LEN = 4;

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
    f = f * GRAVITY * (1 / (dist(a, b) * dist(a, b)));
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

int main()
{
    srand(time(0));
    freopen("input.txt", "r", stdin);
    freopen("visualizer/july.AS/graph_read.txt", "w", stdout);
    int n, m, i, j, a, b;
    scanf("%i %i", &n, &m);
    p.resize(n);
    tr.resize(n);
    for (i = 0; i < m; i++)
    {
        scanf("%i %i", &a, &b);
        a--;
        b--;
        tr[a].push_back(b);
        tr[b].push_back(a);
    }
    for (i = 0; i < n; i++)
    {
        p[i] = randp();
//        cout << p[i].x << ' ' << p[i].y << endl;
    }

//    for (i = 0; i < n; i++)
//    {
//        printf("%f %f\n", p[i].x, p[i].y);
//    }
    for (int iter = 0; iter < ITERATION_COUNT; iter++)
    {
        Point cntr = Point(0, 0);
        for (i = 0; i < n; i++)
        {
            Point force = Point();
            for (j = 0; j < n; j++)
                if (i != j)
                {
                    force = force + point_force(p[i], p[j]);
                }
            for (int v : tr[i])
            {
                force = force + edge_force(p[i], p[v]);
            }
            p[i] = p[i] + (force * MOVE_DIST);
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
    ld mx, my;
    mx = p[0].x;
    my = p[0].y;
    for (i = 1; i < n; i++)
    {
        mx = min(mx, p[i].x);
        my = min(my, p[i].y);
    }
    printf("%i\n", n);
    for (i = 0; i < n; i++)
    {
        printf("%f %f\n", (p[i].x - mx + 2) * 20, (p[i].y - my + 2) * 20);
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
