#include <ostream>
#include <iostream>
#include <fstream>
#include "stdio.h"
using namespace std;


void HeaderBegin(const char *inTitle)//设置网页标题
{
	cout<<"Content Type:TEXT/HTML\n\n"<<"<HTML><HEAD><TITLE>\n"<<inTitle<<"\n</TITLE></HEAD><BODY>\n";

}
void HeaderEnd()
{
	cout<<"</BODY></HTML>\n";

}
void main()
{
	HeaderBegin("网页标题：使用C++开发CGI服务端例程");
	cout<<"<H1>注意CGI的输入输出方法</H1>";//输出正文
	HeaderEnd();
}