#include <iostream>
#include <time.h>
#include "msg.pb.h"

using namespace std;

#define RUN_TIMES 100000

class TimeRecord
{
public:
	void Init()
	{
		begin = clock();
	}

	void End()
	{
		end = clock();
	}

	clock_t Diff()
	{
		return end - begin;
	}

private:
	clock_t begin = 0;
	clock_t end = 0;
};

void modifyT(MSG::T& t)
{
	t.set_bool_optional(true);
	t.set_bool_required(true);
	for (int i = 0; i < 10; ++i)
		t.add_bool_repeated(true);

	t.set_int_optional(12345678);
	t.set_int_required(12345678);
	for (int i = 0; i < 10; ++i)
		t.add_int_repeated(12345678);

	t.set_int64_optional(0x123456789abcdef0);
	t.set_int64_required(0x123456789abcdef0);
	for (int i = 0; i < 10; ++i)
		t.add_int64_repeated(0x123456789abcdef0);

	t.set_string_optional("1234567890cabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	t.set_string_required("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	for (int i = 0; i < 10; ++i)
		t.set_string_optional("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

int main()
{
	TimeRecord tr;
	tr.Init();

	int packSize = 0;
	for (int i = 0; i < RUN_TIMES; ++i)
	{
		MSG msg;
		msg.set_bool_optional(true);
		msg.set_bool_required(true);
		for (int i = 0; i < 10; ++i)
			msg.add_bool_repeated(true);

		msg.set_int_optional(12345678);
		msg.set_int_required(12345678);
		for (int i = 0; i < 10; ++i)
			msg.add_int_repeated(12345678);

		msg.set_int64_optional(0x123456789abcdef0);
		msg.set_int64_required(0x123456789abcdef0);
		for (int i = 0; i < 10; ++i)
			msg.add_int64_repeated(0x123456789abcdef0);

		msg.set_string_optional("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		msg.set_string_required("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		for (int i = 0; i < 10; ++i)
			msg.set_string_optional("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

		MSG::T* t = msg.mutable_t_optional();
		modifyT(*t);

		MSG::T* t2 = msg.mutable_t_required();
		modifyT(*t2);

		for (int i = 0; i < 10; ++i)
		{
			MSG::T* t = msg.add_t_repeated();
			modifyT(*t);
		}

		std::string&& str = msg.SerializeAsString();
		packSize = str.size();
	}

	tr.End();

	cout << "protobuf_2.6.1 size " << packSize << endl;
	cout << "cost " << tr.Diff() << " ms" << endl;

	return 0;
}
