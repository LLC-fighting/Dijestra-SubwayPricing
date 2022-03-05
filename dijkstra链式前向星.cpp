#include<iostream>
#include<string>
#include<cstdio>
#include<queue>

#define inf 0x3f3f3f3f

using namespace std;

const int nodeNum=48;						//节点数 
const int edgeNum=102;						//边数 

const string stationName[nodeNum+2]={"","pingguoyuan","gucheng","bajiao amusement park","babaoshan","yuquanlu","wukesong",
							"wanshoulu","gongzhufen","military museum","muxidi","nanlishilu","fuxingmen","fuchengmen",
							"chegongzhuang","xizhimen","xinjiekou","ping'anli","xisi","lingjinghutong","xidan","zhangchunjie",
							"xuanwumen","tian'anmenxi(W)","jishuitan","guloudajie","andingmen","tian'anmendong(E)","wangfujing",
							"hepingmen","qianmen","chongwenmen","dongdan","dengshikou","dongsi","zhangzizhonglu","beixinqiao"
							,"yonghegong lama temple","dongzhimen","dongsishitiao","chaoyangmen","jianguomen","beijing railway station","yonganli",
							"guomao","dawanglu","sihui","sihuidong(E)"};	//车站名 

struct edge									//边 
{
	int to;									//终点 
	int next;								//与这条边同起点的下一条边的终点 
	int length;								//这条边的长度； 
}e[edgeNum+2];

struct node									//节点 
{
	int now,w;								//now代表该点位置  w是起点到此的距离 
	node(int a,int b)						//构造函数 
	{
		now=a;
		w=b;
	}
	bool operator<(const node& x) const		//重写优先队列的排序函数  小的先出 
	{
		return w>x.w;						//到起点距离小的排在前面 
	}
};

int head[edgeNum+2];						//记录起点相同的边中最后一条边 
int vis[nodeNum+2];							//标记节点是否使用 
int dis[nodeNum+2];							//记录各节点到要求起点的最短距离 

priority_queue<node>q;						//定义一个优先队列，用于存储选出的节点 

void add(int u,int v,int w)					//加边  u起点 v终点  w边长 
{
	static int cnt=0; 						//记录边的标号 
	e[++cnt].to=v;							//第cnt条边起点 
	e[cnt].length=w;						//第cnt条边长度 
	e[cnt].next=head[u];					//第cnt条边的下一条边 
	head[u]=cnt;							//
	e[++cnt].to=u;							//无向边 存两次 
	e[cnt].length=w;
	e[cnt].next=head[v];
	head[v]=cnt;
} 

void dijkstra(int s)
{
	for(int i=1;i<=nodeNum;i++)
		dis[i]=inf;							//初始距离都设为无穷 
	dis[s]=0;
	q.push((node){s,0});					//起始点加入队列 
	while(q.size())							//队列为空了，就说明所有点都是最短距离了 
	{
		node x=q.top();						//读出队列中距离最小的 
		q.pop();							//使刚读入的节点出列 
		int r=x.now;
		if(vis[r])							//如果该节点使用过，则继续下一个循环 
			continue;
		vis[r]=1; 							//标记这次选用的节点 
		for(int i=head[r];i;i=e[i].next)	//遍历所有与r相连的点 
		{
			int t=e[i].to;
			if(dis[t]>dis[r]+e[i].length)	//如果经过r到达t的距离更新，就更新到t的距离 
			{
				dis[t]=dis[r]+e[i].length;		
				q.push((node){t,dis[t]});	//将t压入队列 
			}
		}
	}
}

int fee(int distance)						//计算费用 
{
	if(distance==0)							//先判断这个，不可以在底下用d判断，因为可能distance小于1000，d为0 
		return 0;
	int d=distance/1000;
	if(d<=6)
		return 3;
	else if(d<=12)
		return 4;
	else if(d<=22)
		return 5;
	else if(d<=32)
		return 6;
	else
		return 6+(d-32)/20;
} 

void init()									//初始化数据 
{
	add(1,2,2606);							//存边 
	add(2,3,1921);
	add(3,4,1953);
	add(4,5,1479);
	add(5,6,1810);
	add(6,7,1778);
	add(7,8,1313);
	add(8,9,1172);
	add(9,10,1166);
	add(10,11,1291);
	add(11,12,424);
	add(12,20,1590);
	add(20,23,1217);
	add(23,27,925);
	add(27,28,852);
	add(28,32,774);
	add(32,41,1230);
	add(41,43,1377);
	add(43,44,790);
	add(44,45,1385);
	add(45,46,1673);
	add(46,47,1714);
	add(15,14,909);
	add(14,13,960);
	add(13,12,1832);
	add(12,21,1234);
	add(21,22,929);
	add(22,29,851);
	add(29,30,1171);
	add(30,31,1634);
	add(31,42,1030);
	add(42,41,945);
	add(41,40,1763);
	add(40,39,1027);
	add(39,38,824);
	add(38,37,2228);
	add(37,26,794);
	add(26,25,1237);
	add(25,24,1766);
	add(24,15,1899);
	add(15,16,1025);
	add(16,17,1100);
	add(17,18,1100);
	add(18,19,869);
	add(19,20,1011);
	add(20,22,815);
	add(36,37,866);
	add(35,36,791);
	add(34,35,1016);
	add(34,33,848);
	add(33,32,945);
	add(32,31,821);
}

int main()
{
	string str;
	getline(cin,str);						//不能用cin，有的站名包含空格 
	int p=str.find(";");					//找到；对应的下标 
	string start,end;	
	start=str.substr(0,p);					//划分；前的 
	end=str.substr(p+1);					//划分；后的 
	int st=0,en=0;
	for(int i=1;i<=nodeNum;i++)
	{
		if(stationName[i]==start)			//找到起点对应下标 
			st=i;
		if(stationName[i]==end)				//找到终点对应下标 
			en=i;
	}
	init();	
	dijkstra(st);
	cout<<fee(dis[en]); 					//计算到终点的钱 
	return 0;
}
