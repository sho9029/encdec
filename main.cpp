#include "pch.h"
#include "encdec.h"

int main()
{
	int a;
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

	string inFilePath, outFilePath, key;
	cout << str << "するファイルパス > ";
	getline(cin, inFilePath);
	cout << "出力するファイルパス > ";
	getline(cin, outFilePath);
	cout << str << "キー > ";
	cin >> key;

	try
	{
		if (a == 0)
		{
			encdec::Encryption::Binary(inFilePath, outFilePath, key);
		}

		if (a == 1)
		{
			encdec::Decryption::Binary(inFilePath, outFilePath, key);
		}
	}
	catch (exception & e)
	{
		cout << endl << e.what();
		system("pause");
		return -1;
	}

	cout << endl << str << "が終了しました" << endl;
	system("pause");
	return 0;
}
