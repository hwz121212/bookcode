
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;

void test(int i, double d, const string &s)
{
	cout << "i= " << i << " d= " << d << " s= " << s << endl;
}
int test1(int i, double d, const string &s)
{
	cout << "i= " << i << " d= " << d << " s= " << s << endl;
	return i;
}

int main(int argc, const char *argv[])
{
	function<void(void)> fp;
	string s = "foo";
	int a = 3;
	double b = 6.7;
	fp = bind(&test, a, b, s);
	fp();

	function <void(int, const string&)> fp1;
	double b2 = 4.6;
	fp1 = bind(test, _1, b2, _2);
	fp1(4, "kity");

	function <int(int, const string&) > fp2;
	fp2 = bind<int>(test1, _1, b2, _2);
	int  y = fp2(4, "kity");
	cout << y << endl;

	auto fn = bind(test, 10, 23.3, "heko");//不用function指定函数参数，
	fn();

	auto ff = bind(test, _1, _3, _2);//bind中的i参数类型与test的_j的参数类型对应
	ff(12, "ppp", 12.5);

	class A
	{
	public:
		void print(int a, double x)
		{
			cout << a << " " << x << endl;
		}
	};
	A a3;
	auto fclass = bind(&A::print, &a3, 11, 7.7);
	fclass();
	return 0;
}
