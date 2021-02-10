#include "encdec.h"

int encdec::Convert(string inFilePath, string outFilePath, string key)
{
    //現在の空き物理メモリサイズを取得
    MEMORYSTATUSEX memoryBuf;
    memoryBuf.dwLength = sizeof(memoryBuf);
    GlobalMemoryStatusEx(&memoryBuf);
    auto memoryFreeSize = memoryBuf.ullAvailPhys;

    //現在の空き物理メモリサイズの80%をプログラムによる使用上限に設定
    if (memoryFreeSize <= splitSize) splitSize = static_cast<size_t>(memoryFreeSize * 0.8);

    //キーをシードに疑似乱数生成
    key = random::rand(key);
    ifstream in(inFilePath, ios::binary);
    if (!in) throw exception("Can't open file");
    //ファイルサイズ取得
    size_t fileSize = in.seekg(0, ios::end).tellg();
    in.clear();
    in.seekg(0, ios::beg);
    //1バイトごとにキーを分割
    auto [spkeyBuf, spkeySize] = conv::split(key, 2);
    uint8_t a;
    vector<uint8_t> b, spkey;
    size_t i = 0;
    //分割済みキーをuint8_t型に変換
    for (auto &f : spkeyBuf) spkey.emplace_back(conv::stoi(f));
    PrintProgress(i, fileSize);
    if (splitSize <= fileSize) b.reserve(splitSize);

    //ヘッダーの確認
    Header::header h;
    in.read((char*)&h, sizeof(h));
    Header::match result;

    if (h.identifier[0] == IDENTIFIER[0]
        && h.identifier[1] == IDENTIFIER[1]
        && h.identifier[2] == IDENTIFIER[2])
    {
        if (h.version[0] == VERSION[0])
        {
            result = Header::match::Match;
            fileSize -= identifierSize + versionSize;
        }
        else
        {
            throw exception("Incorrect version");
        }
    }
    else
    {
        result = Header::match::noMatch;
    }

    ofstream out(outFilePath, ios::trunc | ios::binary);
    if (!out)
    {
        throw exception("Can't output file");
    }

    if (result == Header::match::noMatch)
    {
        in.clear();
        in.seekg(0, ios::beg);
        Header::HeaderWrite(h);
        out.write((char*)&h, sizeof(h));
    }

    while (!in.eof())
    {
        in.read((char*)&a, 1);
        if (in.eof()) break;
        
        a ^= spkey[i % spkeySize];
        ++i;
        b.emplace_back(a);

        if (i % splitSize == 0 && splitSize <= i)
        {
            for (size_t j = 0; j < splitSize; ++j)
            {
                out.write((char*)&b[j], 1);
            }

            b.clear();
            PrintProgress(i, fileSize);
        }
    }

    in.close();

    for (size_t j = 0, size = b.size(); j < size; ++j)
    {
        out.write((char*)&b[j], 1);
    }

    PrintProgress(i, fileSize);
    out.close();
    return static_cast<int>(result);
}

void encdec::PrintProgress(const size_t& nowSize, const size_t& maxSize)
{
    cout << "\r" << flush;
    if (maxSize < 1e3)
        cout << nowSize << "B / " << maxSize << "B";
    else if (maxSize < 1e6)
        cout << nowSize / 1e3 << "KB / " << maxSize / 1e3 << "KB";
    else if (maxSize < 1e9)
        cout << nowSize / 1e6 << "MB / " << maxSize / 1e6 << "MB";
    else
        cout << nowSize / 1e9 << "GB / " << maxSize / 1e9 << "GB";
    return;
}
