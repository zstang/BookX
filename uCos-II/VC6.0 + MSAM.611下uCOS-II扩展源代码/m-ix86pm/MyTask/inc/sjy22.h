/* $Id: sjy22.h,v 1.1 2002/02/06 02:17:11 linfusheng Exp $
 */
#ifndef SJY22_H
#define SJY22_H

#define	F206_RAM_SIZE		4064	// F206 BCA���鳤��

#define	cmdLCD_RESET		0xe0   	//
#define	cmdLCD_HORIZONTAL	0xe1   	//
#define	cmdLCD_VERTICAL		0xe2   	//
#define	cmdLCD_UPDATA		0xe3   	//
#define	cmdLCD_CPMEMORY		0xe4   	//

/* function code */
#define	cmdINIT_CARD		0x00   	//���ܿ���ʼ������dspResetCard()
#define cmdGET_CARD		0x01   	//��ñ��ܿ���һ������Ϣ(�����)
#define	cmdGET_LOG	       	0x02   	//��ñ��ܿ��������־��Ϣ
#define	cmdGET_LOGNUM     	0x03   	//��ñ��ܿ��������־��Ϣ
#define	cmdCLR_LOG	       	0x04   	//������ܿ��������־��Ϣ
#define	cmdSET_TIME		0x05   	//���ñ��ܿ��ڲ�ʱ��
#define	cmdGET_TIME		0x06   	//��ñ��ܿ��ڲ�ʱ��

#define	cmdHAV_ICHEAD		0x2a   	//�Ƿ����IC��
#define	cmdSHK_IC		0x2b   	//����IC�����д��������ͨ��
#define	cmdWRT_ICHEAD		0x20   	//�ƿ�ʱд��IC����ͷ����Ϣ
#define	cmdWRT_ICKK		0x21   	//дKK����Կ����	dspWriteKKToKeyCard()
#define	cmdWRT_ICMKT		0x22   	//дMKT����Կ����	dspWriteMKTToKeyCard()
#define	cmdWRT_ICUSR		0x23   	//д�û���Ϣ������Ա��
#define	cmdCLR_IC	        0x24	//���IC������������	dspClearICCard()
#define	cmdGET_ICHEAD		0x25	//���IC��ͷ����Ϣ
#define	cmdGET_USRNUM	   	0x26	//ȡ���ܿ�����Ч�û���Ŀ
#define	cmdGET_USRPIN		0x27 	//ȡ���ܿ���ĳ���û���Ϣ
#define	cmdAUT_USRPIN		0x28 	//��֤��ݿ�������Ƿ�ϸ�
#define	cmdCLR_USRPIN		0x29 	//������ܿ���ĳ���û���Ϣ

#define	cmdINIT_KP1	      	0x40  	//��ʼ������Կ	dspInitKP1()
#define	cmdWRT_KK	      	0x41  	//д��KK�㷨	dspWriteKKToCard
#define	cmdWRT_MKT		0x42  	//д��MKT�㷨	dspWriteMKTToCard()
#define	cmdCHG_KK	      	0x43  	//ͨ��SMC�Զ�����KK
#define	cmdREC_MKT		0x44  	//��SMC�����µĶ˶���Կ����
#define	cmdCHG_MKT		0x45  	//�����µĶ˶���Կ����dspEnabledNewMKT()
#define	cmdSTOP_CARD		0x46  	//ͨ��SMC�Զ����ٱ��ܿ�dspStopSecurityCard()

#define	cmdENC_INIT	      	0x60 	//�ӽ����㷨��ʼ��(��Կ�ڿ���)
#define	cmdENC_INITSTR		0x61 	//�������㷨���ܳ�ʼ��(��Կ�ڿ���)
#define	cmdDEC_INITSTR		0x67 	//�������㷨���ܳ�ʼ��(��Կ�ڿ���)
#define	cmdENC_INITKEY		0x62 	//�ӽ����㷨��ʼ������Կ��Ӧ�ó������룩
#define	cmdENC_INITKP		0x69 	//�ӽ����㷨��ʼ����ʹ������Կ��
#define	cmdENC_INITKK		0x6a 	//�ӽ����㷨��ʼ����ʹ����Կ������Կ��

#define	cmdBCA_UPD		0x63 	//����128�ӽ����㷨 dspBCAUpdate()
#define	cmdHASH_UPD		0x64 	//Hash��֤����㺯��dspHashUpdate()
#define	cmdSTR_UPD	      	0x66 	//����������㷨 dspStreamUpdate()
#define	cmdBCA_FIN		0x68 	//����128�ӽ��ܽ����㷨 dspBCAFinal()
#define	cmdHASH_FIN		0x65 	//���������֤�� dspHashFinal()
#define	cmdSTR_FIN	      	0x69 	//�����������㷨 dspStreamFinal()

#define	cmdGEN_RND		0x80 	//�������ⳤ�������bscGenerateRandom()
#define	cmdGEN_RNDBCA		0x81 	//�������ⳤ�ĸ������������

#define		BCAIIE_CMD 	0x01	// 128λBCAII����
#define		BCAIID_CMD 	0x08	// 128λBCAII����
#define		HASH_CMD   	0x45	// 128λHASH��֤
#define		STREAM_CMD 	0x00	// 128�������㷨

#define		BCA64E_CMD 	0x07	// 64λBCAII����
#define		BCA64D_CMD 	0x03	// 64λBCAII����
#define		HASH64_CMD  	0x47	// 64λHASH��֤
#define		STREAM64_CMD 	0x00	// 64�������㷨

#define		BCAIIIE_CMD 	0xa0	// 128λBCAIII����
#define		BCAIIID_CMD 	0xa1	// 128λBCAIII����

#define		KSLENGTH 	16	/*�Ự��Կ���� */
#define		MACLENGTH 	16	/*�Ự��Կ���� */

#define		CARD_READY	6
#define		CARD_BAD	4
#define		CARD_BUSY	8

#define		CARD_NUM	2 	/* card number is 2 */


/* We sugguest that, the inputlen is align 8 , and key is 128 bit length */
extern int  SJY22_encrypt(unsigned char *input,int inputlen,unsigned char *output,unsigned char *keybyte,int keylen,unsigned char *iv,int ivlen);

extern int SJY22_decrypt(unsigned char *input,int inputlen,unsigned char *output,unsigned char *keybyte,int keylen,unsigned char *iv,int ivlen);



extern void SJY22_hash_Init (void *ctx);
extern void SJY22_hash_Update(void *ctx, unsigned char *input, unsigned int inputlen);
extern void SJY22_hash_Final(unsigned char output[16], void *ctx);

#endif
