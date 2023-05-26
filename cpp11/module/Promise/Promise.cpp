#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <random>//随机数类
#include <chrono>//时间处理类
#include <stdexcept>//标准异常类
#include <functional>//STL 定义运算函数（代替运算符）
#include <utility>//STL 通用模板类
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
		//在主函数调用get()方法时线程会停滞（block）直到share state 成为ready-当promise的set_value()或set_exception()执行后便是如此,也不意味promise的线程已经结束；
		//该线程可能仍执行着其他语句，甚至储存其他结果放进其他promise内。
		//如果想令shared state 在线程确实结束时变成ready-以确保线程的local object 及其他材料在释放前清除线程你应该使用set_value_at_thread_exit() and set_exception_at_thread_exit()，防止泄露
		p.set_value_at_thread_exit(move(s));
	}
	catch (const exception &e)
	{
		p.set_exception_at_thread_exit(current_exception());
	}
}


//Promise内部会建立一个shared state是用来放一个相应的类型的值或是一个异常，并可被future object 取其数据当线程结果
//promise是在形成成果后才将结果放进shared state中。所以不会发生读和写的并发操作

int main()
{
	try{
		promise<string>p;//在线程定义前定义一个promise object。promise内部会建立y一个shared state， 在这里
		//是用来放一个相应的类型的值或是一个异常，并可被future object 取其数据当线程结果
		//这个promise随后被传给一个分离线程中运行的任务（task）：
		thread t(toSomething, ref(p));//借由ref() 确保promise以by reference(传地址)方式传递，使其可以被改变。
		t.detach();//将线程分离主线程，使其在后台运行
		future<string> f(p.get_future());//定义一个用来取promise结果的future(),它与promise()是匹配的
		cout << "result: " << f.get() << endl;//获取线程的结果

	}
	catch (const exception &e)
	{
		cerr << "EXCEPTION:" << e.what() << endl;
	}
	system("pause");
	return 0;
}