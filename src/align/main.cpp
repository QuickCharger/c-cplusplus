/*
* c++的对齐 见过恶心的，没见过这么恶心的
* 总结：
*	获取max_align 的坑：
		char[n] 此类值不会影响max_align, 占用空间为4*(n/4)
	vptr占用的空间等于max_align, 但如果有多余的空间, 此空间不会参与剩下变量的对齐. 参见A3
*/

#include <iostream>

using namespace std;

class A1 {
	virtual void func() {};		// 4
};

class A2 {
	virtual void func() {};		// vptr 占用8
	long long ll;
};

class A3 {
	virtual void func() {};		// vptr 占用8 但余下的4没有被i1占用
	int i1;
	long long ll;
};

/*
* char[] 的对齐大小不会改变最大对齐值
*/
class B {
	virtual void func() {}		// 4
	char ch[5];					// 8
	int i1;						// 4
	short c;					// 4
};

class C {
	virtual void func() {};
	int i3;
	int i4;
	long long ll;
	char ch[5];
	int i1;
	int i2;
	char b;
};

#define SIZEOF(T) cout << "sizeof(" << #T  << "): "<<  sizeof(T) << endl;

int main()
{
	SIZEOF(A1);
	SIZEOF(A2);
	SIZEOF(A3);

	SIZEOF(B);

	cout << "over" << std::endl;
	getchar();

	return 0;
}
