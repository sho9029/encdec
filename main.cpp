#include "pch.h"
#include "encdec.h"

enum selectPos
{
    up,
    down
};

int main()
{
    string mode;
    int pos = up;

    cout << "暗号化 <\n復号    ";

    while (1)
    {
        if (GetAsyncKeyState(VK_RETURN)) break;
        if (GetAsyncKeyState(VK_UP) && pos == down)
        {
            system("cls");
            cout << "暗号化 <\n復号    ";
            pos = up;
        }
        else if (GetAsyncKeyState(VK_DOWN) && pos == up)
        {
            system("cls");
            cout << "暗号化\n復号   <";
            pos = down;
        }
    }

    if (pos == up) mode = "暗号化";
    else mode = "復号";

    string inFilePath, outFilePath, key, _;
    getline(cin, _);
    cout << endl << mode << "するファイルパス > ";
    getline(cin, inFilePath);
    cout << "出力するファイルパス > ";
    getline(cin, outFilePath);
    cout << mode << "キー > ";
    cin >> key;

    try
    {
        encdec::Convert(inFilePath, outFilePath, key);
    }
    catch (exception & e)
    {
        cout << endl << e.what();
        system("pause");
        return -1;
    }

    cout << endl << mode << "が終了しました" << endl;
    system("pause");
    return 0;
}
