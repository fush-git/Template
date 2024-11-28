constexpr int N = 1e5 + 10;
struct treap{
	struct node{int size, val, rank, ls, rs;}d[N];
	int tot = 0, root = 0, seed = 187230412;
	int rd(){return ((long long)(seed = 222 * seed % 2957242 / 25 * 21 % 287324) * 12424 + 98321) / 97124 * (seed + 2);}
	int newnode(int val){d[++tot].val = val, d[tot].rank = rd(), d[tot].size = 1, d[tot].ls = d[tot].rs = 0;return tot;}
	void getsize(int u){d[u].size = 1 + d[d[u].ls].size + d[d[u].rs].size;}
	void split(int now, int val, int& L, int& R){
		if(!now)return L = 0, R = 0, void();
		if(d[now].val <= val)L = now, split(d[now].rs, val, d[now].rs, R);
		else R = now, split(d[now].ls, val, L, d[now].ls);
		return getsize(now);
	}
	int merge(int L, int R){
		if(!L || !R)return L + R;
		if(d[L].rank < d[R].rank)return d[L].rs = merge(d[L].rs, R), getsize(L), L;
		else return d[R].ls = merge(L, d[R].ls), getsize(R), R;
	}
	void insert(int val){int L, R;split(root, val, L, R), root = merge(merge(L, newnode(val)), R);}
	void del(int val){int L, mid, R;split(root, val, L, R), split(L, val - 1, L, mid), mid = merge(d[mid].ls, d[mid].rs), root = merge(merge(L, mid), R);}
	int queryval(int k, int rak){
		while(1){
			if (rak <= d[d[k].ls].size)k = d[k].ls;
			else if (!(rak -= d[d[k].ls].size + 1))return d[k].val;
			else k = d[k].rs;
		}
	}
	int queryrnk(int val){int L, R;split(root, val - 1, L, R);int ans = d[L].size + 1;return root = merge(L, R), ans;} 
	int pre_val(int x){int L, R;split(root, x - 1, L, R);int ans = queryval(L, d[L].size);return root = merge(L, R), ans;}
	int next_val(int x){int L, R;split(root, x, L, R); int ans = queryval(R, 1);return root = merge(L, R), ans;}
};