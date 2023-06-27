
#ifndef _ENC_DEC_HEADER_
#define _ENC_DEC_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

/** Structure used for encoder instance creation */
typedef struct	{
	int width;				//����ͼ����
	int height;				//����ͼ��߶�
	int max_key_interval;	//�ؼ�֡���
	int framerate;			//����֡��
	int quant;				//��������
	int bitrate;			//������С��ʵ��CBR
	void *handle;			//���������
} ENC_PARAM;

///////////////////////////////////////////////////////////////////////////
int enc_init(ENC_PARAM *enc_param);		//����������
int enc_stop();							//���ٱ�����
int enc_main(unsigned char *image,		//����ͼ��ָ��
			 unsigned char *bitstream,	//���������ָ��
			 int *key,					//�ؼ�֡��־
			 int *stats_type,			//��������
			 int *stats_quant,			//��������
			 int *stats_length);		//�����������С

////////////////////////////////////////////////////////////////////////////
int dec_init(int width, int height);	//����������
int dec_stop();							//���ٽ�����
int dec_main(unsigned char *istream,	//����ָ��
			unsigned char *ostream,		//����ͼ���ָ��
			int istream_size,			//��������
			int width);					//ͼ����

////////////////////////////////////////////////////////////////////////////

void SwapBitmap(unsigned char *pInBuf, unsigned char *pOutBuf, int nPicType);

#ifdef __cplusplus
}
#endif


#endif

