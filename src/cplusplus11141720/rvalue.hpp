#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>
#include <stdio.h>

using namespace std;

#include <future>

class R
{
public:
	R(const char *res) {
		printf("char* %s\n", res);
		m_ = new string(res);
	}

	R(const R& o) {
		printf("copy %s\n", o.m_->c_str());
		m_ = new string(o.m_->c_str());
	}

	R(R&& o) {
		printf("move cons %s\n", o.m_->c_str());
		m_ = o.m_;
		o.m_ = nullptr;
	}

	R& operator=(const R& o) {
		R tmp(o);
		swap(m_, tmp.m_);
		printf("assign %s\n", o.m_->c_str());
		return *this;
	}

	R& operator=(R&& o) {
		printf("move assign %s\n", o.m_->c_str());
		m_ = o.m_;
		o.m_ = nullptr;
		return *this;
	}

	~R() {
		if (m_) {
			printf("destroy %s\n", m_->c_str());
			delete m_;
		}
	}

private:
	string* m_;
};

void testCopy() {
	printf("====start testCopy()====\n");
	R r1("res1");							// char *
	R r2 = r1;								// copy		产生新的对象时，不调用赋值，调用构造。
	printf("====destroy for stack\n");
}

void testAssign()
{
	printf("====start testAssign====\n");
	R r1("res1");							// char *
	R r2("res2");							// char *
	r2 = r1;								// copy, assign		次数没有产生新对象 所以调用的是赋值。
	printf("====destroy for stack====\n");
}

void testRValue() {
	printf("====start testRValue====\n");
	R r2("res2");							// char *
	r2 = R("res1");							// char *, move		R("res1")的结果是右值，会自动改用右值赋值。
	R r3("res3");
	r2 = std::move(r3);						// move				move(arg)返回arg的右值
	printf("====destroy for stack====\n");
}

void process_value(int& i)
{
	std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int&& i)
{
	std::cout << "RValue processed: " << i << std::endl;
}

void forward_value(int&& i)
{
	process_value(i);				// 调用process_value(int& i)
	process_value(std::move(i));	// 调用process_value(int&& i)
}

void test() {
	R r1("res1");
	{
		std::move(r1);						// move(arg) 不会对arg产生任何影响，不会把arg变为右值，而是变为右值引用！！！！ 
											// 如果此处move后变为右值，则该语句块执行后，arg会自动析构，实际情况并没有。
											// 而且查看move的实现，只是cast为&&
											// &&为右值引用不为右值
	}
	std::vector<R> v;
	v.push_back(std::move(r1));				// 由于c++11的vector::push_back新增加了push_back(&&)的定义。所以调用push_back时,如果arg是&&,则自动调用push_back(&&)

	/*
	* 以下实验说明右值引用依旧是左值类型，如果想保持右值引用传递，每次调用都要使用move()!!!
	*/
	{
		forward_value(10);
	}

	/*
	*				无&&构造								有&&构造
	*	arg			调用push_back(T&),copy构造			同左侧
	*	move(arg)	调用push_back(T&&),copy构造			调用push_back(T&&),move构造
	*
	*	结论		兼容早期push_back()
	*			push_back(&&) 如果对象没有&&构造，则使用其他构造。如果有&&构造，才使用&&构造。
	*/
}

void RValueTest()
{
	testCopy();
	testAssign();
	testRValue();
	test();
}
