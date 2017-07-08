//���³�������SED1330���Ƶ�Һ����ʾģ��,��ʾ����Ϊ320X240
#include "stdarg.h"

#define CR        39                                   /*������ʾ���ڵĳ���,���ַ�Ϊ��λ*/
#define TCR       45                                   /*����LCD��ʱ�䳣��.���ʱ�䳣��Ӧ�þ���С(��Ƶ�ʹ�),��ֹת��ʱ������˸*/
#define LF        239                                  /*����LCD������*/
#define APL       40                                   /*����LCDһ����ռ���������ֽ���,��8λ*/
#define APH       0                                    /*����LCDһ����ռ���������ֽ���,��8λ*/

#define SAD1      0X0000                               /*������ʾһ����ַ*/
#define SAD1L     0X00                                 /*������ʾһ����ַ��8λ*/
#define SAD1H     0X00                                 /*������ʾһ����ַ��8λ*/
#define SL1       239                                  /*������ʾһ����ռ��ʾ��Ļ������*/

#define SAD2      0X2800                               /*������ʾ������ַ*/
#define SAD2L     0X00                                 /*������ʾ������ַ��8λ*/
#define SAD2H     0X28                                 /*������ʾ������ַ��8λ*/
#define SL2       239                                  /*������ʾ������ռ��ʾ��Ļ������*/

#define SAD3      0X5000                               /*������ʾ������ַ*/
#define SAD3L     0X00                                 /*������ʾ������ַ��8λ*/
#define SAD3H     0X50                                 /*������ʾ������ַ��8λ*/

#define SAD4      0X2800                               /*������ʾ������ַ*/
#define SAD4L     0X00                                 /*������ʾ������ַ��8λ*/
#define SAD4H     0X28                                 /*������ʾ������ַ��8λ*/

#define TA_LEFT		0									//����뷽ʽ
#define TA_CENTER	1									//���Ķ��뷽ʽ
///////////////////////
void wrstr(unsigned int sad,unsigned int hnum,unsigned char vnum,unsigned char* str);
void wrdot(unsigned int sad,unsigned int hnum,unsigned char vnum);
void initlcd();
void rectangle(unsigned int sad,unsigned int strhnum,unsigned char strvnum,unsigned int endhnum,unsigned char endvnum,unsigned char fill);
void wrchat(unsigned int sad,unsigned int hnum,unsigned char vnum,unsigned char chatnum);
void liney(unsigned int sad,unsigned int x,unsigned char y1,unsigned char y2);
void linex(unsigned int sad,unsigned char y,unsigned int x1,unsigned int x2);
//////////////////////
/*�趨������ʾ����Ϊ:��һ��ʾ��   0000H----27FFH  (10K����)
                     �ڶ���ʾ��   2800H----4FFFH  (10K����)
                     ������ʾ��   5000H----77FFH  (10K����)*/
const unsigned char  LCDSYSINIT[8]={0X30,0X87,0X07,CR,TCR,LF,APL,APH};                          /*��LCD0��SYS���ò���*/
const unsigned char  LCDSCRINIT[10]={SAD1L,SAD1H,SL1,SAD2L,SAD2H,SL2,SAD3L,SAD3H,SAD4L,SAD4H};  /*��LCD0��SCR���ò���*/


/***********************************************************
*   ��������: INITLCD                                     *
*   ������;: ��SED1330 ��ʼ����3��ͼ�η�ʽ               *
*   �������: ��                                          *
*														  *
*                                                         *
***********************************************************/
void initlcd()           
{
	xdata unsigned char counter;
	
	LCDORDER=0X40;							/*����SYS����*/
	for(counter=0;counter<=7;counter++)
	{LCDDATA=LCDSYSINIT[counter];}			/*����8��SYSTERM����*/
	
	LCDORDER=0X44;							/*����SCROLL����*/
	for(counter=0;counter<=9;counter++)
	{LCDDATA=LCDSCRINIT[counter];}			/*����ʮ��SCROLL����*/
	
	LCDORDER=0X5A;							/*����HDOTSCR����*/
	LCDDATA=0X00;							/*����HDOTSCR����*/
	
	LCDORDER=0X4F;
	
	LCDORDER=0X5B;							/*����OVLAY����*/
	LCDDATA=0X1D;							/*����OVLAY����,��ʾ��ʽ==(L1*L2)+L3 */
	
	LCDORDER=0X59;							/*������ʾ*/
	LCDDATA=0X40;							/*����һ.����.��, �رչ��*/
	//LCDDATA=0X04|0x10|0x40;							/*����һ.����.��, �رչ��*/
	
	
	LCDORDER=0X5D;							/*���ù��*/
	LCDDATA=0X07;							/*ˮƽ����Ϊ7*/
	LCDDATA=0X87;							/*��ֱ����Ϊ7,��Ӱ��ʾ*/	
}
/***********************************************************
*   ��������: WRDOT()                                     *
*   ������;: ��ָ�����ָ��λ��д��.                     *
*   �������: sad    ָ������ڴ��ַ                     *
*             hnum   �������                             *
*             vnum   ��������                             *
*                                                         *
***********************************************************/
void wrdot(unsigned int sad,unsigned int hnum,unsigned char vnum)
{
	unsigned char flag;
    union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}curadd;
    curadd.add=vnum*(APL)+hnum/8+sad;
    flag=hnum-(hnum/8)*8;
    flag=(0x80)>>flag;
	
    LCDORDER=0X46;                       /*���ù���ַ*/
    LCDDATA=curadd.addhalf.addlo;
    LCDDATA=curadd.addhalf.addhi;
	
    LCDORDER=0X43;                       /*ȡ���õ����ڵ�ַ������*/ 
    flag=flag|(LCDORDER);
	
    LCDORDER=0X46;
    LCDDATA=curadd.addhalf.addlo;
    LCDDATA=curadd.addhalf.addhi;
	
    LCDORDER=0X42;
    LCDDATA=flag;	
}                    
/***********************************************************
*   ��������: WRDOT()                                     *
*   ������;: ��ָ�����ָ��λ�����.                     *
*   �������: sad    ָ������ڴ��ַ                     *
*             hnum   �������                             *
*             vnum   ��������                             *
*                                                         *
***********************************************************/
/*void clsdot(unsigned int sad,unsigned int hnum,unsigned char vnum)
{
	xdata unsigned char flag;
    xdata union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}curadd;
    curadd.add=vnum*(APL)+hnum/8+sad;
    flag=hnum-(hnum/8)*8;
    flag=(0x80)>>flag;
	flag=~flag;
	
    LCDORDER=0X46;                       //���ù���ַ
    LCDDATA=curadd.addhalf.addlo;
    LCDDATA=curadd.addhalf.addhi;
	
    LCDORDER=0X43;                       //ȡ���õ����ڵ�ַ������
    flag=flag&(LCDORDER);
	
    LCDORDER=0X46;
    LCDDATA=curadd.addhalf.addlo;
    LCDDATA=curadd.addhalf.addhi;
	
    LCDORDER=0X42;
    LCDDATA=flag;	
}           */
/***********************************************************
*   ��������: CLSSED()                                     *
*   ������;: �����ʾ��			                       *
*   �������: ��										   *
*								                           *
*								                           *
*                                                          *
************************************************************/
void clssed(unsigned int sad)
{
	xdata union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}curadd;
    curadd.add=sad;
    LCDORDER=0X46;                       /*���ù���ַ*/
    LCDDATA=curadd.addhalf.addlo;
    LCDDATA=curadd.addhalf.addhi;
	LCDORDER=0X4C;
	LCDORDER=0X42;
	sad=0;
	while(sad<9600)
	{
		LCDDATA=0X00;
		sad++;
	}
}           

/***********************************************************
*   ��������: LINEX()                                      *
*   ������;: ��ˮƽ��  			                       *
*   �������: sad    ָ������ڴ��ַ                      *
*			  yλ��										   *
*			  x1���									   * 
*			  x2�յ�			                           *
*								                           *
*                                                          *
************************************************************/
void linex(unsigned int sad,unsigned char y,unsigned int x1,unsigned int x2)
{
	do{
		wrdot(sad,x1,y);
		x1++;
	}while(x1<=x2);
}    

/***********************************************************
*   ��������: LINEY()                                      *
*   ������;: ����ֱ��  			                       *
*   �������: sad    ָ������ڴ��ַ                      *
*			  xλ��										   *
*			  y1���									   * 
*			  y2�յ�			                           *
*								                           *
*                                                          *
************************************************************/
void liney(unsigned int sad,unsigned int x,unsigned char y1,unsigned char y2)
{
	do{
		wrdot(sad,x,y1);
		y1++;
	}while(y1<=y2);
}    
/***********************************************************
*   ��������: LINE()                                       *
*   ������;: ����ֱ��  			                       *
*   �������: sad    ָ������ڴ��ַ                      *
*			  x1���									   *
*			  x2�յ�									   *
*			  y1���									   * 
*			  y2�յ�			                           *
*								                           *
*                                                          *
************************************************************/
/*void line(unsigned int sad,unsigned int x1,unsigned int x2,unsigned char y1,unsigned char y2)
{
	unsigned char tem,tem1;
	if(y2>y1)
	{
		tem=y2-y1;
		for(tem1=0;tem1<=tem/2;tem1++)
		{
			wrdot(sad,x1,y1+tem1);
			wrdot(sad,x2,y1+tem/2+tem1+1);
		}
	}
	else
	{
		tem=y1-y2;
		for(tem1=0;tem1<=tem/2;tem1++)
			wrdot(sad,x1,y1-tem1);
		for(tem1=1;tem1<=tem/2;tem1++)
			wrdot(sad,x2,y1-tem/2-tem1);
	}
}    */

/***********************************************************
*   ��������: WRCHAT()                                    *
*   ������;: ��ָ�����ָ��λ��дASCII�ַ�               *
*   �������: sad    ָ������ڴ��ַ                     *
*             hnum   �������                             *
*             vnum   ��������                             *
*             chatnum�ַ������ֵ                         *
***********************************************************/
void wrchatasc(unsigned int sad,unsigned int hnum,unsigned char vnum,unsigned char chatnum)
{
	unsigned char buff[16];                   /*����,���ڶ�дASCII�ַ���16*16����*/
	unsigned char counter;
	unsigned char flag1;
	unsigned char flag2;
	unsigned char offset;
	union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}curadd;
	curadd.add=vnum*(APL)+hnum/8+sad;      /*�������ַ*/
	offset=hnum-(hnum/8)*8;               /*������ַ��ڵ�ƫ����*/
	
	LCDORDER=0X46;                         /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	
	/*����д�ַ�����*/
	LCDORDER=0X4F;                         /*ȷ������ƶ�����Ϊ����*/
	
	flag1=(0XFF)<<(8-offset);
	flag2=~flag1;
	
		
	LCDORDER=0X43;                         /*�ɹ�괦��ʼ,���¶���16������*/                                        
	for(counter=0;counter<16;counter++)
    {  /*����LCDORDER�Ĳ�����һ��д,һ�ζ�,C51�����ڶ�����ʱ�Ż���ֱ��ʹ��д������,
		�������ж�����,���Լ�һ������ָ��*/
		buff[counter]=(LCDORDER&flag1)|(ASC_MSK[chatnum][counter]>>offset);
    }
	
	LCDORDER=0X46;                         /*�ٴ�ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	LCDORDER=0X42;
	for(counter=0;counter<16;counter++)
    {
		(LCDDATA)=buff[counter];
	}
	

	curadd.add=curadd.add+1;         /*��ַ��1,�Ƶ��Ҳ�*/
	
	LCDORDER=0X4F;                   /*ȷ������ƶ�����Ϊ����*/
	
	LCDORDER=0X46;                   /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	flag1=(0XFF)>>offset;
	flag2=~flag1;
	flag1=0XFF>>offset;
				
	LCDORDER=0X43;                   /*�ɹ�괦��ʼ,���¶���16������*/
	for(counter=0;counter<16;counter++)
	{
		buff[counter]=(LCDORDER&flag1)|(ASC_MSK[chatnum][counter]<<(8-offset));
	}
	
	LCDORDER=0X46;                   /*�ٴ�ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	LCDORDER=0X42;
	for(counter=0;counter<16;counter++)
	{
		(LCDDATA)=buff[counter];
	}
}
/***********************************************************
*   ��������: WRCHAT()                                    *
*   ������;: ��ָ�����ָ��λ��д�����ַ�                    *
*   �������: sad    ָ������ڴ��ַ                     *
*             hnum   �������                             *
*             vnum   ��������                             *
*             chatnum�ַ������ֵ                         *
***********************************************************/
void wrchat(unsigned int sad,unsigned int hnum,unsigned char vnum,unsigned char chatnum)
{
	unsigned char buff[16];                   /*����,���ڶ�дASCII�ַ���16*16����*/
	unsigned char counter;
	unsigned char flag1;
	unsigned char flag2;
	unsigned char offset;
	union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}curadd;
	curadd.add=vnum*(APL)+hnum/8+sad;      /*�������ַ*/
	offset=hnum-(hnum/8)*8;               /*������ַ��ڵ�ƫ����*/
	
	LCDORDER=0X46;                         /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	
	/*����д�ַ�����*/
	LCDORDER=0X4F;                         /*ȷ������ƶ�����Ϊ����*/
	
	flag1=(0XFF)<<(8-offset);
	flag2=~flag1;
	
		
	LCDORDER=0X43;                         /*�ɹ�괦��ʼ,���¶���16������*/                                        
	for(counter=0;counter<16;counter++)
    	buff[counter]=(LCDORDER&flag1)|(GB_16[chatnum].Msk[counter]>>offset);
    
	LCDORDER=0X46;                         /*�ٴ�ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	LCDORDER=0X42;
	for(counter=0;counter<16;counter++)
    	LCDDATA=buff[counter];
	

    /*����д�ַ����Ҳ�*/
	curadd.add=curadd.add+1;         /*��ַ��1,�Ƶ��Ҳ�*/
	
	LCDORDER=0X4F;                   /*ȷ������ƶ�����Ϊ����*/
	
	LCDORDER=0X46;                   /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	flag1=(0XFF)>>offset;
	flag2=~flag1;
	flag1=0XFF>>offset;
				
	LCDORDER=0X43;                   /*�ɹ�괦��ʼ,���¶���16������*/
	for(counter=0;counter<16;counter++)
		buff[counter]=(LCDORDER&flag1)|(GB_16[chatnum].Msk[counter]<<(8-offset));
	
	LCDORDER=0X46;                   /*�ٴ�ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	LCDORDER=0X42;
	for(counter=0;counter<16;counter++)
		LCDDATA=buff[counter];
	
////////////////////////////////////////////////
	LCDORDER=0X46;                         /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	
	/*����д�ַ�����*/
	LCDORDER=0X4F;                         /*ȷ������ƶ�����Ϊ����*/
	
	flag1=(0XFF)<<(8-offset);
	flag2=~flag1;	
		
	LCDORDER=0X43;                         /*�ɹ�괦��ʼ,���¶���16������*/                                        
	for(counter=0;counter<16;counter++)
    	buff[counter]=(LCDORDER&flag1)|(GB_16[chatnum].Msk[counter+16]>>offset);
    
	LCDORDER=0X46;                         /*�ٴ�ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	LCDORDER=0X42;
	for(counter=0;counter<16;counter++)
		LCDDATA=buff[counter];
	
	
	curadd.add=curadd.add+1;         /*��ַ��1,�Ƶ��Ҳ�*/
	
	LCDORDER=0X4F;                   /*ȷ������ƶ�����Ϊ����*/
	
	LCDORDER=0X46;                   /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	flag1=(0XFF)>>offset;
	flag2=~flag1;
	flag1=0XFF>>offset;
				
	LCDORDER=0X43;                   /*�ɹ�괦��ʼ,���¶���10������*/
	for(counter=0;counter<16;counter++)
		buff[counter]=(LCDORDER&flag1)|(GB_16[chatnum].Msk[counter+16]<<(8-offset));
	
	LCDORDER=0X46;                   /*�ٴ�ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	LCDORDER=0X42;
	for(counter=0;counter<16;counter++)
		LCDDATA=buff[counter];
}
void myprintf(unsigned int sad,unsigned char bcenter,unsigned int hnum,unsigned char vnum,unsigned char *fmt, ...)
{
	va_list arg_ptr;
	unsigned char tmpBuf[64];				// LCD��ʾ���ݻ�����
	unsigned char i,uLen,j;
	unsigned char c1,c2;
	
	va_start(arg_ptr,fmt);
	uLen=(unsigned char)vsprintf(tmpBuf,fmt,arg_ptr);
	va_end(arg_ptr);
	
	if(bcenter)
		hnum=hnum-(uLen*4);
	i=0;
	while(i<uLen)
	{
		c1 = tmpBuf[i];
		c2 = tmpBuf[i+1];
		if(c1<128)//ASCII
		{
			if(c1<31)
			{
				if(c1==13||c1==10)
				{					
					i++;
					if(vnum<224)
						vnum+=16;
					else
						vnum=0;
					hnum=0;
					continue;
				}		
				c1=31;
			}
			wrchatasc(sad,hnum,vnum,(c1-31));
			hnum+=8;
		}
		else
		{	// ����
			for(j=0;j<sizeof(GB_16)/sizeof(GB_16[0]);j++)
			{
				if(c1==GB_16[j].Index[0]&&c2==GB_16[j].Index[1])
				{
					wrchat(sad,hnum,vnum,j);
					break;
				}
			}			
			hnum+=16;
			i++;
		}
		i++;
		if(hnum>312)
		{
			hnum=0;
			if(vnum<224)
				vnum+=17;
			else
				vnum=0;
		}		
	}
}

#if Number361
void wrnumber(unsigned int sad,unsigned char hnum,unsigned char vnum,unsigned char chatnum)
{
	unsigned char counter;
	union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}curadd;
	curadd.add=vnum*(APL)+hnum+sad;      /*�������ַ*/
	LCDORDER=0X46;                         /*ȷ������ַ*/
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	
	
	LCDORDER=0X4F;                         /*ȷ������ƶ�����Ϊ����*/
	LCDORDER=0X42;
	for(counter=0;counter<36;counter++)
    	LCDDATA=mynumbermsk[chatnum][counter];
    //����д�ַ����Ҳ�
	curadd.add++;	
	LCDORDER=0X46;                   
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	LCDORDER=0X42;
	for(counter=0;counter<36;counter++)
    	LCDDATA=mynumbermsk[chatnum][counter+36];
	curadd.add++;	
	LCDORDER=0X46;                   
	LCDDATA=curadd.addhalf.addlo;
	LCDDATA=curadd.addhalf.addhi;
	LCDORDER=0X42;
	for(counter=0;counter<36;counter++)
    	LCDDATA=mynumbermsk[chatnum][counter+72];
    
}

void mynuprintf(unsigned int sad,unsigned char hnum,unsigned char vnum,unsigned char *fmt, ...)
{
	va_list arg_ptr;
	unsigned char tmpBuf[16];				// LCD��ʾ���ݻ�����
	unsigned char i,uLen;
	
	va_start(arg_ptr,fmt);
	uLen=(unsigned char)vsprintf(tmpBuf,fmt,arg_ptr);
	va_end(arg_ptr);
	
	i=0;
	hnum=hnum-(uLen*3);
	while(i<uLen)
	{
		if(tmpBuf[i]<58&&tmpBuf[i]>47)
		{
			wrnumber(sad,hnum,vnum,(tmpBuf[i]-47));
			hnum+=3;
		}
		else
		{
			if(tmpBuf[i]=='.')
			{
				wrnumber(sad,hnum,vnum,0);
				hnum+=1;
			}
			else
			{
				if(tmpBuf[i]=='-')
					wrnumber(sad,hnum,vnum,12);
				else
					wrnumber(sad,hnum,vnum,11);
				hnum+=3;
			}			
		}
		i++;		
	}
}

#endif


/*void rectangl(unsigned int sad,unsigned int strhnum,unsigned char strvnum,unsigned int endhnum,unsigned char endvnum)
{
	linex(sad,strvnum,strhnum,endhnum);
	linex(sad,endvnum,strhnum,endhnum);
	liney(sad,strhnum,strvnum,endvnum);
	liney(sad,endhnum,strvnum,endvnum);
}*/
/***********************************************************
*   ��������: RECTANGLE()                                 *
*   ������;: ��ָ�����ָ��λ��������                  *
*   �������: sad       ָ������ڴ���ʼ��ַ              *
*             strhnum   ��ʼ�������                      *
*             strvnum   ��ʼ��������                      *
*             endrhnum  �����������                      *
*             endvnum   ������������                      *
*             fill      �������(1:���1;0���0)          *
***********************************************************/
void rectangle(unsigned int sad,unsigned int strhnum,unsigned char strvnum,unsigned int endhnum,unsigned char endvnum,unsigned char fill)
{
	xdata unsigned char count1;
	xdata unsigned char count2;
	xdata LCD_BUFF[240];                          /*��Ļһ�еĻ���*/ 
	xdata unsigned char stroffset;
	xdata unsigned char endoffset;
	
	xdata unsigned char flag_str;                 /*����������ʼ�е���ֵ*/
	xdata unsigned char flag_end;                 /*�������ν����е���ֵ*/ 
	
	xdata union {unsigned int add;
	struct {unsigned char addhi;unsigned char addlo;}addhalf;
	}stradd,endadd;
	
	
	if(fill==0){fill=0;}                           /*����Ҫд1����д1*/
	else{fill=0XFF;}
	
	stradd.add=strvnum*(APL)+strhnum/8+sad;        /*�����ˮƽ��ʼ��ĵ�ַ*/
	endadd.add=strvnum*(APL)+endhnum/8+sad;        /*�����ˮƽ������ĵ�ַ*/
	
	stroffset=strhnum-(strhnum/8)*8;               /*�����ˮƽ��ʼ���ַ��ڵ�ƫ����*/
	endoffset=endhnum-(endhnum/8)*8;               /*�����ˮƽ�������ַ��ڵ�ƫ����*/ 
	
	flag_str=0XFF<<(8-stroffset);               
	flag_end=0XFF>>(endoffset+1);    
	
	if(stradd.add==endadd.add)                     /*���ˮƽ����ʼ��ĵ�ַ�ͽ�����ĵ�ַ��ͬ*/
	{
		flag_str=flag_str|flag_end;
	}                /*��ʼ������ͬһ�ֽ���,ͷ��β�����ܸ�д*/
	
	
	/*+++++++++++++++��д��ʼ�е���Ļ����+++++++++++++++*/
	LCDORDER=0X46;                                 /*�趨����ַ*/
	LCDDATA=stradd.addhalf.addlo;
	LCDDATA=stradd.addhalf.addhi;                  /*ȷ������ַ*/
	
	
	LCDORDER=0X4F;                                 /*ȷ������ƶ�����Ϊ����*/
	
	LCDORDER=0X43;                                 /*׼����*/
	for(count1=0;count1<=(endvnum-strvnum);count1++)
    {LCD_BUFF[count1]=LCDORDER;} 
	
	/*+++++++++++++++������ʼ�е���Ļ����+++++++++++++++*/ 
	for(count1=0;count1<=(endvnum-strvnum);count1++) 
    {LCD_BUFF[count1]=( LCD_BUFF[count1] & flag_str ) | ( fill & (~flag_str) );}  
	/*++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	
	
	/*+++++++++++++++������ʼ�е���Ļ����+++++++++++++++*/
	LCDORDER=0X46;                                 /*�趨����ַ*/
	LCDDATA=stradd.addhalf.addlo;
	LCDDATA=stradd.addhalf.addhi;                  /*ȷ������ַ*/
	
	
	LCDORDER=0X4F;                                 /*ȷ������ƶ�����Ϊ����*/
	
	LCDORDER=0X42;                                 /*׼��д*/
	for(count1=0;count1<=(endvnum-strvnum);count1++) 
    {LCDDATA=LCD_BUFF[count1];} 
	/*+++++++++++++++�����е���Ļ���ݸ�д+++++++++++++++*/
	
	if(stradd.add<endadd.add)                      /*���ˮƽ����ʼ��ĵ�ַ�ͽ�����ĵ�ַ����ͬ*/ 
	{
		/*+++++++++++++++��д�����е���Ļ����+++++++++++++++*/
		LCDORDER=0X46;                             /*�趨����ַ*/
		LCDDATA=endadd.addhalf.addlo;
		LCDDATA=endadd.addhalf.addhi;              /*ȷ������ַ*/
		
		
		LCDORDER=0X4F;                             /*ȷ������ƶ�����Ϊ����*/
		
		LCDORDER=0X43;                             /*׼����*/
		for(count1=0;count1<=(endvnum-strvnum);count1++)
		{LCD_BUFF[count1]=LCDORDER;} 
		
		/*+++++++++++++++��������е���Ļ����+++++++++++++++*/ 
		for(count1=0;count1<=(endvnum-strvnum);count1++)
		{LCD_BUFF[count1]=( LCD_BUFF[count1] & flag_end ) | ( fill & (~flag_end) );}  
		
		/*+++++++++++++++���ؽ����е���Ļ����+++++++++++++++*/
		LCDORDER=0X46;                               /*�趨����ַ*/
		LCDDATA=endadd.addhalf.addlo;
		LCDDATA=endadd.addhalf.addhi;                /*ȷ������ַ*/
		
		
		LCDORDER=0X4F;                               /*ȷ������ƶ�����Ϊ����*/
		
		LCDORDER=0X42;                               /*׼��д*/
		for(count1=0;count1<=(endvnum-strvnum);count1++)
		{LCDDATA=LCD_BUFF[count1];}    	   
		
	}
	
	/*+++++++++++++++�м��е���Ļ���ݸ�д+++++++++++++++*/
	if((endadd.add-stradd.add)>=2 )               /*������ַ������ʼ��ַ2������,˵�����м���*/ 
	{
		stradd.add=stradd.add+1;                    /*ˮƽ��ʼ��ַ��1*/
		
		for(count2=( (strhnum/8)+1);count2<=((endhnum/8)-1);count2++)
		{
			/*+++++++++++++++�����м��е���Ļ����+++++++++++++++*/ 
			for(count1=0;count1<=(endvnum-strvnum);count1++)
			{LCD_BUFF[count1]=fill;}   
			
			/*+++++++++++++++�����м��е���Ļ����+++++++++++++++*/
			LCDORDER=0X46;                           /*�趨����ַ*/
			LCDDATA=stradd.addhalf.addlo;
			LCDDATA=stradd.addhalf.addhi;            /*ȷ������ַ*/
			
			LCDORDER=0X4F;                           /*ȷ������ƶ�����Ϊ����*/
			
			LCDORDER=0X42;                           /*׼��д*/
			for(count1=0;count1<=(endvnum-strvnum);count1++)
			{
				LCDDATA=LCD_BUFF[count1];
			}
			stradd.add=stradd.add+1;                 /*ˮƽ��ʼ��ַ��1*/
		}   
	}   
}  
//////////////////////////////ENDSED1330////////////// 
