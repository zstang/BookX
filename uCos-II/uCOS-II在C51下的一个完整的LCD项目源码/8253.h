////////////////////////����ģ��////////////////////////
//��Ӧ8253ͨ���ļ���ֵ
//����count8253[x][0]Ϊ���һ��ļ�����
//count8253[x][1]Ϊ���һ�εļ���ֵ
//count8253[x][2]Ϊ��һ�εļ���ֵ 
//count8253[x][0]=count8253[x][2]-count8253[x][1]
unsigned int  count8253[4][3];		
void getconut()
{
	COM8253=0x04;
	dat168.dat8.lo=A8253;
	dat168.dat8.hi=A8253;
	count8253[0][2]=count8253[0][1];
	count8253[0][1]=dat168.dat16;
	count8253[0][0]=count8253[0][2]-count8253[0][1];
	
	COM8253=0x44;
	dat168.dat8.lo=B8253;
	dat168.dat8.hi=B8253;
	count8253[1][2]=count8253[1][1];
	count8253[1][1]=dat168.dat16;
	count8253[1][0]=count8253[1][2]-count8253[1][1];
	
	COM8253=0x84;
	dat168.dat8.lo=C8253;
	dat168.dat8.hi=C8253;
	count8253[2][2]=count8253[2][1];
	count8253[2][1]=dat168.dat16;
	count8253[2][0]=count8253[2][2]-count8253[2][1];

	dat168.dat8.lo=TL0;
	dat168.dat8.hi=TH0;
	count8253[3][2]=count8253[3][1];
	count8253[3][1]=dat168.dat16;
	count8253[3][0]=count8253[3][1]-count8253[3][2];
}
//��ʼ����������ʽ2 ��������couΪ��ʼ����ͨ����
void initcount()
{
	//ͨ��ʹ��0 1����2
	//ʹ��8253 0 1��
	PALE=1;
	PA0=1;PA1=1;PA2=1;
	PALE=0;
	//���ü�����ʽ2��������
	COM8253=0x34;
	A8253=0xFF;A8253=0xFF;
	//���ü�����ʽ2��������
	COM8253=0x74;
	B8253=0xFF;B8253=0xFF;
	//���ü�����ʽ2��������
	COM8253=0xb4;
	C8253=0xff;C8253=0xff;
	PALE=1;
	PA0=1;PA1=1;PA2=1;
	PALE=0;
	//T0�����������2����
	TMOD &= 0XF0;                    
    TMOD  |= 0X5;
    TL0 = 0X0;						
    TH0 = 0X0;						
    TR0 = 1;
}
