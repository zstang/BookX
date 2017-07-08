#include <stdio.h>
#include <string.h>

int m,n;
int a[10][10];
char f[10][10][2010];

// ��������Ͻ��ߵ�(x, y)��ʱ����ȡ�����ֺ��ܷ�Ϊd
bool Solve(int x,int y,int d)
{
  // �ѽ����¼��f[x][y][d+1000], ��Ϊd����Ϊ����
  char &res=f[x][y][d+1000];

  // ���Ѿ����, ��ֱ�ӷ��ؽ��
  if(res!=-1) return res;
  // �ݹ������
  if(!x && !y) return res=(d==a[0][0]);
  if(x && Solve(x-1,y,d-a[x][y])) return res=1;
  if(y && Solve(x,y-1,d-a[x][y])) return res=1;
  // ��¼���������
  return res=0;
}

int main()
{
  while(scanf("%d%d",&m,&n)==2) {
    int i;
    for(i=0;i<m;i++)
      for(int j=0;j<n;j++) scanf("%d",&a[i][j]);
    // ȫ����Ϊ-1, ��ʾû�б����
    memset(f,255,sizeof(f));
    int ans=-1;
    // ����С�Ŀɴ��������
    for(i=1;i<=m*n*20;i++) if(Solve(m-1,n-1,i)) {
      ans=i;break;
    }
    // ������
    printf("%d\n",ans);
  }

  return 0;
}
