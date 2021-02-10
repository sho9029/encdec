#include "pch.h"
#include "encdec.h"

enum arg
{
    arg_i,
    arg_o,
    arg_k
};

int main(int argc, char **argv)
{
    string inFilePath, outFilePath, key, _;
    vector<string> args(argv, argv + argc);

    if (argc == 2 && (args[1] == "--help" || args[1] == "-h" || args[1] == "-?"))
    {
        cout << "\nUsage: encdec.exe [-i input file path] [-o output file path] [-k key]"
                "\n\nor run without arguments";
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
                arg = arg_i;
                req.inFilePath = true;
            }
            else if (args[i] == "-o")
            {
                arg = arg_o;
                req.outFilePath = true;
            }
            else if (args[i] == "-k")
            {
                arg = arg_k;
                req.key = true;
            }
            else
            {
                switch (arg)
                {
                case arg_i:
                    inFilePath += args[i];
                    break;
                case arg_o:
                    outFilePath += args[i];
                    break;
                case arg_k:
                    key += args[i];
                    break;
                default:
                    break;
                }
            }
        }

        if (!(req.inFilePath && req.outFilePath && req.key))
        {
            cout << "Incorrect argument" << endl;
            system("pause");
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
        cout << "Incorrect argument" << endl;
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

    cout << endl << "The process is completed" << endl;
    system("pause");
    return 0;
}
