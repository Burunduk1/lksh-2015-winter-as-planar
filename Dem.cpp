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
bool ink1[N];
bool ink2[N];
bool ink3[N];
int p[N];
int h[N];
vector<int> edge[N];
vector<int> link[N];
vector<pii> edges;
vector<int> cycle;

bool findcc(int u, int p, int t){
	if (u == t){
		return 1;
	}
	for (auto v: edge[u]){
		if (v != p){
			cycle.pb(v);
			if (findcc(v, u, t)) return 1;
			cycle.pob();
		}
	}
	return 0;
}

int get(int u){ 
	return u == p[u] ? u : p[u] = get(p[u]);
}

bool unite(int a, int b){
	a = get(a);
	b = get(b);
	if (a == b) return 0;
	if (h[a] > h[b]){
		p[b] = a;
	}
	else{
		p[a] = b;
		h[b] += (h[a] == h[b]);
	}
	return 1;
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
vector<int> f_ver[5 * N];
vector<int> c_eds[5 * N];
vector<int> c_fac[5 * N];
int c_fac_len[N];
int c_cnt = 0, f_cnt = 0;
int used[3 * N];

void c_edfs(int u){
    used[u] = 1;
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
	if (used[u]) return 0;
	pii &e = edges[u];
	used[u] = 1;
	if (e.F != lv){
		if (blocked[e.F]) {
		    b_path.pb(e.F);
			return 1;
		}
		for (auto v: link[e.F]){
			b_path.pb(e.F);
			if (block_edfs(v, facet, e.F)) return 1;
			b_path.pob();
		}
	}
	else{
	    if (blocked[e.S]) {
		    b_path.pb(e.S);
			return 1;
		}
		for (auto v: link[e.S]){
			b_path.pb(e.S);
			if (block_edfs(v, facet, e.S)) return 1;
			b_path.pob();
		}
	}
	return 0;
}

#define file ""

int main(){
	freopen(file"in", "r", stdin);
	freopen(file"out", "w", stdout);
    int n, qm, m = 0;
    cin >> n >> qm;
    cerr << n << "\n";
    bool flag = 0;
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
       		flag = 1;
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
    	cerr << v << " ";
    cerr << "\n";
    for (auto v: cycle)
    	blocked[v] = 1;
    f_ver[f_cnt++] = cycle;
    f_ver[f_cnt++] = cycle;
    
    memset(used, 0, sizeof(used));
    for (int i = 0; i < m; ++i) {
    	pii &e = edges[i];
    	if (!used[i] && (!blocked[e.F] || !blocked[e.S])){
    		c_fac[c_cnt] = {0, 1};
      		c_fac_len[c_cnt++] = 2;
      		c_edfs(i);       	
    	}
    }

    for (;;) {       
    	///Here we find a component to place
    	int cur_c = -1;
        for (int i = 0; i < c_cnt; ++i)
        	if (c_fac_len[i] < c_fac_len[cur_c]) cur_c = i;
        if (cur_c == -1 || c_fac_len[cur_c] == INF) break;
        if (c_fac_len[cur_c] == 0) {
        	cout << "-1\n";
        	cerr << "C_FAC_LEN = 0\n";
        	return 0;
        }
        c_fac_len[cur_c] = INF;

        ///Here we find a path inside the component
    	int cur_f = c_fac[cur_c][0];
    	int start_e = -1, start_v = -1;            
    	for (int i = 0; i < c_eds[cur_c].size(); ++i) {
    		pii &e = edges[c_eds[cur_c][i]];
    		if (blocked[e.F] || blocked[e.S]) {
    			start_e = i;
    			start_v = (blocked[e.F] ? e.F : e.S);
    			break;
    		}	
    	}
    	assert(start_e != -1 && start_v != -1);
    	memset(used, 0, sizeof(used));
    	b_path = {start_v};
    	block_edfs(start_e, cur_f, start_v);
    	cerr << "ok\n";
    	for (auto v: b_path) {
    		cerr << v << " ";
    		blocked[v] = 1;
    	}
    	cerr << "\n";

    	///Here we divide the component into new components
    	memset(used, 0, sizeof(used));
    	for (int i = 0; i < c_eds[cur_c].size(); ++i) {
    		pii &e = edges[c_eds[cur_c][i]];
    	    if (used[i] || (blocked[e.F] && blocked[e.S])) continue;
    	    c_edfs(i);
    	    c_fac[c_cnt] = {cur_f};
      		c_fac_len[c_cnt++] = 1;
        }

    	///Here we update other components
    	memset(ink1, 0, sizeof(ink1));
    	memset(ink2, 0, sizeof(ink2));    	
    	memset(ink3, 0, sizeof(ink3));    	
    	for (auto v: b_path) ink1[v] = 1;
    	int fk2 = f_cnt++;
    	int fk3 = f_cnt++;
    	int cur_color = 0;
        for (auto i : f_ver[cur_f]) {
    		if (ink1[i]) {
      			if (b_path[0] != i)
      				reverse(b_path.begin(), b_path.end());
      			if (cur_color) f_ver[fk2].insert(f_ver[fk2].end(), b_path.begin(), b_path.end());
      			else f_ver[fk2].insert(f_ver[fk2].end(), b_path.begin(), b_path.end());
      			cur_color ^= 1;
    			continue;
    		}
    		if (cur_color) {
    			f_ver[fk2].pb(i);
    			ink2[i] = 1;
    		}	
    		else {
    			f_ver[fk3].pb(i);
    			ink3[i] = 1;
    		}
    	}
    	ink1[b_path[0]] = false;
    	ink1[b_path.back()] = false;
    	for (int i = 0; i < c_cnt; ++i) {
    		if (c_fac_len[i] == INF) continue;
    		bool flag = false;
    		for (int j = 0; j < c_fac[i].size(); j++){
    		 	if (c_fac[i][j] == cur_f){
    		 	    flag = true;
    		 		c_fac[i].erase(c_fac[i].begin() + j);
    		 		break;
    		 	}
    		}	
    		if (!flag) continue;                                                   
    		bool k1 = 0, k2 = 0, k3 = 0;
    		for (auto id: c_eds[i]){
    			pii &e = edges[id];
    			for (int it = 0; it <= 1; ++it) {
    				int v = e.F;
    				k1 |= ink1[v];
    				k2 |= ink2[v];
    				k3 |= ink3[v];
    				swap(e.F, e.S);
    			}
    		}
			if (k1 && k2 && k3){
				cout << "-1\n";
				return 0;
			}
    		if (k1 && !k2 && !k3) {
    			assert(c_fac[i].size() == 0);
    			c_fac[i].pb(fk2);
    			c_fac[i].pb(fk3);
    			c_fac_len[i] = 2;
    		}      
   			if (k2 && k3) continue;
			if (k2)
				c_fac[i].push_back(fk2);
			else if (k3)
				c_fac[i].push_back(fk3);
			else{
			    c_fac[i].push_back(fk2);
			    c_fac[i].push_back(fk3);
			}      

    	}
    	f_ver[cur_f].clear();
    	c_fac[cur_c].clear();
    	c_eds[cur_c].clear();
    }
    vector<int> ans;
    for (int i = 0; i < f_cnt; i++){
    	if (!f_ver[i].empty()){
    		ans.push_back(i);
    	}
    }
    cout << ans.size() << "\n";
    for (auto v: ans){
    	cout << f_ver[v].size() << " ";
    	for (auto j: f_ver[v]){
    		cout << j << " ";
    	}
    	cout << "\n";
    }
	return 0;
}
