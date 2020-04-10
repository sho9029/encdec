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
		string _;
		getline(cin, _);//cin >> b での改行にgetlineが反応するため破棄
		system("cls");
		if (b == 0 || b == 1) break;
	}

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
			if (b == 0) encdec::Encryption::Text(inFilePath, outFilePath, key);
			else encdec::Encryption::Binary(inFilePath, outFilePath, key);
		}

		if (a == 1)
		{
			if (b == 0) encdec::Decryption::Text(inFilePath, outFilePath, key);
			else encdec::Decryption::Binary(inFilePath, outFilePath, key);
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
