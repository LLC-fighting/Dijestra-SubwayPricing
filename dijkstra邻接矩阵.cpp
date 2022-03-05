#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
# define inf 0x3f3f3f3f				//定义一个充当无穷大的数 
using namespace std;

const int num=48;					//车站数 
int a[num+1][num+1];				//存图的二维数组 
const string stationName[num+1]={"","pingguoyuan","gucheng","bajiao amusement park","babaoshan","yuquanlu","wukesong",
							"wanshoulu","gongzhufen","military museum","muxidi","nanlishilu","fuxingmen","fuchengmen",
							"chegongzhuang","xizhimen","xinjiekou","ping'anli","xisi","lingjinghutong","xidan","zhangchunjie",
							"xuanwumen","tian'anmenxi(W)","jishuitan","guloudajie","andingmen","tian'anmendong(E)","wangfujing",
							"hepingmen","qianmen","chongwenmen","dongdan","dengshikou","dongsi","zhangzizhonglu","beixinqiao"
							,"yonghegong lama temple","dongzhimen","dongsishitiao","chaoyangmen","jianguomen","beijing railway station","yonganli",
							"guomao","dawanglu","sihui","sihuidong(E)"};
//1 苹果园2 古城3 八角游乐园4 八宝山5 玉泉路6 五棵松7 万寿路8 公主坟9 军事博物馆10 木樨地11 南礼士路12 复兴门13 阜成门
//14 车公庄15 西直门16 新街口17 平安里18 西四19 灵境胡同20 西单21 长椿街22 宣武门23 天安门西24 积水潭25 鼓楼大街26 安定门
//27 天安门东28 王府井29 和平门30 前门31 崇文门32 东单33 灯市口34 东四35 张自忠路36 北新桥
//37 雍和宫38 东直门39 东四十条40 朝阳门41 建国门42 北京站 43 永安里 44 国贸 45 大望路46 四惠47 四惠东
									//车站名字
int dis[num+1];						//到起点s的距离 
int vis[num+1]; 					//用于标记一个节点是否已经使用过
 
void init()							//初始化数据函数 
{
	for(int i=1;i<=num;i++)
	{
		for(int j=1;j<=num;j++)
			if(i==j)
				a[i][j]=0;			//同一个车站标记为0 
			else 
				a[i][j]=inf;		//初始距离为无穷大 
	}
	//站点距离
	//1号线 
	a[1][2]=a[2][1]=2606;
	a[2][3]=a[3][2]=1921;
	a[3][4]=a[4][3]=1953;
	a[4][5]=a[5][4]=1479;
	a[5][6]=a[6][5]=1810;
	a[6][7]=a[7][6]=1778;
	a[7][8]=a[8][7]=1313;
	a[8][9]=a[9][8]=1172;
	a[9][10]=a[10][9]=1166;
	a[10][11]=a[11][10]=1291;
	a[11][12]=a[12][11]=424;
	a[12][20]=a[20][12]=1590;
	a[20][23]=a[23][20]=1217;
	a[23][27]=a[27][23]=925;
	a[27][28]=a[28][27]=852;
	a[28][32]=a[32][28]=774;
	a[32][41]=a[41][32]=1230;
	a[41][43]=a[43][41]=1377;
	a[43][44]=a[44][43]=790;
	a[44][45]=a[45][44]=1385;
	a[45][46]=a[46][45]=1673;
	a[46][47]=a[47][46]=1714;
	//2号线
	a[15][14]=a[14][15]=909;
	a[14][13]=a[13][14]=960;
	a[13][12]=a[12][13]=1832;
	a[12][21]=a[21][12]=1234;
	a[21][22]=a[22][21]=929;
	a[22][29]=a[29][22]=851;
	a[29][30]=a[30][29]=1171;
	a[30][31]=a[31][30]=1634;
	a[31][42]=a[42][31]=1023;
	a[42][41]=a[41][42]=945;
	a[41][40]=a[40][41]=1763;
	a[40][39]=a[39][40]=1027;
	a[39][38]=a[38][39]=824;
	a[38][37]=a[37][38]=2228;
	a[37][26]=a[26][37]=794;
	a[26][25]=a[25][26]=1237;
	a[25][24]=a[24][25]=1766;
	a[24][15]=a[15][24]=1899;
	//4号线(西直门-宣武门)
	a[15][16]=a[16][15]=1025; 
	a[16][17]=a[17][16]=1100;
	a[17][18]=a[18][17]=1100;
	a[18][19]=a[19][18]=869;
	a[19][20]=a[20][19]=1011;
	a[20][22]=a[22][20]=815;
	//5号线(雍和宫-崇文门)
	a[37][36]=a[36][37]=866;
	a[36][35]=a[35][36]=791;
	a[35][34]=a[34][35]=1016;
	a[34][33]=a[33][34]=848;
	a[33][32]=a[32][33]=945;
	a[32][31]=a[31][32]=821;
}

void dijkstra(int start)
{
	vis[start]=1; 					//标记起点已经使用 
	for(int i=1;i<=num;i++)			//初始化所有节点到起点的距离 
		dis[i]=a[start][i]; 
	bool tmp=1;						//标记变量 
	while(1)
	{
		tmp=1;						//恢复为1
		int min=inf;				//最小的刚开始为无穷 
		int work=0;
		for(int i=1;i<=num;i++)
		{
			if(dis[i]<min&&!vis[i])	//距离小且没有使用过该节点 
			{
				min=dis[i];			//找到剩余节点中距离最短的 
				work=i;				//记录该节点的下标
				tmp=0;				//将标记变量置为0 
			}
		}
		if(tmp)						//如果上一步中没有找到，说明所有节点都使用了，退出循环 
			break;
		vis[work]=1;				//标记该次选中的距离最短的节点
		for(int i=1;i<=num;i++)		//更新距离 
			if(!vis[i]&&dis[i]>dis[work]+a[work][i])				//如果这个点没有使用过且不是最短距离就更新 
				dis[i]=dis[work]+a[work][i]; 	//更新为最小值 
	} 
} 

int fee(int distance)				//计算费用 
{
	if(distance==0)					//先判断这个，不可以在底下用d判断，因为可能distance小于1000，d为0 
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

int main()
{
	string str;
	getline(cin,str);						//不能用cin，有的站名包含空格 
	int p=str.find(";");					//找到；对应的下标 
	string start,end;	
	start=str.substr(0,p);					//划分；前的 
	end=str.substr(p+1);					//划分；后的 
	int s,e;
	for(int i=1;i<=num;i++)
	{
		if(stationName[i]==start)			//找到起点对应下标 
			s=i;
		if(stationName[i]==end)				//找到终点对应下标 
			e=i;
	}
	init();									//初始化 
	dijkstra(s);							//Dijkstra算法
	cout<<fee(dis[e]); 						//计算到终点的钱 
	return 0;
}

