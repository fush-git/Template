constexpr int N = 1e5 + 10;
struct treap{
	struct node{int size, val, rank, ch[2];}d[N];
	int tot = 0, root = 0, seed = 187230412;
	int rd(){return ((long long)(seed = 222 * seed % 2957242 / 25 * 21 % 287324) * 12424 + 98321) / 97124 * (seed + 2);}
	int newnode(int val){d[++tot].val = val, d[tot].rank = rd(), d[tot].size = 1, d[tot].ch[0] = d[tot].ch[1] = 0;return tot;}
	void getsize(int u){d[u].size = 1 + d[d[u].ch[0]].size + d[d[u].ch[1]].size;}
	void split(int now, int val, int& L, int& R){
		if(!now)return L = 0, R = 0, void();
		if(d[now].val <= val)L = now, split(d[now].ch[1], val, d[now].ch[1], R);
		else R = now, split(d[now].ch[0], val, L, d[now].ch[0]);
		return getsize(now);
	}
	int merge(int L, int R){
		if(!L || !R)return L + R;
		if(d[L].rank < d[R].rank)return d[L].ch[1] = merge(d[L].ch[1], R), getsize(L), L;
		else return d[R].ch[0] = merge(L, d[R].ch[0]), getsize(R), R;
	}
	void insert(int val){int L, R;split(root, val, L, R), root = merge(merge(L, newnode(val)), R);}
	void del(int val){int L, mid, R;split(root, val, L, R), split(L, val - 1, L, mid), mid = merge(d[mid].ch[0], d[mid].ch[1]), root = merge(merge(L, mid), R);}
	int queryval(int k, int rak){
		while(1){
			if (rak <= d[d[k].ch[0]].size)k = d[k].ch[0];
			else if (!(rak -= d[d[k].ch[0]].size + 1))return d[k].val;
			else k = d[k].ch[1];
		}
	}
	int queryrnk(int val){int L, R;split(root, val - 1, L, R);int ans = d[L].size + 1;return root = merge(L, R), ans;} 
	int pre_val(int x){int L, R;split(root, x - 1, L, R);int ans = queryval(L, d[L].size);return root = merge(L, R), ans;}
	int next_val(int x){int L, R;split(root, x, L, R); int ans = queryval(R, 1);return root = merge(L, R), ans;}
};
