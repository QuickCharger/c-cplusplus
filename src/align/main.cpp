/*
* c++�Ķ��� �������ĵģ�û������ô���ĵ�
* �ܽ᣺
*	��ȡmax_align �Ŀӣ�
		char[n] ����ֵ����Ӱ��max_align, ռ�ÿռ�Ϊ4*(n/4)
	vptrռ�õĿռ����max_align, ������ж���Ŀռ�, �˿ռ䲻�����ʣ�±����Ķ���. �μ�A3
*/

#include <iostream>

using namespace std;

class A1 {
	virtual void func() {};		// 4
};

class A2 {
	virtual void func() {};		// vptr ռ��8
	long long ll;
};

class A3 {
	virtual void func() {};		// vptr ռ��8 �����µ�4û�б�i1ռ��
	int i1;
	long long ll;
};

/*
* char[] �Ķ����С����ı�������ֵ
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
