#include "pch.h"
#include "encdec.h"
#include <filesystem>

namespace fs = std::filesystem;

enum arg
{
    arg_i,
    arg_o,
    arg_k
};

// 安全なパス入力のための簡易バリデーション
bool IsSafePath(const string& path) {
    if (path.empty()) return false;
    
    // システムデバイスへの書き込みを防止 (Windows)
    string p = path;
    for (auto &c : p) c = toupper(c);
    if (p == "NUL" || p == "CON" || p == "PRN" || p == "AUX" || p == "COM1" || p == "LPT1") return false;
    
    return true;
}

void WaitForKey() {
    cout << "\nPress Enter to continue...";
    cin.clear();
    // ストリームに残っている改行などを飛ばす
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main(int argc, char **argv)
{
    string inFilePath, outFilePath, key;
    vector<string> args(argv, argv + argc);

    if (argc == 2 && (args[1] == "--help" || args[1] == "-h" || args[1] == "-?"))
    {
        cout << "\nUsage: encdec.exe [-i input file path] [-o output file path] [-k key]"
                "\n\nor run without arguments";
        return 0;
    }
    else if (argc == 2)
    {
        inFilePath = args[1];
        cout << "output file path > ";
        getline(cin, outFilePath);
        cout << "key > ";
        getline(cin, key);
    }
    else if (argc >= 7)
    {
        int arg = -1;
        struct { bool in = false, out = false, k = false; } req;

        for (size_t i = 1; i < argc; ++i)
        {
            if (args[i] == "-i") { arg = arg_i; req.in = true; }
            else if (args[i] == "-o") { arg = arg_o; req.out = true; }
            else if (args[i] == "-k") { arg = arg_k; req.k = true; }
            else
            {
                switch (arg)
                {
                case arg_i: inFilePath += args[i]; break;
                case arg_o: outFilePath += args[i]; break;
                case arg_k: key += args[i]; break;
                }
            }
        }
        if (!(req.in && req.out && req.k)) {
            cout << "Error: Missing required arguments." << endl;
            WaitForKey();
            return -1;
        }
    }
    else if (argc == 1)
    {
        cout << "Input file path > ";
        getline(cin, inFilePath);
        cout << "Output file path > ";
        getline(cin, outFilePath);
        cout << "Key > ";
        getline(cin, key);
    }
    else
    {
        cout << "Incorrect argument count." << endl;
        WaitForKey();
        return -1;
    }

    // パスバリデーション
    if (!IsSafePath(inFilePath) || !IsSafePath(outFilePath)) {
        cout << "Error: Invalid or unsafe file path detected." << endl;
        WaitForKey();
        return -1;
    }

    try
    {
        encdec::Convert(inFilePath, outFilePath, key);
        cout << "\n\nThe process is completed successfully." << endl;
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl;
        WaitForKey();
        return -1;
    }

    WaitForKey();
    return 0;
}

