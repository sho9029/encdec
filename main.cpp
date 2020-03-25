#include "pch.h"
#include "encdec.h"

int main()
{
	int a, b;
	string str;

	while (1)
	{
		cout << "暗号化 = 0 複合 = 1" << endl;
		cin >> a;

		system("cls");
		if (a == 0 || a == 1) break;
	}

	if (a == 0) str = "暗号化";
	else str = "復号";

	while (1)
	{
		cout << str << "\n\nテキストファイル = 0 バイナリファイル = 1" << endl;
		cin >> b;

		system("cls");
		if (b == 0 || b == 1) break;
	}

	string inFilePath, outFilePath, Key;
	cout << str << "するファイルパス > ";
	cin >> inFilePath;
	cout << "出力するファイルパス > ";
	cin >> outFilePath;
	cout << str << "キー > ";
	cin >> Key;

	try
	{
		if (a == 0)
		{
			if (b == 0) encdec::Encryption::Text(inFilePath, outFilePath, Key);
			else encdec::Encryption::Binary(inFilePath, outFilePath, Key);
		}

		if (a == 1)
		{
			if (b == 0) encdec::Decryption::Text(inFilePath, outFilePath, Key);
			else encdec::Decryption::Binary(inFilePath, outFilePath, Key);
		}
	}
	catch (exception & e)
	{
		cout << endl << e.what();
		system("pause");
		return -1;
	}

	cout << str << "が終了しました";
	system("pause");
	return 0;
}
