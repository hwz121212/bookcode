#include <ostream>
#include <iostream>
#include <fstream>
#include "stdio.h"
using namespace std;


void HeaderBegin(const char *inTitle)//������ҳ����
{
	cout<<"Content Type:TEXT/HTML\n\n"<<"<HTML><HEAD><TITLE>\n"<<inTitle<<"\n</TITLE></HEAD><BODY>\n";

}
void HeaderEnd()
{
	cout<<"</BODY></HTML>\n";

}
void main()
{
	HeaderBegin("��ҳ���⣺ʹ��C++����CGI���������");
	cout<<"<H1>ע��CGI�������������</H1>";//�������
	HeaderEnd();
}