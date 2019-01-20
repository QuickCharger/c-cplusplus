#include <iostream>
#include <map>
#include <string>

using namespace std;

enum TYPE
{
	eUNKNOWN = 1,
	eJson,
	eXML,
};

class CSpecialChar
{
public:
	CSpecialChar()
	{
		m_map['['] = ']';
		m_map['{'] = '}';
		for (auto it = m_map.begin(); it != m_map.end(); ++it)
		{
			m_str += it->first;
			m_str += it->second;
		}
	}

	bool Find(char ch)
	{
		return m_str.find(ch) != string::npos;
	}

	bool PairIncTab(char ch)
	{
		return m_map.find(ch) != m_map.end();
	}

	bool PairDecTab(char ch)
	{
		for (auto it = m_map.begin(); it != m_map.end(); ++it)
		{
			if (it->second == ch)
				return true;
		}
		return false;
	}

	char GetPair(char ch)
	{
		for (auto it = m_map.begin(); it != m_map.end(); ++it)
		{
			if (it->first == ch)
				return it->second;
			if (it->second == ch)
				return it->first;
		}
		return 0;
	}

private:
	string m_str;			// ���������ַ�
	/*
	* key ����Ҫ���tab������
	* value ����Ҫ��ȥtab������
	*/
	map<char, char> m_map;	// �����ַ������
};

void getLines(int n, string &dst)
{
	stringstream contextStream;

	do {
		getline(cin, dst);
		contextStream << dst << endl;
		dst.clear();
	} while (n--);
	dst = contextStream.str();
}

char findChar(const char &ch, const char *p)
{
	while (*p != '/0')
	{
		if (*p == ch)
			return *p;
	}
	return 0;
}

/*
* �����һ����Ч�ַ��Ƿ���Ҫ�س�
*/
bool NeedTab(const string& src, unsigned int pos, CSpecialChar &sp)
{
	for (pos; pos < src.size(); ++pos)
	{
		if (src[pos] != ' ' && sp.PairIncTab(src[pos]))
			return true;
	}
	return false;
}

/*
* �����һ����Ч�ַ���λ��
*/
int GetNextChar(const string &src, unsigned int pos)
{
	for (pos; pos < src.size(); ++pos)
	{
		/*
		* ���Կո�ͻس�
		*/
		if (src[pos] == ' ' || src[pos] == '\n')
			continue;
		else
			return pos - 1;
	}
	return pos - 1;
}

void WriteTab(string &str, int n)
{
	//newContext += 48 + n;
	for (int i = 0; i < n; ++i)
	{
		str += '\t';
	}
}

int parseType(const string &str)
{
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '{')
			return TYPE::eJson;
		else if (str[i] == '<')
			return TYPE::eXML;
	}
	return TYPE::eUNKNOWN;
}

void parseJson(const string &src, string &dst)
{
	vector<char>	vecSpecial;
	CSpecialChar	special;
	int tab = 0;

	char ch = 0;
	for (unsigned int i = 0; i < src.size(); ++i)
	{
		ch = src[i];

		/*
		* ����ҵ������ַ�
		* ����tab����
		* �ַ���ջ���ջ
		* �س� tab ���self
		*/
		if (special.Find(ch))
		{
			//WriteTab(tab);
			if (special.PairIncTab(ch))
			{
				dst += '\n';
				WriteTab(dst, tab);
				dst += ch;
				tab++;
				vecSpecial.push_back(ch);
			}
			else if (vecSpecial.size() && vecSpecial.back() == special.GetPair(ch))
			{
				tab--;
				vecSpecial.pop_back();
				dst += '\n';
				WriteTab(dst, tab);
				dst += ch;
			}
			continue;
		}
		/*
		* ȥ���п�ͷ��tab
		*/
		else if (ch == '\t' || ch == '\n' || ch == ' ')
		{
			continue;
		}
		/*
		* ע��, ֱ�Ӷ�����β
		*/
		else if (ch == '#')
		{
			dst += '\n';
			WriteTab(dst, tab);
			for (unsigned int j = i; j < src.size(); ++j)
			{
				dst += src[j];
				if (src[j] == '\n')
				{
					i = j;
					break;
				}
			}
			WriteTab(dst, tab);
			continue;
		}

		if (dst.size() &&
			(special.PairIncTab(dst.back())	// �����һ���ַ��������ַ��� �س��ո�
			|| dst.back() == ','))			// �����һ���ַ��Ƕ���, �س��ո�
		{
			dst += '\n';
			WriteTab(dst, tab);
		}
		dst += ch;
	}
}

void parseXML(const string &src, string &dst)
{
	/*
	* ��Ҫ��tag
	*/
	vector<char>	vecSpecial;
	CSpecialChar	special;
	int tab = 0;

	char ch = 0;
	for (unsigned int i = 0; i < src.size(); ++i)
	{
		ch = src[i];

		/*
		* ����ҵ������ַ�
		* ����tab����
		* �ַ���ջ���ջ
		*/
		if (special.Find(ch))
		{
			//WriteTab(tab);
			if (special.PairIncTab(ch))
			{
				dst += '\n';
				WriteTab(dst, tab);
				dst += ch;
				tab++;
				vecSpecial.push_back(ch);
			}
			else if (vecSpecial.size() && vecSpecial.back() == special.GetPair(ch))
			{
				tab--;
				vecSpecial.pop_back();
				dst += '\n';
				WriteTab(dst, tab);
				dst += ch;
			}
			continue;
		}
		/*
		* ȥ���п�ͷ��tab
		*/
		else if (ch == '\t' || ch == '\n' || ch == ' ')
		{
			continue;
		}

		if (dst.size() &&
			(special.PairIncTab(dst.back())	// �����һ���ַ��������ַ��� �س��ո�
			|| dst.back() == ','))			// �����һ���ַ��Ƕ���, �س��ո�
		{
			dst += '\n';
			WriteTab(dst, tab);
		}
		dst += ch;
	}
}

void cleanup(string &str)
{
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it == '\n')
		{
			*it = 0;
		}
		else
		{
			return;
		}
	}
	return;
}
