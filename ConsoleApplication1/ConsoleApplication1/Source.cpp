#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char** alphabet();
string encrypt(const string& text, const string& key);
string decrypt(const string& text, const string& key);
void destroy(char** alphabet);
void convert_to_lower(string& text, bool letter_case[]);
void revert(string& text, bool letter_case[]);

int main()
{
	string text, key;
	do
	{
		cout << "Podaj tekst do zaszyfrowania: ";
		cin >> text;
		cout << "Podaj klucz (przynamniej = " << text.length() << " znakow) : ";
		cin >> key;
	}
	while (key.length() < text.length()); 

	bool *letter_case = new bool[text.length()];
	bool *letter_case_key = new bool[key.length()];
	
	convert_to_lower(text, letter_case);
	convert_to_lower(key, letter_case_key);
	text = encrypt(text, key);
	revert(text, letter_case);
	revert(key, letter_case_key);
	cout << "Zaszyfrowany tekst: " << text << endl;

	delete[] letter_case;
	delete[] letter_case_key;
	
	do
	{
		cout << "Podaj tekst do odszyfrowania: ";
		cin >> text;
		cout << "Podaj klucz (przynamniej = " << text.length() << " znakow) : ";
		cin >> key;
	} while (key.length() < text.length());
	
	letter_case = new bool[text.length()];
	letter_case_key = new bool[key.length()];

	convert_to_lower(text, letter_case);
	convert_to_lower(key, letter_case_key);
	text = decrypt(text, key);
	revert(text, letter_case);
	revert(key, letter_case_key);
	cout << "Odszyfrowany tekst: " << text << endl;

	delete[] letter_case;
	delete[] letter_case_key;
}

char** create_alphabet()
{
	char **alphabet = new char*['z' + 1];
	for (unsigned int i = 'a'; i <= 'z'; ++i)
	{
		alphabet[i] = new char['z' + 1];
	}

	for (char ch = 'a'; ch <= 'z'; ++ch)
	{
		char character = ch;
		for (unsigned int i = 'a'; i <= 'z'; ++i)
		{
			if (character == 'z' + 1)
			{
				character = 'a';
			}
			alphabet[ch][i] = character;
			++character;
		}
	}
	return alphabet;
}

string encrypt(const string& text, const string& key)
{
	char **alphabet = create_alphabet();
	string result;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		result.push_back(alphabet[text[i]][key[i]]);
	}
	destroy(alphabet);
	return result;
}

string decrypt(const string& text, const string& key)
{
	char **alphabet = create_alphabet();
	string result;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		if (text[i] != ' ')
		{
			for (unsigned int ch = 'a'; ch <= 'z'; ++ch)
			{
				if (text[i] == alphabet[key[i]][ch])
				{
					result.push_back(alphabet['a'][ch]);
				}
			}
		}
	}
	destroy(alphabet);
	return result;
}

void destroy(char** alphabet)
{
	for (unsigned int i = 'a'; i <= 'z'; ++i)
	{
		delete[] alphabet[i];
	}
	delete[] alphabet;
}

void convert_to_lower(string& text, bool letter_case[])
{
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		letter_case[i] = isupper(text[i]);
		char ch = tolower(text[i]);
		text[i] = ch;
	}
}

void revert(string& text, bool letter_case[])
{
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		if (letter_case[i])
		{
			char ch = text[i]; 
			text[i] = toupper(ch);
		}
	}
}