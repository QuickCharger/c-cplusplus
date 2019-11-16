/*
*	c++11 参考链接
*	https://zh.wikipedia.org/wiki/C%2B%2B11
*	http://www.stroustrup.com/C++11FAQ.html
*
*	cplusplus 11 14 17 20详细功能和编译器支持度，参考如下链接
*	https://zh.cppreference.com/w/cpp/compiler_support
*	vs2015不支持c++17， 想要测试就用g++ -std=c++1z
*/

#include "../common.h"
#include "rvalue.hpp"

struct Foo {
	Foo(std::initializer_list<int> l)
	{
		m_v = std::move(l);
	}

	void test_initializer_list(std::initializer_list<int> l)
	{
		m_v = std::move(l);
	}

private:
	vector<int> m_v;
};

std::tuple<int, double, std::string> TestTuple()
{
	return std::make_tuple(1, 2.3, "456");
};

template<typename T, typename U>
class MagicType {
public:
	T dark;
	U magic;
};

template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

template<typename T = int, typename U = int>
auto DefaultTemplateArgument(T x, U y) -> decltype(x + y) {
	return x + y;
}

int main()
{
	/*
	* if/switch变量声明强化
	* todo
	*/


	/*
	* 初始化列表 initializer_list #include<initializer_list>
	*	https://changkun.de/modern-cpp/zh-cn/02-usability/index.html#%E5%88%9D%E5%A7%8B%E5%8C%96%E5%88%97%E8%A1%A8
	*	{...} 作为参数时，会自动把该参数转为initializer_list类
	*/
	{
		Foo f{ 1,2,3,4 };
		f.test_initializer_list({ 2,3,4,5 });
	}

	/*
	* tuple, tie, 结构化绑定 #include<typel>
	*	https://zh.cppreference.com/w/cpp/utility/tuple
	*/
#ifndef WIN32
	{
		auto[x, y, z] = TestTuple();		// 结构化绑定在vs2015中不可用
		cout << "x=" << x << ". y=" << y << ". z=" << z << endl;
	}
#endif

	/*
	* auto decltype
	* auto就不说了
	* decltype 返回操作数的数据类型，在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。
	* decltype 有坑. decltype会保留 const 指针 引用 的属性. 对指针进行解指针时要特别注意
	*/
	{
		int i = 10;
		decltype(i) ii = 11;			// 类型为int. 依据i的类型创建ii

		const int constI = 1;
		decltype(constI) constII = 2;	// 类型为const int. decltype会保留推断中的const， auto则不会!!!


		const int *ptrConstI = nullptr;
		decltype(ptrConstI) ptrConstII = nullptr;	// 类型为const int *. decltype会保留推断中的const 和 *， auto则不会!!!

		int &refI = i;
		decltype(refI) refII = i;		// 类型为int&. decltype会保留推断中的引用!!!
		decltype((i)) refIII = i;		// 双层括号表示引用!!!

		const int &constRefI = i;
		decltype(constRefI) constRefII = i;	// 类型为const int&. decltype会保留推断中的引用 和 const!!!
		decltype((constI)) constRefIII = i;	// 双层括号表示引用!!!

		int* pI = &i;
		decltype(pI) pII = nullptr;		// 类型为int*. decltype会保留推断中的指针!!!
		decltype(*pI) refIIII = i;		// 类型为int&. 表达式内容为解引用操作,类型为 int& ！！！！！！！！！
	}

	/*
	* for迭代
	*/
	{
		std::vector<int> v = { 1,2,3,4 };
		cout << "before: ";
		for (auto it : v)		// read only
			std::cout << it;
		for (auto &it : v)		// writeable
			it += 1;
		cout << endl << "after: ";
		for (auto it : v)		// read only
			std::cout << it;
		cout << endl;
	}

	/*
	* using 为了解决不能typedef模板的问题
	*/
	{
		typedef int(*process)(void*);		// 两个语句有相同的效果
		using NewProcess = int(*)(void*);

		TrueDarkMagic<bool> you;
	}

	/*
	* 默认模板参数
	*/
	{
		DefaultTemplateArgument<float>(1.2f, 3);
	}

	/*
	* 变长参数模板
	* https://changkun.de/modern-cpp/zh-cn/02-usability/index.html#%E5%8F%98%E9%95%BF%E5%8F%82%E6%95%B0%E6%A8%A1%E6%9D%BF
	* 没啥好写的
	*/

	/*
	* 折叠表达式
	* https://blog.csdn.net/ding_yingzi/article/details/79973809
	* 只看懂皮毛，不写测试了
	*/

	/*
	* lambda
	* lambda的捕获列表和参数列表的使用场景不同。捕获列表捕获的是上下文的环境 创建时即获取，参数列表是调用时传参。
	* https://www.cprogramming.com/c++11/c++11-lambda-closures.html    How are Lambda Closures Implemented? 该节有描述c++中lambda的实现方式
	*/

	/*
	* 右值引用 和 move
	* 这个文章写的明白易懂
	* https://juejin.im/post/59c3932d6fb9a00a4b0c4f5b
	* https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/index.html
	*
	* 表面上看只是增加了一个引用符号，但它对 C++ 软件设计和类库的设计有非常大的影响。
	* 它既能简化代码，又能提高程序运行效率。每一个 C++ 软件设计师和程序员都应该理解并能够应用它。
	* 我们在设计类的时候如果有动态申请的资源，也应该设计转移构造函数和转移拷贝函数。
	* 在设计类库时，还应该考虑 std::move 的使用场景并积极使用它。
	*/
	RValueTest();

	getchar();
}
