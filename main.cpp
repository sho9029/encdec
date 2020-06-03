#include "pch.h"
#include "encdec.h"

enum selectPos
{
    up,
    down
};

enum area
{
    area_i,
    area_o,
    area_k
};

int main(int argc, char **argv)
{
    string inFilePath, outFilePath, key, _;
    vector<string> args(argv, argv + argc);
    int pos = up;

    if (argc == 2 && (argv[1] == "--help" || argv[1] == "help" || argv[1] == "?"))
    {
        cout << "\nUsage: encdec.exe [-i input file path] [-o output file path] [-k key]"
                "\n\nor run without arguments";
    }
    else if (argc >= 7)
    {
        int area = -1;
        bool space = false;

        struct requirements
        {
            bool inFilePath = false;
            bool outFilePath = false;
            bool key = false;
        }req;

        for (size_t i = 1; i < argc; ++i)
        {
            if (args[i] == "-i")
            {
                space = false;
                area = area_i;
                req.inFilePath = true;
            }
            else if (args[i] == "-o")
            {
                space = false;
                area = area_o;
                req.outFilePath = true;
            }
            else if (args[i] == "-k")
            {
                space = false;
                area = area_k;
                req.key = true;
            }
            else
            {
                switch (area)
                {
                case area_i:
                    inFilePath = (space ? " " : "");
                    inFilePath += args[i];
                    break;
                case area_o:
                    outFilePath = (space ? " " : "");
                    outFilePath += args[i];
                    break;
                case area_k:
                    key = (space ? " " : "");
                    key += args[i];
                    break;
                default:
                    break;
                }
            }
        }

        if (!(req.inFilePath && req.outFilePath && req.key))
        {
            cout << "正しくない引数です" << endl;
            system("pause");
            return -1;
        }
    }
    else if (argc == 1)
    {
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

        string mode = pos == up ? "暗号化" : "復号";

        getline(cin, _);
        cout << endl << mode << "するファイルパス > ";
        getline(cin, inFilePath);
        cout << "出力するファイルパス > ";
        getline(cin, outFilePath);
        cout << mode << "キー > ";
        cin >> key;
    }
    else
    {
        cout << "正しくない引数です" << endl;
        system("pause");
        return -1;
    }

    try
    {
        encdec::Convert(inFilePath, outFilePath, key);
    }
    catch (exception& e)
    {
        cout << endl <<  e.what() << endl;
        system("pause");
        return -1;
    }

    cout << endl << "処理が終了しました" << endl;
    system("pause");
    return 0;
}
