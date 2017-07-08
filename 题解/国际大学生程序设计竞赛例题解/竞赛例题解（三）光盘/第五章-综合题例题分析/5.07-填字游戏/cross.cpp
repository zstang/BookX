#include <fstream.h>
ifstream in;
ofstream out;
#define cin in
#define cout out
#include <string.h>

int r,c,w;
#define MAXR 60
#define MAXC 60
#define MAXW 310
#define bool int
#define true 1
#define false 0
char input[MAXW][MAXR];
char matrx[MAXR][MAXC];
int rmatrx[MAXR][MAXC];
int cmatrx[MAXR][MAXC];

struct node{
    int index;
    bool mark;
    node* next;
};
node* refer[MAXR];
struct point{
    bool dir;
    int x,y,l;
};
#define MAXP 310
point array[MAXP];
int m;
bool put[MAXP];
int stack[MAXP];
bool sta[MAXP];
int top;
void write(int who,int index)
{
    int i;
  if(array[who].dir==0)
  {
   for(i=0;i<array[who].l;i++)
       if(matrx[array[who].x][array[who].y+i]=='.')
       {  
matrx[array[who].x][array[who].y+i]=input[index][i];         if(cmatrx[array[who].x][array[who].y+i]>=0&&sta[cmatrx[array[who].x][array[who].y+i]]==0)
          {
              stack[top++]=cmatrx[array[who].x][array[who].y+i];
              sta[cmatrx[array[who].x][array[who].y+i]]=1;
          }
       }
  }else {
     for(i=0;i<array[who].l;i++)
       if(matrx[array[who].x+i][array[who].y]=='.')
       {  
matrx[array[who].x+i][array[who].y]=input[index][i];      if(rmatrx[array[who].x+i][array[who].y]>=0&&sta[rmatrx[array[who].x+i][array[who].y]]==0)
          {
              stack[top++]=rmatrx[array[who].x+i][array[who].y];
              sta[rmatrx[array[who].x+i][array[who].y]]=1;
          }
       }
  }
}
bool check(int who,node* temp){
    if(temp->mark==true)
        return false;
    int index=temp->index;
        int i;
  if(array[who].dir==0)
  {
   for(i=0;i<array[who].l;i++)
       if(matrx[array[who].x][array[who].y+i]!='.'&&matrx[array[who].x][array[who].y+i]!=input[index][i])
           return false;
  }
  else {
     for(i=0;i<array[who].l;i++)
       if(matrx[array[who].x+i][array[who].y]!='.'&&matrx[array[who].x+i][array[who].y]!=input[index][i])
           return false;
  }
  return true;
}
void save(char* s,int who){
    int i;
    if(array[who].dir==0)
    {
        for(i=0;i<array[who].l;i++)
     s[i]=matrx[array[who].x][array[who].y+i];
    }else 
        for(i=0;i<array[who].l;i++)
         s[i]=matrx[array[who].x+i][array[who].y];
}
void store(char* s,int who){
    int i;
    if(array[who].dir==0)
    {
        for(i=0;i<array[who].l;i++)
         matrx[array[who].x][array[who].y+i]=s[i];
    }else
        for(i=0;i<array[who].l;i++)
     matrx[array[who].x+i][array[who].y]=s[i];
}
    
int doing(){
    int i;
    char copy[MAXR];
    if(top==0)   //���ջ��
    {
        for(i=0;i<m;i++)
            if(put[i]==0){  //�е���û��д,�Ͱ�����ջ
                stack[top++]=i;
                sta[i]=1;
                break;
}
            if(i>=m){   //������е��ʶ���д����,��������
                return 1;
            }
    }
    int a=stack[top-1];//��ջ��ȡ��һ���ɹ���д��λ��
    sta[a]=0;
    top--;
    i=top;//����ջ��ָ��
    put[a]=1; //����д��־
    save(copy,a);
    node* temp=refer[array[a].l];
//�ڳ��������������ʺϵĵ�����дλ��a
    while(temp!=NULL)
    {
        if(check(a,temp)) //���tempָ�ŵĵ�������дλ��a
        {    temp->mark=true;
             write(a,temp->index);// tempָ�ŵĵ�����д��λ��a
             if(doing())return 1; 
while(top>i){
sta[stack[top-1]]=0;top--;//�ָ���ջ
}
             temp->mark=false;
             store(copy,a);
        }
        temp=temp->next;
    }
    put[a]=0; //��λ��д��־
    return 0;
}

void process(){
    int i,j;
    cin>>r>>c>>w;
    m=0;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            cin>>matrx[i][j];
        for(i=0;i<MAXR;i++)
            refer[i]=NULL;
        node* temp;
        for(i=0;i<w;i++){
          cin>>input[i];
          temp=new node;   
              temp->index=i; //��д����������
              temp->mark=0;
              temp->next=refer[strlen(input[i])];
              refer[strlen(input[i])]=temp;
        }


        i=0,j=0;
        int s,e,l;
        while(i<r)  //ɨ��ÿһ���ҳ�����д��λ��,��¼��array��
        {
            while(i<r){
                  while(matrx[i][j]=='#'&&j<c)j++;
                 if(j>=c){i++,j=0;}
                else break;
            }
            if(i<r){
                s=i,e=j,l=0;
                while(matrx[i][j]!='#'&&j<c){
                    rmatrx[i][j]=m;
                    j++,l++;
}
                if(l>0){
                    array[m].dir=0;
                    array[m].l=l;
                    array[m].x=s;
                    array[m].y=e;
                    m++;
                }
            }
        }
        i=0,j=0;
        while(j<c) //ɨ��ÿһ���ҳ�����д��λ��,��¼��array��
        {
            while(j<c){
              while(matrx[i][j]=='#'&&i<r)i++;
              if(i>=r){j++,i=0;}
              else break;
            }
            if(j<c){
                s=i,e=j,l=0;
                while(matrx[i][j]!='#'&&i<r){
                    cmatrx[i][j]=m;
                    i++,l++;
}
                if(l>0){
                    array[m].dir=1;
                    array[m].l=l;
                    array[m].x=s;
                    array[m].y=e;
                    m++;
}
            }
        }
      for(i=0;i<m;i++)
          put[i]=sta[i]=0;  //��ʼ����ջ��Ǻ���д���
      top=0;
      doing();  //����
      for(i=0;i<r;i++)  //����������
      {   
          for(j=0;j<c;j++)
              cout<<matrx[i][j];
          cout<<endl;
      }
      for(i=0;i<w;i++){ //�ͷſռ�
            temp=refer[strlen(input[i])];
        if(temp!=NULL){
                refer[strlen(input[i])]=refer[strlen(input[i])]->next;
                delete temp;
            }
        }

}
int z;
void main(){
    in.open(��cross.in��);
    out.open("cross.out");
    int t;
    cin>>t;
    while(t--){
         if(z==0)z=1;
         else cout<<endl;
            process();
    }
}
