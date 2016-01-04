#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
//для opencv
//#include <cv.h>
//#include <highgui.h>

using namespace std;

#define lld long double

const int W = 1000;
const int H = 500;
const lld K = 0.1; // масштаб

const int MAX_N = 1e5;

const int ITR = 100; // исло итераций
const lld L = 0; // длинна ребра
const lld dd = 0.01; // коэффициент шага
const lld D = 0.999999; // коэффициент затухания шага

struct P
{
    lld x, y;

    P(){}
    P(lld x, lld y):x(x), y(y){}

    void set_rand()
    {
        x = max(L, (lld)1)*((lld)RAND_MAX*RAND_MAX - 2.0*(rand()*RAND_MAX+rand())) / ((lld)RAND_MAX*RAND_MAX);
        y = max(L, (lld)1)*((lld)RAND_MAX*RAND_MAX - 2.0*(rand()*RAND_MAX+rand())) / ((lld)RAND_MAX*RAND_MAX);
    }

    void reset()
    {
        x = y = 0;
    }
};

int n;
lld dcr = D;
// для opencv
//IplImage *img = cvCreateImage(cvSize(W,H),IPL_DEPTH_8U,3);
P point[MAX_N];
P force[MAX_N];
vector <int> g[MAX_N];

lld dist(P a, P b)
{
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

void get_graph()
{
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        static int u, v;
        cin >> u >> v;
        u--; v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; i++) point[i].set_rand();

    // рандом
    /*for (int i = 0; i < n; i++)
    {
        point[i].set_rand();
        for (int j = i+1; j < n; j++)
            if (rand()%20 == 0)
            {
                g[i].push_back(j);
                g[j].push_back(i);
            }
    }*/
}

// для opencv
void draw()
{
    /*cvSetZero(img);

    P cm = P(0,0);
    for (int i = 0; i < n; i++)
    {
        cm.x += point[i].x;
        cm.y += point[i].y;
    }
    cm.x /= n;
    cm.y /= n;

    for (int i = 0; i < n; i++)
    for (int j = 0; j < g[i].size(); j++)
    {
        cvLine(img, cvPoint((point[i].x-cm.x)*K*W/2 + W/2, H/2 - (point[i].y-cm.y)*K*H/2),
                    cvPoint((point[g[i][j]].x-cm.x)*K*W/2 + W/2, H/2 - (point[g[i][j]].y-cm.y)*K*H/2),
                    CV_RGB(0,255,0));
    }
    for (int i = 0; i < n; i++)
        cvCircle(img, cvPoint((point[i].x-cm.x)*K*W/2 + W/2, H/2 - (point[i].y-cm.y)*K*H/2), 3, CV_RGB(0,0,255), -1);

    cvShowImage("img", img);
    if (cvWaitKey(1) == 27) exit(0);*/
}

void update()
{
    for (int i = 0; i < n; i++) force[i].reset();

    for (int i = 0; i < n; i++)
    for (int j = 0; j < g[i].size(); j++)
    {
        lld d = dist(point[i], point[g[i][j]]);
        lld dx = point[g[i][j]].x - point[i].x;
        lld dy = point[g[i][j]].y - point[i].y;

        force[i].x += (d-L) * dx / d;
        force[i].y += (d-L) * dy / d;
    }

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
        if (i == j) continue;

        lld d = dist(point[i], point[j]);
        lld dx = point[j].x - point[i].x;
        lld dy = point[j].y - point[i].y;

        force[i].x -= 1/d/d * dx / d;
        force[i].y -= 1/d/d * dy / d;
    }

    for (int i = 0; i < n; i++)
    {
        point[i].x += force[i].x * dd * dcr;
        point[i].y += force[i].y * dd * dcr;
    }

    dcr *= D;
}

int main()
{
    freopen("5.in", "r", stdin);
    srand(time(NULL));

    get_graph();
    while(1)
    {
        update();
        draw();
    }

    return 0;
}
