/////////////////////////////////�����й�/////////////////////////////////////
#define  uchar  unsigned char
#define  uint   unsigned int
#define  OLEN	128							//���������������С
unsigned char	seroutbuf[OLEN+1];				//�������������
unsigned char	outbit=0;					//���ͱ�֡���ֽ���  
unsigned char	idata curoutleng=OLEN;
#define  ILEN	128							//������ջ�������С
unsigned char	serinbuf[ILEN+1];				//������ջ�����
unsigned char	inbit=0;				//��ǰ�����ֽ�λ
unsigned char	idata passtime=0;				//ʱ��������
bit   seron;								//���ձ�������֡״̬

unsigned char machinebase;					//�����豸���
unsigned char baud;							//���粨����
unsigned char curmanno;						//��ǰ�����ߺ�

unsigned char netoutresult[OLEN+1];			//���������
unsigned char enoutresult;
unsigned char netoutcurdat[OLEN+1];			//��ʱ���ݻ���
unsigned char netoutsigned[OLEN+1];			//��ǩ������
unsigned char enoutsigned;					
unsigned char netoutcurman[OLEN+1];			//��ǰ��Ȩ����
unsigned char netoutcursta[OLEN+1];			//��ǰ�豸״̬

unsigned char netinbuf[OLEN+1];				//�����������ݻ���
unsigned char cardno[2][2][8];				//��Ȩ��ʶ����

void converdata() reentrant;
void writecardno(unsigned char nu) reentrant;

//���������ź���
OS_EVENT *NetComSem;

unsigned char code CRC[256]={
	0,94,188,226,97,63,221,131,194,156,126,32,163,253,31,65,
	157,195,33,127,252,162,64,30,95,1,227,189,62,96,130,220,
	35,125,159,193,66,28,254,160,225,191,93,3,128,222,60,98,
	190,224,2,92,223,129,99,61,124,34,192,158,29,67,161,255,
	70,24,250,164,39,121,155,197,132,218,56,102,229,187,89,7,
	219,133,103,57,186,228,6,88,25,71,165,251,120,38,196,154,
	101,59,217,135,4,90,184,230,167,249,27,69,198,152,122,36,
	248,166,68,26,153,199,37,123,58,100,134,216,91,5,231,185,
	140,210,48,110,237,179,81,15,78,16,242,172,47,113,147,205,
	17,79,173,243,112,46,204,146,211,141,111,49,178,236,14,80,
	175,241,19,77,206,144,114,44,109,51,209,143,12,82,176,238,
	50,108,142,208,83,13,239,177,240,174,76,18,145,207,45,115,
	202,148,118,40,171,245,23,73,8,86,180,234,105,55,213,139,
	87,9,235,181,54,104,138,212,149,203,41,119,244,170,72,22,
	233,183,85,11,136,214,52,106,43,117,151,201,74,20,246,168,
	116,42,200,150,21,75,169,247,182,232,10,84,215,137,107,53
};
//����CRC�룬
unsigned char GetMyCRC(unsigned char* source,unsigned char leng) reentrant
{
	unsigned char dscrc;
	dscrc=0x00;
	for(;leng!=0;leng--) 
	{
		dscrc=CRC[dscrc^(*source)];
		source++;
	}
	return(dscrc);
}

//9600 11.0592MHz
void init_serial() reentrant
{	
	PCON &= 0x7F;				
	TH1 = 0xFD;	
	TMOD |= 0X20;                      //��ʱ��1��ʽ2
	SCON = 0X50;                      //�������
	TR1 = 1;                          //������ʱ��1
	ES = 1;                           //���п��ж�����
}

//////////////////////////////////////////////////
//��һ�����ݵ����ͻ�����,����Ϊ�����������С
void myputbytes(unsigned char *outplace,unsigned char leng) reentrant
{ 	
	unsigned char i;
	for(i = 0; i < leng; i++)
		seroutbuf[i] = outplace[i];
	outbit = 0;
	curoutleng = leng;
}
//�����жϴ���
void serial() reentrant
{   
	if(RI)  
    {  
		RI = 0;
		if(passtime > 1)
		{
			serinbuf[0] = SBUF;
			if(serinbuf[0] == machinebase)
			{
				inbit = 1;
				seron = 1;
			}
			else
			{
				seron = 0;
			}
		}
		else
		{
			if(seron)
			{
				serinbuf[inbit] = SBUF;
				if(inbit < ILEN)
					inbit++;
				if(inbit > 3)
				{
					if(inbit == serinbuf[2]+4)
					{
						seron = 0;
						OSSemPost(NetComSem);											
					}
				}
			}
		}
		passtime = 0;		
	}
	else
    { 
		TI = 0;   
		if(outbit < curoutleng)
		{
			SBUF = seroutbuf[outbit]; 
			outbit++;
		}
		else
		{
			RS485 = 1;
		}
	}
}
void errorreturn() reentrant
{
	netinbuf[1] += 128;
	netinbuf[2] = 0;
	netinbuf[3] = GetMyCRC(netinbuf,3);
	myputbytes(netinbuf, 4);//ѹ���µķ������ݵ����ͻ�����	
}
//�������ݴ���
void netsend(void *lcnpdata) reentrant
{
	unsigned char neterr;
	unsigned char tem;
	

	lcnpdata = lcnpdata;
	NetComSem = OSSemCreate(0);
	seron = 0;
	RS485 = 1;
	//��ǰ�豸״̬
	netoutcursta[0] = machinebase;
	netoutcursta[1] = 1;
	netoutcursta[2] = 4;
	netoutcursta[3] = 0x03;
	netoutcursta[4] = 0x06;
	if(onpower == 0xA5)
	{
		netoutcursta[5] &= 0x06;//��λ������ǩ�ͽ������
	}
	else
	{
		netoutcursta[5] = 0x00;//����������
		enoutresult = 0;
		enoutsigned = 0;
	}
	/*
	-------1	//�м�ʱ����
	------1-	//�н������
	-----1--	//�б�ǩ����
	----1---	//����Ȩ��ʶ

	*/
	init_serial();
	while(1)
	{
		OSSemPend(NetComSem, 0, &neterr);
		if(neterr == OS_NO_ERR)
		{
			neterr = serinbuf[2]+4;
			if((serinbuf[1] < 128) && (serinbuf[neterr-1] == GetMyCRC(serinbuf,neterr-1)))
			{
				for(tem = 0; tem < neterr; tem++) 
				{
					netinbuf[tem] = serinbuf[tem];
				}
				switch(netinbuf[1])
				{
				case 1://�豸״̬
					if(neterr == 4)
					{
						netoutcursta[0] = machinebase;
						netoutcursta[6] = curmanno;//��ǰ�豸�����ߺ�
						netoutcursta[7] = GetMyCRC(netoutcursta,7);
						myputbytes(netoutcursta, 8);//ѹ���µķ������ݵ����ͻ�����
						RS485 = 0;			
						TI = 1;
					}
					break;
				case 2://��ʱ����
					if(neterr == 4)
					{
						converdata();
						myputbytes(netoutcurdat, 13);//ѹ���µķ������ݵ����ͻ�����
						RS485 = 0;			
						TI = 1;
					}
					break;
				case 3://�����
					if(neterr == 4)
					{
						if(enoutresult)
						{
							myputbytes(netoutresult, 101);//ѹ���µķ������ݵ����ͻ�����
							netoutcursta[5] &= 0xFD;//�޼����
						}
						else
						{
							errorreturn();
						}
						RS485 = 0;			
						TI = 1;
					}
					break;
				case 4://��ǩ����
					if(neterr == 4)
					{
						if(enoutsigned)
						{
							myputbytes(netoutsigned, 29);//ѹ���µķ������ݵ����ͻ�����
							netoutcursta[5] &= 0xFB;//�ޱ�ǩ����
						}
						else
						{
							errorreturn();
						}
						RS485 = 0;			
						TI = 1;
					}
					break;
				case 5://���͵�ǰ��Ȩ��ʶ����
					if(neterr == 4)
					{
						if( curmanno == 1)
						{
							netoutcurman[0] = machinebase;
							netoutcurman[1] = 5;
							netoutcurman[2] = 19;
							for(tem = 0; tem < 8; tem++) 
								netoutcurman[3+tem] = cardno[0][0][tem];
							netoutcurman[11] = cardno[0][1][0];
							netoutcurman[12] = cardno[0][1][1];
							netoutcurman[13] = cardno[0][1][2];	
							for(tem = 0; tem < 8; tem++) 
								netoutcurman[14+tem] = manname1[tem];
							netoutcurman[22] = GetMyCRC(netoutcurman,22);
							myputbytes(netoutcurman, 23);//ѹ���µķ������ݵ����ͻ�����
						}
						else
						{
							if( curmanno == 2)
							{
								netoutcurman[0] = machinebase;
								netoutcurman[1] = 5;
								netoutcurman[2] = 19;
								for(tem = 0; tem < 8; tem++) 
									netoutcurman[3+tem] = cardno[1][0][tem];
								netoutcurman[11] = cardno[1][1][0];
								netoutcurman[12] = cardno[1][1][1];
								netoutcurman[13] = cardno[1][1][2];	
								for(tem = 0; tem < 8; tem++) 
									netoutcurman[14+tem] = manname2[tem];
								netoutcurman[22] = GetMyCRC(netoutcurman,22);
								myputbytes(netoutcurman, 23);//ѹ���µķ������ݵ����ͻ�����
							}
							else//δ��Ȩ����
							{
								errorreturn();
							}
						}
						RS485 = 0;			
						TI = 1;
					}
					break;
				case 60://�޸���Ȩ��ʶ����
					if(neterr == 16)
					{
						if(netinbuf[3] == 0)
						{
							for(tem = 0; tem < 8; tem++)
							{
								cardno[0][0][tem] = netinbuf[tem+4];
							}
							cardno[0][1][0] = netinbuf[12];
							cardno[0][1][1] = netinbuf[13];
							cardno[0][1][2] = netinbuf[14];
							writecardno(0);
							myputbytes(netinbuf, 16);//ѹ���µķ������ݵ����ͻ�����
						}
						else
						{
							if(netinbuf[3] == 1)
							{
								for(tem = 0; tem < 8; tem++)
								{
									cardno[1][0][tem] = netinbuf[tem+4];
								}
								cardno[1][1][0] = netinbuf[12];
								cardno[1][1][1] = netinbuf[13];
								cardno[1][1][2] = netinbuf[14];
								writecardno(1);
								myputbytes(netinbuf, 16);//ѹ���µķ������ݵ����ͻ�����
							}
							else
							{
								errorreturn();
							}		
						}						
					}
					else
					{
						errorreturn();
					}
					RS485 = 0;			
					TI = 1;
					break;
				case 61://�޸��豸��ַ
					if(neterr == 5)
					{
						machinebase = netinbuf[3];
						Writei2c(&machinebase,14,1);
						myputbytes(netinbuf, 5);			//ѹ���µķ������ݵ����ͻ�����
						RS485 = 0;			
						TI = 1;
					}
					break;
				default://�Ƿ�������
					errorreturn();
					RS485 = 0;			
					TI = 1;
					break;
				}
			}
		}
	}
}


void converdata() reentrant
{
	union {unsigned int resultdata;
	struct {unsigned char hi;unsigned char lo;}half;
	}curresult;

	netoutcurdat[0] = machinebase;
	netoutcurdat[1] = 2;
	//���ݳ���
	netoutcurdat[2] = 9;
	curresult.resultdata = (unsigned int)(result[1]*10);//��ǰ��ѹ*10
	netoutcurdat[3] = curresult.half.hi;
	netoutcurdat[4] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(result[0]*100);//��ǰ����*100
	netoutcurdat[5] = curresult.half.hi;
	netoutcurdat[6] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(result[3]*1000);//��ǰ��ѹ*1000
	netoutcurdat[7] = curresult.half.hi;
	netoutcurdat[8] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(result[2]*100);//��ǰ����*100mR
	netoutcurdat[9] = curresult.half.hi;
	netoutcurdat[10] = curresult.half.lo;
	netoutcurdat[11] = lastselect;							//�������
	//����CRC
	netoutcurdat[12] = GetMyCRC(netoutcurdat,12);
}


unsigned char copytosend() reentrant
{
	union {unsigned int resultdata;
	struct {unsigned char hi;unsigned char lo;}half;
	}curresult;

	enoutresult = 1;
	if(netoutcursta[5] & 0x02)//�м����
		return(0);

	netoutresult[0] = machinebase;
	netoutresult[1] = 3;
	//���ݳ���
	netoutresult[2] = 97;
	//�Լ����
	netoutresult[3] = testname[0];
	netoutresult[4] = testname[1];
	netoutresult[5] = testname[2];
	netoutresult[6] = testname[3];
	netoutresult[7] = testname[4];
	netoutresult[8] = testname[5];
	netoutresult[9] = testname[6];
	netoutresult[10] = testname[7];
	//�����ߺ�
	switch(curmanno)
	{
	case 1:
		netoutresult[11] = manname1[0];
		netoutresult[12] = manname1[1];
		netoutresult[13] = manname1[2];
		netoutresult[14] = manname1[3];
		netoutresult[15] = manname1[4];
		netoutresult[16] = manname1[5];
		netoutresult[17] = manname1[6];
		netoutresult[18] = manname1[7];
		break;
	case 2:
		netoutresult[11] = manname2[0];
		netoutresult[12] = manname2[1];
		netoutresult[13] = manname2[2];
		netoutresult[14] = manname2[3];
		netoutresult[15] = manname2[4];
		netoutresult[16] = manname2[5];
		netoutresult[17] = manname2[6];
		netoutresult[18] = manname2[7];
		break;
	default:
		netoutresult[11] = ' ';
		netoutresult[12] = ' ';
		netoutresult[13] = ' ';
		netoutresult[14] = ' ';
		netoutresult[15] = ' ';
		netoutresult[16] = ' ';
		netoutresult[17] = ' ';
		netoutresult[18] = ' ';
		break;
	}
	//���ʱ��
	readtimer(disstr,1);
	netoutresult[19] = disstr[0];
	netoutresult[20] = disstr[1];
	netoutresult[21] = disstr[2];
	netoutresult[22] = disstr[3];
	netoutresult[23] = disstr[4];
	netoutresult[24] = disstr[5];
	netoutresult[25] = disstr[6];
	netoutresult[26] = disstr[7];
	//�����
	//8�����
	curresult.resultdata = (unsigned int)(outpointr[0]>0?outpointr[0]*100:0);//�������1(����)*100
	netoutresult[27] = curresult.half.hi;
	netoutresult[28] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[4]>0?outpointr[4]*100:0);//�������1(����)*100
	netoutresult[29] = curresult.half.hi;
	netoutresult[30] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[1]>0?outpointr[1]*100:0);//�������2(����)*100
	netoutresult[31] = curresult.half.hi;
	netoutresult[32] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[5]>0?outpointr[5]*100:0);//�������2(����)*100
	netoutresult[33] = curresult.half.hi;
	netoutresult[34] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[2]>0?outpointr[2]*100:0);//�������3(����)*100
	netoutresult[35] = curresult.half.hi;
	netoutresult[36] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[6]>0?outpointr[6]*100:0);//�������3(����)*100
	netoutresult[37] = curresult.half.hi;
	netoutresult[38] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[3]>0?outpointr[3]*100:0);//�������4(����)*100
	netoutresult[39] = curresult.half.hi;
	netoutresult[40] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[7]>0?outpointr[7]*100:0);//�������4(����)*100
	netoutresult[41] = curresult.half.hi;
	netoutresult[42] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[8]>0?outpointr[8]*100:0);//�������5(����)*100
	netoutresult[43] = curresult.half.hi;
	netoutresult[44] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[12]>0?outpointr[12]*100:0);//�������5(����)*100
	netoutresult[45] = curresult.half.hi;
	netoutresult[46] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[9]>0?outpointr[9]*100:0);//�������6(����)*100
	netoutresult[47] = curresult.half.hi;
	netoutresult[48] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[13]>0?outpointr[13]*100:0);//�������6(����)*100
	netoutresult[49] = curresult.half.hi;
	netoutresult[50] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[10]>0?outpointr[10]*100:0);//�������7(����)*100
	netoutresult[51] = curresult.half.hi;
	netoutresult[52] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[14]>0?outpointr[14]*100:0);//�������7(����)*100
	netoutresult[53] = curresult.half.hi;
	netoutresult[54] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[11]>0?outpointr[11]*100:0);//�������8(����)*100
	netoutresult[55] = curresult.half.hi;
	netoutresult[56] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointr[15]>0?outpointr[15]*100:0);//�������8(����)*100
	netoutresult[57] = curresult.half.hi;
	netoutresult[58] = curresult.half.lo;
	//8����ʱ
	curresult.resultdata = (unsigned int)(outpointt[0]>0?outpointt[0]*10000:0);//������ʱ1(����)*10000
	netoutresult[59] = curresult.half.hi;
	netoutresult[60] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[4]>0?outpointt[4]*10000:0);//������ʱ1(����)*10000
	netoutresult[61] = curresult.half.hi;
	netoutresult[62] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[1]>0?outpointt[1]*10000:0);//������ʱ2(����)*10000
	netoutresult[63] = curresult.half.hi;
	netoutresult[64] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[5]>0?outpointt[5]*10000:0);//������ʱ2(����)*10000
	netoutresult[65] = curresult.half.hi;
	netoutresult[66] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[2]>0?outpointt[2]*10000:0);//������ʱ3(����)*10000
	netoutresult[67] = curresult.half.hi;
	netoutresult[68] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[6]>0?outpointt[6]*10000:0);//������ʱ3(����)*10000
	netoutresult[69] = curresult.half.hi;
	netoutresult[70] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[3]>0?outpointt[3]*10000:0);//������ʱ4(����)*10000
	netoutresult[71] = curresult.half.hi;
	netoutresult[72] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[7]>0?outpointt[7]*10000:0);//������ʱ4(����)*10000
	netoutresult[73] = curresult.half.hi;
	netoutresult[74] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[8]>0?outpointt[8]*10000:0);//������ʱ5(����)*10000
	netoutresult[75] = curresult.half.hi;
	netoutresult[76] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[12]>0?outpointt[12]*10000:0);//������ʱ5(����)*10000
	netoutresult[77] = curresult.half.hi;
	netoutresult[78] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[9]>0?outpointt[9]*10000:0);//������ʱ6(����)*10000
	netoutresult[79] = curresult.half.hi;
	netoutresult[80] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[13]>0?outpointt[13]*10000:0);//������ʱ6(����)*10000
	netoutresult[81] = curresult.half.hi;
	netoutresult[82] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[10]>0?outpointt[10]*10000:0);//������ʱ7(����)*10000
	netoutresult[83] = curresult.half.hi;
	netoutresult[84] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[14]>0?outpointt[14]*10000:0);//������ʱ7(����)*10000
	netoutresult[85] = curresult.half.hi;
	netoutresult[86] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[11]>0?outpointt[11]*10000:0);//������ʱ8(����)*10000
	netoutresult[87] = curresult.half.hi;
	netoutresult[88] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outpointt[15]>0?outpointt[15]*10000:0);//������ʱ8(����)*10000
	netoutresult[89] = curresult.half.hi;
	netoutresult[90] = curresult.half.lo;
	//�����  
	curresult.resultdata = (unsigned int)(outresult[0]*10);//���ϵ�ѹ*10
	netoutresult[91] = curresult.half.hi;
	netoutresult[92] = curresult.half.lo;
	curresult.resultdata = (unsigned int)(outresult[1]*10);//�ͷŵ�ѹ*10
	netoutresult[93] = curresult.half.hi;
	netoutresult[94] = curresult.half.lo;
	if(lastselect > 0)
	{
		curresult.resultdata = (unsigned int)(outresult[2]*1000);//������ѹ*1000
		netoutresult[95] = curresult.half.hi;
		netoutresult[96] = curresult.half.lo;
		curresult.resultdata = (unsigned int)(outresult[3]*1000);//�ͷ���ѹ*1000
		netoutresult[97] = curresult.half.hi;
		netoutresult[98] = curresult.half.lo;
	}
	else
	{
		netoutresult[95] = 0;
		netoutresult[96] = 0;
		netoutresult[97] = 0;
		netoutresult[98] = 0;
	}
	netoutresult[99] = lastselect;							//�������
	//����CRC
	netoutresult[100] = GetMyCRC(netoutresult,100);
	//�޸�״̬
	netoutcursta[5] |= 0x02;//�м����
	return(1);
}

unsigned char copytosigned() reentrant
{
	if(netoutcursta[5] & 0x04)//�б�ǩ����
		return(0);
	netoutsigned[0] = machinebase;
	netoutsigned[1] = 4;
	//���ݳ���
	netoutsigned[2] = 25;
	//�Լ����
	netoutsigned[3] = testname[0];
	netoutsigned[4] = testname[1];
	netoutsigned[5] = testname[2];
	netoutsigned[6] = testname[3];
	netoutsigned[7] = testname[4];
	netoutsigned[8] = testname[5];
	netoutsigned[9] = testname[6];
	netoutsigned[10] = testname[7];
	//�����ߺ�
	switch(curmanno)
	{
	case 1:
		netoutsigned[11] = manname1[0];
		netoutsigned[12] = manname1[1];
		netoutsigned[13] = manname1[2];
		netoutsigned[14] = manname1[3];
		netoutsigned[15] = manname1[4];
		netoutsigned[16] = manname1[5];
		netoutsigned[17] = manname1[6];
		netoutsigned[18] = manname1[7];
		break;
	case 2:
		netoutsigned[11] = manname2[0];
		netoutsigned[12] = manname2[1];
		netoutsigned[13] = manname2[2];
		netoutsigned[14] = manname2[3];
		netoutsigned[15] = manname2[4];
		netoutsigned[16] = manname2[5];
		netoutsigned[17] = manname2[6];
		netoutsigned[18] = manname2[7];
		break;
	default:
		netoutsigned[11] = ' ';
		netoutsigned[12] = ' ';
		netoutsigned[13] = ' ';
		netoutsigned[14] = ' ';
		netoutsigned[15] = ' ';
		netoutsigned[16] = ' ';
		netoutsigned[17] = ' ';
		netoutsigned[18] = ' ';
		break;
	}
	//���ʱ��
	readtimer(disstr,1);
	netoutsigned[19] = disstr[0];
	netoutsigned[20] = disstr[1];
	netoutsigned[21] = disstr[2];
	netoutsigned[22] = disstr[3];
	netoutsigned[23] = disstr[4];
	netoutsigned[24] = disstr[5];
	netoutsigned[25] = disstr[6];
	netoutsigned[26] = disstr[7];
	netoutsigned[27] = lastselect;

	netoutcursta[5] |= 0x04;//�б�ǩ����
	//����CRC
	netoutsigned[28] = GetMyCRC(netoutsigned,28);
	enoutsigned = 1;
	return(1);

}
void cardon() reentrant
{
	netoutcursta[5] |= 0x08;//����Ȩ��ʶ
}
void teston() reentrant
{
	netoutcursta[5] |= 0x01;//�м�ʱ����
}
void readcardno() reentrant
{
	Readi2c(cardno[0][0],224,8);
	Readi2c(cardno[0][1],232,8);
	Readi2c(cardno[1][0],240,8);
	Readi2c(cardno[1][1],248,8);
}

void writecardno(unsigned char nu) reentrant
{
	if(nu == 0)
	{
		Writei2c(cardno[0][0],224,8);
		Writei2c(cardno[0][1],232,8);
	}
	else
	{
		Writei2c(cardno[1][0],240,8);
		Writei2c(cardno[1][1],248,8);
	}
}