constexpr int N = 5000, p = 1e9 + 7;
int n, m;
#define A long long
//一维
struct BIT{//单点修改，区间查询。
	A w[N];
	#define lowbit(x) ((x) & (-(x)))
	void modify(int pos,A v){
		for(int i=pos;i<=n;i+=lowbit(i))w[i]+=v;
	}
	int query(int l, int r){
		A ans=0;l--;
		while(r > l)ans += w[r], r -= lowbit(r);
        while(l > r)ans -= w[l], l -= lowbit(l);
        return ans;
	}
    #undef lowbit
};
struct BIT{//区间修改，单点查询。
	A w[N];
	#define lowbit(x) ((x) & (-(x)))
	void modify(int pos,A v){for(int i=pos;i<=n;i+=lowbit(i))w[i]+=v;}
    void add(int l, int r, A v){modify(l, v), modify(r + 1, -v);}
	int query(int x){
		A ans=0;
        while(x)ans += w[x], x -= lowbit(x);
        return ans;
	}
    #undef lowbit
};
struct BIT{//区间修改区间查询
    #define lowbit(x) ((x)&(-(x)))
    struct BIT1 {
        A w[N];
        void modify(int pos,A v){for(;pos<=n;pos+=lowbit(pos))w[pos]+=v;}//修改
        A query(int x){A ans=0;while(x)ans+=w[x],x-=lowbit(x);return ans;}//查询
    }t1, t2;
	A query(int l, int r){return (r+1)*t1.query(r)-l*t1.query(l-1)-(t2.query(r)-t2.query(l-1));}//区间查询
	void modify(int pos, A v){t1.modify(pos, v), t2.modify(pos, pos * v);}//单点修改
	void add(int l,int r,A v){t1.modify(l,v),t2.modify(l,v*l),t1.modify(r+1,-v),t2.modify(r+1,-v*(r+1));}//区间修改
    #undef lowbit
};
//二维
struct BIT{//单点修改，区间查询
    #define lowbit(x) ((x) & (-(x)))
    A w[N][N];
    void add(int x, int y, A v) {for(;x<=n;x+=lowbit(x))for(int j=y;j<=m;j+=lowbit(j))w[x][j]+=v;}//单点修改
    A sum(int x, int y) {//单点询问(前缀和)
        A res=0;
        for(;x;x-=lowbit(x))for (int j=y;j;j-=lowbit(j))res+=w[x][j];
        return res;
    }
    A ask(int x1,int y1,int x2,int y2){return sum(x2,y2)-sum(x2,y1-1)-sum(x1-1,y2)+sum(x1-1,y1-1);}//区间询问
    #undef lowbit
};
struct BIT{
    A w[N][N];
    #define lowbit(x) ((x) & (-(x)))
    void add(int x, int y, A v) {for(;x<=n;x+=lowbit(x))for(int j=y;j<=m;j+=lowbit(j))w[x][j]+=v;}
    A query(int x, int y) {//单点询问
        A ans = 0;
        for (;x;x-=lowbit(x))for(int j=y;j;j-=lowbit(j))ans += w[x][j];
        return ans;
    }
	void add(int x1,int y1,int x2,int y2,A k){add(x1,y1,k),add(x2+1,y2+1,k),add(x2+1,y1,-k),add(x1,y2+1,-k);}//区间修改
};
struct BIT{//区间修改，区间查询，有求余
    #define lowbit(x) ((x) & (-x))
    A w[N][N][4];
    void add(int x, int y, int v){
        A a[4] = {v, (x * v) % p, (y * v) % p, (x * y * v) % p};
        for(;x<=n;x+=lowbit(x))for(int j=y;j<=n;j+=lowbit(j))for(short k=0;k<4;k++)w[x][j][k]=(w[x][j][k]+a[k])%p;
    }
    void add(int x1, int y1, int x2, int y2){add(x1, y1, 1), add(x1, y2 + 1, -1), add(x2 + 1, y1, -1), add(x2 + 1, y2 + 1, 1);}
    A query(int x, int y){
        int a[4] = {0, 0, 0, 0};
        for(;x;x-=lowbit(x))for(int j=y;j;j-=lowbit(j))for(short k=0;k<4;k++)a[k]=(a[k]+w[x][j][k])%p;
        return (a[0] * ((x + 1) * (y + 1) % p) - a[1] * (y + 1) % p - a[2] * (x + 1) % p + a[3]) % p;
    }
    A query(int x1, int y1, int x2, int y2){return(query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1)+10*p)%p;}
    #undef lowbit
};
struct BIT{//无求余
    #define lowbit(x) ((x) & (-x))
    A w[N][N][4];
    void add(int x, int y, int v){
        A a[4] = {v, (x * v), (y*v), (x * y * v)};
        for(;x<=n;x+=lowbit(x))for(int j=y;j<=n;j+=lowbit(j))for(short k=0;k<4;k++)w[x][j][k]=(w[x][j][k]+a[k]);
    }
    void add(int x1, int y1, int x2, int y2){add(x1, y1, 1), add(x1, y2 + 1, -1), add(x2 + 1, y1, -1), add(x2 + 1, y2 + 1, 1);}
    A query(int x, int y){
        int a[4] = {0, 0, 0, 0};
        for(;x;x-=lowbit(x))for(int j=y;j;j-=lowbit(j))for(short k=0;k<4;k++)a[k]=(a[k]+w[x][j][k]);
        return (a[0] * ((x + 1) * (y + 1)) - a[1] * (y + 1) - a[2] * (x + 1) + a[3]);
    }
    A query(int x1, int y1, int x2, int y2){return(query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1));}
    #undef lowbit
};
