#include <iostream>
#include <time.h>
#include "msgpack.hpp"

using namespace std;

#define RUN_TIMES 100000

std::array<bool, 10> vb;
std::array<int, 10> vn;
std::array<long long int, 10> vll;
std::array<std::string, 10> vstr;

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

struct T
{
	T()
	{
		m_bOptional = true;
		m_bRequired = true;
		m_nOptional = 12345678;
		m_nRequired = 12345678;
		m_llOptional = 0x123456789abcdef0;
		m_llRequired = 0x123456789abcdef0;
		m_strOptional = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		m_strRequired = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < 10; ++i)
		{
			m_bRepeated[i] = true;
			m_nRepeated[i] = 12345678;
			m_llRepeated[i] = 0x123456789abcdef0;
			m_strRepeated[i] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		}
	}

	T(const T& t)
	{
		this->m_bOptional = t.m_bOptional;
		this->m_bRequired = t.m_bRequired;
		this->m_bRepeated = t.m_bRepeated;

		this->m_nOptional = t.m_nOptional;
		this->m_nRequired = t.m_nRequired;
		this->m_nRepeated = t.m_nRepeated;

		this->m_llOptional = t.m_llOptional;
		this->m_llRequired = t.m_llRequired;
		this->m_llRepeated = t.m_llRepeated;

		this->m_strOptional = t.m_strOptional;
		this->m_strRequired = t.m_strRequired;
		this->m_strRepeated = t.m_strRepeated;
	}

	void operator =(T&& t)
	{
		std::swap(this->m_bOptional, t.m_bOptional);
		std::swap(this->m_bRequired, t.m_bRequired);
		std::swap(this->m_bRepeated, t.m_bRepeated);

		std::swap(this->m_nOptional, t.m_nOptional);
		std::swap(this->m_nRequired, t.m_nRequired);
		std::swap(this->m_nRepeated, t.m_nRepeated);

		std::swap(this->m_llOptional, t.m_llOptional);
		std::swap(this->m_llRequired, t.m_llRequired);
		std::swap(this->m_llRepeated, t.m_llRepeated);

		std::swap(this->m_strOptional, t.m_strOptional);
		std::swap(this->m_strRequired, t.m_strRequired);
		std::swap(this->m_strRepeated, t.m_strRepeated);
	}

	bool m_bOptional;
	bool m_bRequired;
	std::array<bool, 10> m_bRepeated;

	int m_nOptional;
	int m_nRequired;
	std::array<int, 10> m_nRepeated;

	long long int m_llOptional;
	long long int m_llRequired;
	std::array<long long int, 10> m_llRepeated;

	std::string m_strOptional;
	std::string m_strRequired;
	std::array<std::string, 10> m_strRepeated;

	MSGPACK_DEFINE(m_bOptional, m_bRequired, m_bRepeated, m_nOptional, m_nRequired, m_nRepeated, m_llOptional, m_llRequired, m_llRepeated, m_strOptional, m_strRequired, m_strRepeated);
};

int main()
{
	for (int i = 0; i < 10; ++i)
	{
		vb.at(i) = true;
		vn.at(i) = 12345678;
		vll.at(i) = 0x123456789abcdef0;
		vstr.at(i) = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}

	TimeRecord tr;
	tr.Init();

	int packSize = 0;
	for (int i = 0; i < RUN_TIMES; ++i)
	{
		msgpack::sbuffer buf;
		msgpack::packer<msgpack::sbuffer> p(&buf);
		p.pack_map(15);

		p.pack("bool_optional");
		p.pack(true);
		p.pack("bool_required");
		p.pack(true);
		p.pack("bool_repeated");
		p.pack(vb);

		p.pack("int_optional");
		p.pack(12345678);
		p.pack("int_required");
		p.pack(12345678);
		p.pack("int_repeated");
		p.pack(vn);

		p.pack("int64_optional");
		p.pack(0x123456789abcdef0);
		p.pack("int64_required");
		p.pack(0x123456789abcdef0);
		p.pack("int64_repeated");
		p.pack(vll);

		p.pack("string_optional");
		p.pack("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		p.pack("string_required");
		p.pack("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		p.pack("string_repeated");
		p.pack(vstr);

		msgpack::sbuffer b1;
		p.pack("t_optional");
		p.pack(T());
		msgpack::sbuffer b2;
		p.pack("t_required");
		p.pack(T());

		std::array<T, 10> vbuf;
		for (int i = 0; i < 10; ++i)
		{
			vbuf[i] = T();
		}

		p.pack("t_repeated");
		p.pack(vbuf);

		buf.data();
		packSize = buf.size();
	}

	tr.End();

	cout << "msgpack-3.2.0 size " << packSize << endl;
	cout << "cost " << tr.Diff() << " ms" << endl;

	return 0;
}
