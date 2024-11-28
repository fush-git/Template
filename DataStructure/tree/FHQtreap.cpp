constexpr int N = 1e5 + 10;
struct treap{
	struct node{int size, val, rank, ls, rs;}d[N];
	int tot = 0, root = 0, seed = 187230412;
	int rd(){return ((long long)(seed = 222 * seed % 2957242 / 25 * 21 % 287324) * 12424 + 98321) / 97124 * (seed + 2);}
	int newnode(int val){d[++tot].val = val, d[tot].rank = rd(), d[tot].size = 1, d[tot].ls = d[tot].rs = 0;return tot;}
	void getsize(int u){d[u].size = 1 + d[d[u].ls].size + d[d[u].rs].size;}
	void SplitVal(int now, int val, int&L, int&R){
		if(!now)return void(L = R = 0);
		if(d[now].val <= val)L = now, SplitVal(d[now].rs, val, d[now].rs, R);
		else R = now, SplitVal(d[now].ls, val, L, d[now].ls);
		return getsize(now);
	}
	void SplitRank(int now, int k, int&L, int&R){
		if(!now)return void(L = R = 0);
		int size = d[d[now].ls].size;
		if(k <= size)R = now, SplitRank(d[now].ls, k, L, d[R].ls);
		else L = now, SplitRank(d[L].rs, k - size - 1, d[L].rs, R);
		getsize(now);
	}
	int merge(int L, int R){
		if(!L || !R)return L + R;
		if(d[L].rank < d[R].rank)return d[L].rs = merge(d[L].rs, R), getsize(L), L;
		else return d[R].ls = merge(L, d[R].ls), getsize(R), R;
	}
	void insert(int val){int L, R;SplitVal(root, val, L, R), root = merge(merge(L, newnode(val)), R);}
	void del(int val){int L, mid, R;SplitVal(root, val, L, R), SplitVal(L, val - 1, L, mid), mid = merge(d[mid].ls, d[mid].rs), root = merge(merge(L, mid), R);}
	int query_val(int k, int rak){
		while(1){
			if (rak <= d[d[k].ls].size)k = d[k].ls;
			else if (!(rak -= d[d[k].ls].size + 1))return d[k].val;
			else k = d[k].rs;
		}
	}
	int query_rank(int val){int L, R;SplitVal(root, val - 1, L, R);int ans = d[L].size + 1;return root = merge(L, R), ans;} 
	int pre_val(int x){int L, R;SplitVal(root, x - 1, L, R);int ans = query_val(L, d[L].size);return root = merge(L, R), ans;}
	int next_val(int x){int L, R;SplitVal(root, x, L, R); int ans = query_val(R, 1);return root = merge(L, R), ans;}
};