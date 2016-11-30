/*The MIT License (MIT)

Copyright (c) 2016 CStanKonrad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
/* ALPHA version */
#include <bits/stdc++.h>
#define WINDOWS_VERSION
#ifdef WINDOWS_VERSION
#include <windows.h>
#endif
using namespace std;
const int MAX_N = 1000;
int nwp_arr[MAX_N + 7][MAX_N + 7];
int nwp(string a, string b)
{
	for (unsigned i = 1; i <= a.size(); ++i)
	{
		for (unsigned j = 1; j <= b.size(); ++j)
		{
			if (a[i - 1] == b[j - 1])
				nwp_arr[i][j] = nwp_arr[i - 1][j - 1] + 1;
			else
				nwp_arr[i][j] = max(nwp_arr[i - 1][j], nwp_arr[i][j - 1]);
		}
	}
	return nwp_arr[a.size()][b.size()];
}

ifstream in;
string fn;

typedef vector<string> Sequence;

vector<Sequence> word;
Sequence get_next_word_pair()
{
	//cerr << "HI" << endl;
	Sequence res;
	res.push_back("");
	//bool state = 0;
	char tmp_char = -1;
	while (true)
	{
		tmp_char = in.get();
		//cerr << "proc:" << tmp_char << endl;
		if (tmp_char == '\n' || tmp_char == '\r')
		{
			while (in.peek() == '\n' || in.peek() == '\r')
				in.get();
			break;
		}
		if (tmp_char == '#')
		{
			while (in.peek() != '\n' && in.peek() != '\r')
				in.get();
			while (in.peek() == '\n' || in.peek() == '\r')
				in.get();
			res.clear();
			return get_next_word_pair();
		}
		else if (tmp_char == '	')
		{
			res.push_back("");
		}
		else
		{
			//cerr << "Adding:" << tmp_char << endl;
			res[res.size() - 1] += tmp_char;
		}
	}
	//cerr << res[0] << res[1] << endl;
	#ifdef WINDOWS_VERSION
	for (unsigned i = 0; i < res.size(); ++i)
	{
		if (res[i].size() != 0)
		CharToOem(res[i].c_str(), &res[i][0]);
	}
	#endif
	return res;
	
}
int main()
{
	srand(time(0));
	cout << "Please provide a filename:";
	getline(cin, fn);
	in.open(fn);
	if (!in.is_open())
	{
		cerr << "Can't open: " << fn << endl;
		return 0;
	}
	while (!in.eof())
	{
		word.push_back(get_next_word_pair());
	}
	cout << "Readed:" << word.size() << endl;
	string input;
	while (input != "-quit")
	{
		int i = rand()%word.size();
		cout << word[i][word[i].size() - 1] << " = ";
		getline(cin, input);
		//#ifdef WINDOWS_VERSION
		//CharToOem(input.c_str(), &input[0]);
		//#endif
		int nwp_res = nwp(input, word[i][0]);
		//cerr << nwp_res << endl;
		cout << "Matching: " << (double)nwp_res/(word[i][0].size() + input.size() - nwp_res)*100 << "$"<< endl;
		cout << "Correct answer: " << word[i][0] << " Readed: " << input << endl;
	}
	for (unsigned i = 0; i < word.size(); ++i)
	{
		cout << word[i][0] << ":" << word[i][1] << endl;
	}
	return 0;
}
