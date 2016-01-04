#include <bits/stdc++.h> 

#define F first
#define S second
#define pb push_back
#define pob pop_back

using namespace std;

typedef pair <int, int> pii;

const int INF = 1e9 + 9;

const int N = 3001;
bool blocked[N];
int p[N];
int h[N];
vector<int> edge[N];
vector<int> link[N];
vector<pii> edges;
vector<int> cycle;

bool findcc(int u, int p, int t){
	if (u == t){
		return true;
	}
	for (auto v: edge[u]){
		if (v != p){
			cycle.pb(v);
			if (findcc(v, u, t)) return true;
			cycle.pob();
		}
	}
	return false;
}

int get(int u){ 
	return u == p[u] ? u : p[u] = get(p[u]);
}

bool unite(int a, int b){
	a = get(a);
	b = get(b);
	if (a == b) return false;
	if (h[a] > h[b]){
		p[b] = a;
	}
	else{
		p[a] = b;
		h[b] += (h[a] == h[b]);
	}
	return true;
}

vector<int> euler_tour;

void get_euler_tour(int u, int p){
	euler_tour.pb(u);
	for (auto v: edge[u]){
		if (v != p){
			get_euler_tour(v, u);
			euler_tour.pb(u);
		}
	}
}

//bool f_ver[N][N];
vector<int> c_eds[N];
vector<int> c_fac[N];
int c_fac_len[N];
int c_cnt = 0, f_cnt = 0;
int used[3 * N];

void c_edfs(int u){
    used[u] = true;
    pii &e = edges[u];
    c_eds[c_cnt - 1].pb(u);
	for (int it = 0; it <= 1; ++it) {
		if (!blocked[e.F]){
			for (auto v: link[e.F]){
				if (!used[v]){
				 	c_edfs(v);         
				}
			}
		}
		swap(e.F, e.S);
	}                  
}            

vector <int> b_path;
bool block_edfs(int u, int facet, int lv) {
	if (used[u]) return false;
	pii &e = edges[u];
	used[u] = true;
	if (e.F != lv){
		if (blocked[e.F]) {
		    b_path.pb(e.F);
			return true;
		}
		for (auto v: link[e.F]){
			b_path.pb(e.F);
			if (block_edfs(v, facet, e.F)) return true;
			b_path.pob();
		}
	}
	else{
	    if (blocked[e.S]) {
		    b_path.pb(e.S);
			return true;
		}
		for (auto v: link[e.S]){
			b_path.pb(e.S);
			if (block_edfs(v, facet, e.S)) return true;
			b_path.pob();
		}
	}
	return false;
}

int main(){
    int n, qm, m = 0;
    cin >> n >> qm;
    bool flag = false;
    for (int i = 0; i < n; i++){
    	p[i] = i;
    }
    set <pii> st_e;
    for (int i = 0; i < qm; i++){
        int a, b;
        cin >> a >> b;
        if (a == b || st_e.find(pii(a, b)) != st_e.end()) continue;
        ++m;
        st_e.insert(pii(a, b));
        a--;
        b--;                                   
       	if (!unite(a, b) && !flag){
       		flag = true;
       		cycle.pb(a);
       		findcc(a, a, b);
       	}
       	link[a].pb(m - 1);
       	link[b].pb(m - 1);
       	edge[a].pb(b);
        edge[b].pb(a);
        edges.pb(make_pair(a, b));
    }
    if (n == 1){
    	cout << "1\n1 1\n";
    	return 0;
    }
    if (m > 3 * n - 6){
    	cout << "-1";
    	cerr << "M > 3 * N - 6\n";
        return 0;
    }
    if (!flag){
        get_euler_tour(0, 0);
        cout << "1\n";
      	cout << euler_tour.size() << " ";
      	for (auto v: euler_tour) cout << v << " ";
      	cout << "\n"; 
    	return 0;
    }
    for (auto v: cycle)
    	blocked[v] = true;
    f_cnt++;
    
    memset(used, 0, sizeof(used));
    for (int i = 0; i < m; ++i) {
    	if (!used[i]){
    		c_fac[c_cnt] = {0, 1};
      		c_fac_len[c_cnt++] = 2;
      		c_edfs(i);       	
    	}
    }

    for (;;) {
    	///Here we find a component to place
    	int cur_c = 0;
        for (int i = 1; i < c_cnt; ++i)
        	if (c_fac_len[i] < c_fac_len[cur_c]) cur_c = i;
        if (c_fac_len[cur_c] == INF) break;
        if (c_fac_len[cur_c] == 0) {
        	cout << "-1\n";
        	cerr << "C_FAC_LEN = 0\n";
        	return 0;
        }
        c_fac_len[cur_c] = INF;

        ///Here we find a path inside the component
    	int cur_f = c_fac[cur_c][0];
    	int start_e = -1, start_e = -1;            
    	for (int i = 0; i < c_eds[cur_c].size(); ++i) {
    		pii &e = c_eds[cur_c][i];
    		if (blocked[e.F] || blocked[e.S]) {
    			start_e = i;
    			start_v = (blocked[e.F] ? e.F : e.S);
    			break;
    		}	
    	}
    	assert(start_e != -1 && start_v != -1);
    	memset(used, 0, sizeof(used));
    	b_path = {start_v}
    	block_edfs(start_e, cur_f, start_v);
    	for (auto v: b_path) blocked[v] = true;
    	
    	///Here we divide the component into new components
    	memset(used, 0, sizeof(used));
    	for (int i = 0; i < c_eds[cur_c].size(); ++i) {
    		pii &e = c_eds[cur_c][i];
    	    if (used[i] || (blocked[e.F] && blocked[e.S])) continue;
    	    c_edfs(i);
    	    c_fac[c_cnt] = {cur_f};
      		c_fac_len[c_cnt++] = 1;
        }

    	///Here we update other components
    	for (int i = 0; i < c_cnt; ++i) {
    		if (c_fac_len[i] == INF) continue;
    		
    	}
    	c_fac[cur_c].clear();
    	c_eds[cur_c].clear();
    }


	return 0;
}
