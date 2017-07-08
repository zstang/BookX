#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n,k,root[100]; // root��¼ÿ�����ĸ�
int *list[100][50],deg[100][50];
     // list������е�����deg���ÿ����ÿ���ڵ�Ķ�

//������
void read_data()
{
	char flag[100];    // flag���ÿ���ڵ��Ƿ������
	int v1[100],v2[100],i,j;  // (v1[i],v2[i])������һ����
	scanf("%d%d",&k,&n);
	for(i=0;i<k;i++){                    // ���ж���ÿһ����
		memset(deg[i],0,sizeof(deg[i]));
		memset(flag,0,sizeof(flag));
		for(j=0;j<n-1;j++){              // ��������n-1����
			scanf("%d%d",&v1[j],&v2[j]);
			v1[j]--,v2[j]--;
			deg[i][v1[j]]++;      // ͳ�ƣ�deg[i][v]��ʾ��i�����нڵ�v�Ķ�
			flag[v2[j]]=1;
		}
		for(j=0;j<n;j++) if (!flag[j]) root[i]=j;   // Ѱ�Ҹ����ĸ�
		for(j=0;j<n;j++) list[i][j]=new int[deg[i][j]];   // ����ռ�����
		memset(deg[i],0,sizeof(deg[i]));
		for(j=0;j<n-1;j++) list[i][v1[j]][deg[i][v1[j]]++]=v2[j];
         // �������ڽӱ���ʽ����deg��
	}
}

//����������
void swap(int &a,int &b){
	int c;
	c=a,a=b,b=c;
}

//�Ƚϱ��Ϊt1��������p1Ϊ������������Ϊt2��������p2Ϊ���������Ĵ�С
//���ǰ�ߴ��򷵻�1�����ߴ󷵻�-1����ȷ���0
int compare(int t1,int p1,int t2,int p2)
{
	int i,j;
	if (deg[t1][p1]>deg[t2][p2]) return 1;       // �ȱȽ϶ȵĴ�С
	else if (deg[t1][p1]<deg[t2][p2]) return -1;
	else{                         // ����ͬ������µݹ�رȽ�ÿ������
		if (deg[t1][p1]==0) return 0;
		for(i=0;i<deg[t1][p1];i++){
			j=compare(t1,list[t1][p1][i],t2,list[t2][p2][i]);
			if (j!=0) return j;
		}
		return 0;    // ������������ͬ����ô��������Ҳ����ͬ��
	}
}

//�ѱ��Ϊt��������pΪ�������������������С��ʾ
void sort(int t,int p)
{
	int i,j;
     // �ȶ�ÿ����������ȡ�ø�����С�ı�ʾ
	for(i=0;i<deg[t][p];i++) sort(t,list[t][p][i]); 
     // �ٶ�������������
	for(i=0;i<deg[t][p];i++)
		for(j=i+1;j<deg[t][p];j++){
			if (compare(t,list[t][p][i],t,list[t][p][j])==1) swap(list[t][p][i],list[t][p][j]);
		}
}

void solve()   // ������
{
	int i,j;
	char flag[100];
	
	//����
	for(i=0;i<k;i++) sort(i,root[i]);
	
	//ɨ��
	memset(flag,0,sizeof(flag));  // flag������Ƿ��Ѿ���ӡ
	for(i=0;i<k;i++) if (!flag[i]){   // ��һ�ж�ÿ�û�û��ӡ����
		flag[i]=1;
		printf("%d",i+1);
        // Ѱ�Һ�i��ͬ����
		for(j=1;j<k;j++) if (!flag[j]&&compare(i,root[i],j,root[j])==0){
			flag[j]=1;
			printf("=%d",j+1);
		}
		printf("\n");
	}
}

// ������
int main()
{
	freopen("Trees.in","r",stdin);    //ָ����������ļ�
	freopen("Trees.out","w",stdout);
	read_data();    //��������
	solve();        //������
	fclose(stdin); //{�ر��ļ�}
	fclose(stdout); //{�ر��ļ�}
	return 0;
}
