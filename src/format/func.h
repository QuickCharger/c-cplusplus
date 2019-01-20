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
	string m_str;			// 所有特殊字符
	/*
	* key 是需要添加tab数量的
	* value 是需要减去tab数量的
	*/
	map<char, char> m_map;	// 特殊字符的配对
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
* 检测下一个有效字符是否需要回车
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
* 获得下一个有效字符的位置
*/
int GetNextChar(const string &src, unsigned int pos)
{
	for (pos; pos < src.size(); ++pos)
	{
		/*
		* 忽略空格和回车
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
		* 如果找到特殊字符
		* 计算tab数量
		* 字符入栈或出栈
		* 回车 tab 输出self
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
		* 去掉行开头的tab
		*/
		else if (ch == '\t' || ch == '\n' || ch == ' ')
		{
			continue;
		}
		/*
		* 注释, 直接读到行尾
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
			(special.PairIncTab(dst.back())	// 如果上一个字符是特殊字符， 回车空格
			|| dst.back() == ','))			// 如果上一个字符是逗号, 回车空格
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
	* 需要找tag
	*/
	vector<char>	vecSpecial;
	CSpecialChar	special;
	int tab = 0;

	char ch = 0;
	for (unsigned int i = 0; i < src.size(); ++i)
	{
		ch = src[i];

		/*
		* 如果找到特殊字符
		* 计算tab数量
		* 字符入栈或出栈
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
		* 去掉行开头的tab
		*/
		else if (ch == '\t' || ch == '\n' || ch == ' ')
		{
			continue;
		}

		if (dst.size() &&
			(special.PairIncTab(dst.back())	// 如果上一个字符是特殊字符， 回车空格
			|| dst.back() == ','))			// 如果上一个字符是逗号, 回车空格
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
