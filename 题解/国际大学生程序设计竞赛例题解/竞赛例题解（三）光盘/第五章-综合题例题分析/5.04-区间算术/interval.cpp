//Interval arithmetic
#include<stdio.h>
#include<math.h>
const double eps=1e-7;
const long num=100;       
typedef struct node{           
	double min;       //��¼�����½�
	double max;       //��¼�����Ͻ�
} interval;
interval data[num];  //����ջ
char stack[num],     //�����ջ
     deg[128];       //��ASCII��Ϊ�±�,��¼����������ȼ�
long record[num],    //�����ջ����ӦԪ�ص����ȼ�,
     top,            //ָ�������ջ��ջ��λ��
	 n,              //����ջ���������
	 good;           //good=0���������˳���Ϊ0�����
void add()                        //�ԼӺŵĴ���
{
   interval a,b;
   a.min=data[n-2].min;
   a.max=data[n-2].max;
   b.min=data[n-1].min;
	 b.max=data[n-1].max;
   n-=2;
   data[n].min=a.min+b.min;
   data[n].max=a.max+b.max;
   n++;
}
void minus()
{
	interval a,b;
	if(record[top]==1){              //���Ϊ���ţ�������������
	   a.min=data[n-2].min;
       a.max=data[n-2].max;
       b.min=data[n-1].min;
			 b.max=data[n-1].max;
       n-=2;
	   data[n].min=a.min-b.max;
	   data[n].max=a.max-b.min;
	   n++;
	}
	else{                           //���Ϊ���ţ�����ȡ������
		n--;
		a.min=data[n].min;
		a.max=data[n].max;
		data[n].max=-a.min;
		data[n].min=-a.max;
		n++;
	}
}
void multi()                        //�Գ˺ŵĴ���
{
	interval a,b;
	double v[4];
	long i;
	a.min=data[n-2].min;
    a.max=data[n-2].max;
    b.min=data[n-1].min;
    b.max=data[n-1].max;
    n-=2;
	v[0]=a.min*b.min;
	v[1]=a.min*b.max;
	v[2]=a.max*b.min;
	v[3]=a.max*b.max;
	data[n].min=data[n].max=v[0];
	for(i=1;i<4;i++){
		if(v[i]<data[n].min)
			data[n].min=v[i];
		if(v[i]>data[n].max)
			data[n].max=v[i];
	}
	n++;
}
void divide()                       //�Գ��ŵĴ���
{
	interval a,b;
	double v[4];long i;
	a.min=data[n-2].min;
    a.max=data[n-2].max;
    b.min=data[n-1].min;
    b.max=data[n-1].max;
		n-=2;
	if(b.min<=0&&b.max>=0){         //��������������0�����
		good=0;
		printf("Division by zero\n");
		return;
	}
	v[0]=a.min/b.min;
	v[1]=a.min/b.max;
	v[2]=a.max/b.min;
	v[3]=a.max/b.max;
	data[n].min=data[n].max=v[0];
	for(i=1;i<4;i++){
		if(v[i]<data[n].min)
			data[n].min=v[i];
		if(v[i]>data[n].max)
			data[n].max=v[i];
	}
	n++;
}
int main()
{
	freopen("interval.in","r",stdin);
	freopen("interval.out","w",stdout);
	deg['+']=deg['-']=1;      //���ø�����������ȼ�,��ֵԽ��,���ȼ�Խ��
	deg['*']=deg['/']=2;      
	deg['(']=4;               //3ȱʡΪ���ŵ����ȼ�
	long sum,prev;           //�������ֶ����'-'�Ǹ��źͼ���,
                //�������'-'ʱprev=0,����'-'����һ�����������,�Ǹ���
                //�������'-'ʱprev=1,����'-'����һ������������,�Ǽ���
	char ch;
	do{
		sum=0;n=0;good=1;
		top=-1;prev=0;
		do{
			if(scanf("%c",&ch)!=1||ch=='\n'){  //�ж��Ƿ����һ������
				if(good){
				   while(good&&top>=0){
					     if(stack[top]=='+')
						    add();
							 if(stack[top]=='-')
								minus();
							 if(stack[top]=='*')
								multi();
							 if(stack[top]=='/')
								divide();
							 top--;
					 }
				}
				break;
			}
			sum++;
			if(ch=='['){
				scanf("%lf%*c%lf%*c",&data[n].min,&data[n].max);
				n++;
				prev=1;
			}
			else if(good){
				if(ch=='+'||ch=='*'||ch=='/'){
					while(good&&top>=0&&record[top]>=deg[ch]){
							if(stack[top]=='(')break;
							if(stack[top]=='+')
								 add();
								if(stack[top]=='-')
								 minus();
								if(stack[top]=='*')
								 multi();
								if(stack[top]=='/')
								 divide();
								top--;
					}
					stack[++top]=ch;
					record[top]=deg[ch];
					prev=0;
				}
				if(ch=='-'){
					if(prev==0){                  //���ŵ���ջ����
						while(good&&top>=0&&record[top]>=3){
							if(stack[top]=='(')break;
							if(stack[top]=='+')
									 add();
									if(stack[top]=='-')
									 minus();
									if(stack[top]=='*')
									 multi();
									if(stack[top]=='/')
									 divide();
									top--;
						}
						stack[++top]=ch;
						record[top]=3;
						prev=1;
					}
					else{                         //���ŵ���ջ����
						while(good&&top>=0&&record[top]>=1){
							if(stack[top]=='(')break;
							if(stack[top]=='+')
									 add();
									if(stack[top]=='-')
									 minus();
									if(stack[top]=='*')
									 multi();
									if(stack[top]=='/')
									 divide();
									top--;
						}
						stack[++top]=ch;
						record[top]=1;
						prev=0;
					}
				}
				if(ch=='('){
					stack[++top]=ch;
					record[top]=4;
					prev=0;
				}
				if(ch==')'){
					while(good&&top>=0){
						if(stack[top]=='('){
							 top--;
							 break;
						}
						if(stack[top]=='+')
							 add();
							if(stack[top]=='-')
							 minus();
							if(stack[top]=='*')
							 multi();
							if(stack[top]=='/')
							 divide();
							top--;
					}
					prev=1;
				}
			}
		}while(1);
		if(!sum)return 0;
		if(!good)continue;
		if(fabs(data[0].min)<eps)data[0].min=0.0;
		if(fabs(data[0].max)<eps)data[0].max=0.0;
		printf("[%.3lf,%.3lf]\n",data[0].min,data[0].max);
	}while(1);
}
