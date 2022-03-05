#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
# define inf 0x3f3f3f3f				//����һ���䵱�������� 
using namespace std;

const int num=48;					//��վ�� 
int a[num+1][num+1];				//��ͼ�Ķ�ά���� 
const string stationName[num+1]={"","pingguoyuan","gucheng","bajiao amusement park","babaoshan","yuquanlu","wukesong",
							"wanshoulu","gongzhufen","military museum","muxidi","nanlishilu","fuxingmen","fuchengmen",
							"chegongzhuang","xizhimen","xinjiekou","ping'anli","xisi","lingjinghutong","xidan","zhangchunjie",
							"xuanwumen","tian'anmenxi(W)","jishuitan","guloudajie","andingmen","tian'anmendong(E)","wangfujing",
							"hepingmen","qianmen","chongwenmen","dongdan","dengshikou","dongsi","zhangzizhonglu","beixinqiao"
							,"yonghegong lama temple","dongzhimen","dongsishitiao","chaoyangmen","jianguomen","beijing railway station","yonganli",
							"guomao","dawanglu","sihui","sihuidong(E)"};
//1 ƻ��԰2 �ų�3 �˽�����԰4 �˱�ɽ5 ��Ȫ·6 �����7 ����·8 ������9 ���²����10 ľ�ص�11 ����ʿ·12 ������13 ������
//14 ����ׯ15 ��ֱ��16 �½ֿ�17 ƽ����18 ����19 �龳��ͬ20 ����21 ������22 ������23 �찲����24 ��ˮ̶25 ��¥���26 ������
//27 �찲�Ŷ�28 ������29 ��ƽ��30 ǰ��31 ������32 ����33 ���п�34 ����35 ������·36 ������
//37 Ӻ�͹�38 ��ֱ��39 ����ʮ��40 ������41 ������42 ����վ 43 ������ 44 ��ó 45 ����·46 �Ļ�47 �Ļݶ�
									//��վ����
int dis[num+1];						//�����s�ľ��� 
int vis[num+1]; 					//���ڱ��һ���ڵ��Ƿ��Ѿ�ʹ�ù�
 
void init()							//��ʼ�����ݺ��� 
{
	for(int i=1;i<=num;i++)
	{
		for(int j=1;j<=num;j++)
			if(i==j)
				a[i][j]=0;			//ͬһ����վ���Ϊ0 
			else 
				a[i][j]=inf;		//��ʼ����Ϊ����� 
	}
	//վ�����
	//1���� 
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
	//2����
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
	//4����(��ֱ��-������)
	a[15][16]=a[16][15]=1025; 
	a[16][17]=a[17][16]=1100;
	a[17][18]=a[18][17]=1100;
	a[18][19]=a[19][18]=869;
	a[19][20]=a[20][19]=1011;
	a[20][22]=a[22][20]=815;
	//5����(Ӻ�͹�-������)
	a[37][36]=a[36][37]=866;
	a[36][35]=a[35][36]=791;
	a[35][34]=a[34][35]=1016;
	a[34][33]=a[33][34]=848;
	a[33][32]=a[32][33]=945;
	a[32][31]=a[31][32]=821;
}

void dijkstra(int start)
{
	vis[start]=1; 					//�������Ѿ�ʹ�� 
	for(int i=1;i<=num;i++)			//��ʼ�����нڵ㵽���ľ��� 
		dis[i]=a[start][i]; 
	bool tmp=1;						//��Ǳ��� 
	while(1)
	{
		tmp=1;						//�ָ�Ϊ1
		int min=inf;				//��С�ĸտ�ʼΪ���� 
		int work=0;
		for(int i=1;i<=num;i++)
		{
			if(dis[i]<min&&!vis[i])	//����С��û��ʹ�ù��ýڵ� 
			{
				min=dis[i];			//�ҵ�ʣ��ڵ��о�����̵� 
				work=i;				//��¼�ýڵ���±�
				tmp=0;				//����Ǳ�����Ϊ0 
			}
		}
		if(tmp)						//�����һ����û���ҵ���˵�����нڵ㶼ʹ���ˣ��˳�ѭ�� 
			break;
		vis[work]=1;				//��Ǹô�ѡ�еľ�����̵Ľڵ�
		for(int i=1;i<=num;i++)		//���¾��� 
			if(!vis[i]&&dis[i]>dis[work]+a[work][i])				//��������û��ʹ�ù��Ҳ�����̾���͸��� 
				dis[i]=dis[work]+a[work][i]; 	//����Ϊ��Сֵ 
	} 
} 

int fee(int distance)				//������� 
{
	if(distance==0)					//���ж�������������ڵ�����d�жϣ���Ϊ����distanceС��1000��dΪ0 
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
	getline(cin,str);						//������cin���е�վ�������ո� 
	int p=str.find(";");					//�ҵ�����Ӧ���±� 
	string start,end;	
	start=str.substr(0,p);					//���֣�ǰ�� 
	end=str.substr(p+1);					//���֣���� 
	int s,e;
	for(int i=1;i<=num;i++)
	{
		if(stationName[i]==start)			//�ҵ�����Ӧ�±� 
			s=i;
		if(stationName[i]==end)				//�ҵ��յ��Ӧ�±� 
			e=i;
	}
	init();									//��ʼ�� 
	dijkstra(s);							//Dijkstra�㷨
	cout<<fee(dis[e]); 						//���㵽�յ��Ǯ 
	return 0;
}

