// Thread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <future>
#include <vector>
#include <iostream>
using namespace std;

struct result {
	vector<double> x;
	double y;
};

void f1(promise<result> &res)
{
	vector<double> vec(2);
	vec[0] = 1.5;
	vec[1] = 2.2;
	res.set_value({ vec, 4.7 });
}

double f2(double x)
{
	return sin(x);
}

int _tmain(int argc, _TCHAR* argv[])
{
	promise<result> res1;
	packaged_task<double(double)> res2(f2);
	future<result> ft1 = res1.get_future();
	future<double> ft2 = res2.get_future();
	thread th1(f1, ref(res1));
	thread th2(move(res2), 3.14/6);

	ft1.wait();
	ft2.wait();
	assert(ft1._Is_ready() && ft2._Is_ready());

	result r1 = ft1.get();
	double r2 = ft2.get();

	th1.join();
	th2.join();

	cout << "result: x = (" << r1.x[0] << ", " << r1.x[1] << "), y = " << r1.y << endl;
	cout << "sin(pi/6) = " << r2 << endl;
	system("pause");
	return 0;
}

