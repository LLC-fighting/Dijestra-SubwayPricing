#include<iostream>
#include<string>
#include<cstdio>
#include<queue>

#define inf 0x3f3f3f3f

using namespace std;

const int nodeNum=48;						//�ڵ��� 
const int edgeNum=102;						//���� 

const string stationName[nodeNum+2]={"","pingguoyuan","gucheng","bajiao amusement park","babaoshan","yuquanlu","wukesong",
							"wanshoulu","gongzhufen","military museum","muxidi","nanlishilu","fuxingmen","fuchengmen",
							"chegongzhuang","xizhimen","xinjiekou","ping'anli","xisi","lingjinghutong","xidan","zhangchunjie",
							"xuanwumen","tian'anmenxi(W)","jishuitan","guloudajie","andingmen","tian'anmendong(E)","wangfujing",
							"hepingmen","qianmen","chongwenmen","dongdan","dengshikou","dongsi","zhangzizhonglu","beixinqiao"
							,"yonghegong lama temple","dongzhimen","dongsishitiao","chaoyangmen","jianguomen","beijing railway station","yonganli",
							"guomao","dawanglu","sihui","sihuidong(E)"};	//��վ�� 

struct edge									//�� 
{
	int to;									//�յ� 
	int next;								//��������ͬ������һ���ߵ��յ� 
	int length;								//�����ߵĳ��ȣ� 
}e[edgeNum+2];

struct node									//�ڵ� 
{
	int now,w;								//now����õ�λ��  w����㵽�˵ľ��� 
	node(int a,int b)						//���캯�� 
	{
		now=a;
		w=b;
	}
	bool operator<(const node& x) const		//��д���ȶ��е�������  С���ȳ� 
	{
		return w>x.w;						//��������С������ǰ�� 
	}
};

int head[edgeNum+2];						//��¼�����ͬ�ı������һ���� 
int vis[nodeNum+2];							//��ǽڵ��Ƿ�ʹ�� 
int dis[nodeNum+2];							//��¼���ڵ㵽Ҫ��������̾��� 

priority_queue<node>q;						//����һ�����ȶ��У����ڴ洢ѡ���Ľڵ� 

void add(int u,int v,int w)					//�ӱ�  u��� v�յ�  w�߳� 
{
	static int cnt=0; 						//��¼�ߵı�� 
	e[++cnt].to=v;							//��cnt������� 
	e[cnt].length=w;						//��cnt���߳��� 
	e[cnt].next=head[u];					//��cnt���ߵ���һ���� 
	head[u]=cnt;							//
	e[++cnt].to=u;							//����� ������ 
	e[cnt].length=w;
	e[cnt].next=head[v];
	head[v]=cnt;
} 

void dijkstra(int s)
{
	for(int i=1;i<=nodeNum;i++)
		dis[i]=inf;							//��ʼ���붼��Ϊ���� 
	dis[s]=0;
	q.push((node){s,0});					//��ʼ�������� 
	while(q.size())							//����Ϊ���ˣ���˵�����е㶼����̾����� 
	{
		node x=q.top();						//���������о�����С�� 
		q.pop();							//ʹ�ն���Ľڵ���� 
		int r=x.now;
		if(vis[r])							//����ýڵ�ʹ�ù����������һ��ѭ�� 
			continue;
		vis[r]=1; 							//������ѡ�õĽڵ� 
		for(int i=head[r];i;i=e[i].next)	//����������r�����ĵ� 
		{
			int t=e[i].to;
			if(dis[t]>dis[r]+e[i].length)	//�������r����t�ľ�����£��͸��µ�t�ľ��� 
			{
				dis[t]=dis[r]+e[i].length;		
				q.push((node){t,dis[t]});	//��tѹ����� 
			}
		}
	}
}

int fee(int distance)						//������� 
{
	if(distance==0)							//���ж�������������ڵ�����d�жϣ���Ϊ����distanceС��1000��dΪ0 
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

void init()									//��ʼ������ 
{
	add(1,2,2606);							//��� 
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
	getline(cin,str);						//������cin���е�վ�������ո� 
	int p=str.find(";");					//�ҵ�����Ӧ���±� 
	string start,end;	
	start=str.substr(0,p);					//���֣�ǰ�� 
	end=str.substr(p+1);					//���֣���� 
	int st=0,en=0;
	for(int i=1;i<=nodeNum;i++)
	{
		if(stationName[i]==start)			//�ҵ�����Ӧ�±� 
			st=i;
		if(stationName[i]==end)				//�ҵ��յ��Ӧ�±� 
			en=i;
	}
	init();	
	dijkstra(st);
	cout<<fee(dis[en]); 					//���㵽�յ��Ǯ 
	return 0;
}
