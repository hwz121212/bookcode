#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <random>//�������
#include <chrono>//ʱ�䴦����
#include <stdexcept>//��׼�쳣��
#include <functional>//STL �������㺯���������������
#include <utility>//STL ͨ��ģ����
using namespace std;

void toSomething(promise<string> &p)
{
	try{
		cout << "read char ('x' for exception):";
		//char c = cin.get();
		char c;
		default_random_engine dre(time(NULL));
		uniform_int_distribution<int> id(0, 24);
		c = 'a' + id(dre);
		//this_thread::sleep_for(chrono::milliseconds(5000));
		if (c == 'x')
		{
			throw runtime_error(string("char ") + " read");
		}
		string s = string("char ") + c + " processed";
		//������������get()����ʱ�̻߳�ͣ�ͣ�block��ֱ��share state ��Ϊready-��promise��set_value()��set_exception()ִ�к�������,Ҳ����ζpromise���߳��Ѿ�������
		//���߳̿�����ִ����������䣬����������������Ž�����promise�ڡ�
		//�������shared state ���߳�ȷʵ����ʱ���ready-��ȷ���̵߳�local object �������������ͷ�ǰ����߳���Ӧ��ʹ��set_value_at_thread_exit() and set_exception_at_thread_exit()����ֹй¶
		p.set_value_at_thread_exit(move(s));
	}
	catch (const exception &e)
	{
		p.set_exception_at_thread_exit(current_exception());
	}
}


//Promise�ڲ��Ὠ��һ��shared state��������һ����Ӧ�����͵�ֵ����һ���쳣�����ɱ�future object ȡ�����ݵ��߳̽��
//promise�����γɳɹ���Ž�����Ž�shared state�С����Բ��ᷢ������д�Ĳ�������

int main()
{
	try{
		promise<string>p;//���̶߳���ǰ����һ��promise object��promise�ڲ��Ὠ��yһ��shared state�� ������
		//��������һ����Ӧ�����͵�ֵ����һ���쳣�����ɱ�future object ȡ�����ݵ��߳̽��
		//���promise��󱻴���һ�������߳������е�����task����
		thread t(toSomething, ref(p));//����ref() ȷ��promise��by reference(����ַ)��ʽ���ݣ�ʹ����Ա��ı䡣
		t.detach();//���̷߳������̣߳�ʹ���ں�̨����
		future<string> f(p.get_future());//����һ������ȡpromise�����future(),����promise()��ƥ���
		cout << "result: " << f.get() << endl;//��ȡ�̵߳Ľ��

	}
	catch (const exception &e)
	{
		cerr << "EXCEPTION:" << e.what() << endl;
	}
	system("pause");
	return 0;
}