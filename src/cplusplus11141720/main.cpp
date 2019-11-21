/*
*	c++11 参考链接
*	https://zh.wikipedia.org/wiki/C%2B%2B11
*	http://www.stroustrup.com/C++11FAQ.html
*	https://changkun.de/modern-cpp/zh-cn/02-usability/index.html		// 简单易懂
*
*	cplusplus 11 14 17 20详细功能和编译器支持度，参考如下链接
*	https://zh.cppreference.com/w/cpp/compiler_support
*	vs2015不支持c++17， 想要测试就用g++ -std=c++1z
*/

#include "../common.h"
#include "rvalue.hpp"

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

constexpr int GetFive() {
	return 5;
}

struct Foo {
	Foo() {
	}

	Foo(std::initializer_list<int> l) {
		m_v = std::move(l);
	}

	void test_initializer_list(std::initializer_list<int> l) {
		m_v = std::move(l);
	}

private:
	vector<int> m_v;
};

struct Foo_POD {
	std::string name;
	int id;
};

int main()
{
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
	* 默认模板参数
	*/
	{
		DefaultTemplateArgument<float>(1.2f, 3);
	}

	/*
	* 折叠表达式
	* https://blog.csdn.net/ding_yingzi/article/details/79973809
	* 只看懂皮毛，不写测试了
	*/

	/*
	* 3.1 右值引用和move语义
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

	/*
	* 3.2 constexpr – 泛化的常量表示式
	*/
	{
		int v[GetFive() + 11];		// 此为合法写法
	}

	/*
	* 3.3 对POD定义的修正
	*/

	/*
	* 4.1 外部模板
	*/

	/*
	* 5.1 初始化列表 
	* #include<initializer_list>
	* https://changkun.de/modern-cpp/zh-cn/02-usability/index.html#%E5%88%9D%E5%A7%8B%E5%8C%96%E5%88%97%E8%A1%A8
	* {...} 作为参数时，会自动把该参数转为initializer_list类
	*/
	{
		Foo f = { 1,2,3,4 };
		f.test_initializer_list({ 2,3,4,5 });
	}

	/*
	* 5.2 统一的初始化
	* https://blog.csdn.net/wocacaaa/article/details/25784861 通俗易懂
	* https://www.cnblogs.com/me115/p/4800777.html#h29 通俗易懂
	* 即 所有类型均可使用{}初始化
	*/
	{
		/*
		* 以下写法在类类型为POD时可编译通过，依照类中成员的出现顺序依次初始化。 是早期可编译通过的写法
		*/
		Foo_POD f{"qwer", 1};
		Foo_POD f2 = { "qwer", 1 };
	}

	/*
	* 5.3 类型推导
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
	* 5.4 基于范围的for循环
	*/
	{
		std::vector<int> v = { 1,2,3,4 };
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
	* 5.5 Lambda函数与表示式
	* lambda的捕获列表和参数列表的使用场景不同。捕获列表捕获的是上下文的环境 创建时即获取，参数列表是调用时传参。
	* https://www.cprogramming.com/c++11/c++11-lambda-closures.html    How are Lambda Closures Implemented? 该节有描述c++中lambda的实现方式
	*/
	{
		// 没啥可写的
	}

	/*
	* 5.6 返回类型后置的函数声明
	* 模板的返回类型可以自行推导了
	*/

	/*
	* 5.7 对象构造的改良
	* C++11允许构造函数调用其他构造函数
	*/

	/*
	* 5.8 显式虚函数重载
	* override 用于显式指定重写了父类的函数，必须要有完全一致的函数签名
	* final 用于显式指定 类避免被继承 或 类成员禁止被覆盖或重写
	*/

	/*
	* 5.9 空指针
	* c++11之前，NULL是(int)0。 和0有歧义。 c中NULL的类型为(void*)0
	* 新引入的nullptr类型是nullptr_t, 能隐式转换为任何指针或是成员指针的类型
	*/

	/*
	* 5.10 强类型枚举
	* 枚举的类型为类，貌似没啥用。
	*/

	/*
	* 5.11 角括号
	*/

	/*
	* 5.12 显式类型转换子
	*/

	/*
	* 5.13 模板的别名
	* 可以定义模板的别名
	* 可以定义一般类型的别名，等同typedef
	*/
	{
		TrueDarkMagic<bool> you;			// 定义模板的别名，使用using创建了新的模板

		typedef int(*process)(void*);		// 两个语句有相同的效果
		using NewProcess = int(*)(void*);
	}

	/*
	* 5.14 无限制的unions
	* 越来越混乱了
	*/

	/*
	* 6.1 可变参数模板
	* https://changkun.de/modern-cpp/zh-cn/02-usability/index.html#%E5%8F%98%E9%95%BF%E5%8F%82%E6%95%B0%E6%A8%A1%E6%9D%BF
	*/
	{
		// 没啥好写的，编译时...展开
	}

	/*
	* 6.2 新的字符串字面值
	* raw string 可以和 u8 u U 配合使用
	*/
	{
		char *p		= u8"This is a UTF-8 string";
		char16_t *p2 = u"This is a UTF-16 string";
		char32_t *p3 = U"This is a UTF-32 string";
		char *P4 = R"(This is a raw string \s )";		// "(string)" 格式
	}

	/*
	* 6.3 用户定义字面量
	*/

	/*
	* 6.4 多任务内存模型
	*/
	{
		// TODO
	}

	/*
	* 6.5 thread-local的存储期限
	* https://stackoverflow.com/questions/11983875/what-does-the-thread-local-mean-in-c11
	* thread_local变量在每个线程中都有一份自己的拷贝
	* 详看thread项目
	*/

	/*
	* 6.6 使用或禁用对象的默认函数
	*/

	/*
	* 6.7 long long int类型
	* 在32位系统上，一个long long int是保有至少64个有效比特的整数类别
	*/

	/*
	* 6.8 静态assertion
	*/

	/*
	* 6.9 允许sizeof运算符作用在类别的数据成员上，无须明确的对象
	*/

	/*
	* 6.10 垃圾回收机制
	*/

	/*
	* 7.1 标准库组件上的升级
	*/

	/*
	* 7.2 线程支持
	*/
	{
		/*
		* 锁 std::mutex，std::recursive_mutex
		* RAII机制 std::lock_guard和std::unique_lock
		* std::async
		* TODO
		*/
	}

	/*
	* 7.3 多元组类型
	* 多元组可被视为是struct其数据成员的一般化
	* 对传参和返回值有便利
	*/

	/*
	* 7.4 散列表
	*/

	/*
	* 7.5 正则表达式
	*/

	/*
	* 7.6 通用智能指针
	* shared_ptr
	* unique_ptr
	* weak_ptr
	* TODO
	*/

	/*
	* 7.7 可扩展的随机数功能
	* https://zh.cppreference.com/w/cpp/numeric/random
	*/
	{
		std::random_device rd;
		unsigned int i = rd();

		uniform_int_distribution<unsigned> u(0, 9);
		std::default_random_engine rd2;
		auto generator = std::bind(u, rd2);
		unsigned int i2 = generator();
	}

	/*
	* 7.8 包装引用
	* 使代码越发的混乱， 最好别用
	*/

	/*
	* 7.9 多态函数对象包装器
	* 即 function模板
	*/
	{
		std::function<int(int, int)> func;
		func = [](int, int)->int { return 1; };
		if (func)
		{
			cout << func(1,2) << endl;
		}
	}

	/*
	* 7.10 用于元编程的类型属性
	* 此种编程技巧能写出优美、简洁的代码；然而调试是此种编程技巧的弱处：编译期的错误消息让人不知所云，运行期的调试更是困难。
	*/

	/*
	* 7.11 用于计算函数对象回返类型的统一方法
	*/

	/*
	* 7.12 iota 函数
	*/

	/*
	* if/switch变量声明强化
	*/
	{
#ifndef WIN32
		if (bool b = true; false)		// false, g++17可编译过
		{
			cout << "true" << endl;
		}
#endif

		if (true, false)				// false
		{
			cout << "true" << endl;
		}
	}

	/*
	* sleep_for()是c++11引进的标准sleep方法，可以做到时间精确控制。之前的Sleep()是winAPI
	*/
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));		//sleep for 100 ms. Can be use in both windows and Unix environment
	}

	getchar();
}
