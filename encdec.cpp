#include "encdec.h"


int encdec::Encryption(string inFilePath, string outFilePath, string encKey)
{
    //現在の空き物理メモリサイズを取得
    MEMORYSTATUSEX memoryBuf;
    memoryBuf.dwLength = sizeof(memoryBuf);
    GlobalMemoryStatusEx(&memoryBuf);
    auto memoryFreeSize = memoryBuf.ullAvailPhys;

    //現在の空き物理メモリサイズの80%をプログラムによる使用上限に設定
    if (memoryFreeSize <= splitSize) splitSize = static_cast<size_t>(memoryFreeSize * 0.8);

    //キーをシードに疑似乱数生成
    encKey = random::rand(encKey);
    ifstream in(inFilePath, ios::binary);
    if (!in) throw new exception("ファイルを開けませんでした");
    //ファイルサイズ取得
    size_t fileSize = in.seekg(0, ios::end).tellg();
    in.clear();
    in.seekg(0, ios::beg);
    ofstream out(outFilePath, ios::trunc | ios::binary);
    if (!out) throw new exception("ファイルを出力できませんでした");
    //1バイトごとにキーを分割
    auto [spEncKeyBuf, spEncKeySize] = conv::split(encKey, 2);
    uint8_t a;
    vector<uint8_t> b, spEncKey;
    size_t i = 0;
    //分割済みキーをuint8_t型に変換
    for (auto f : spEncKeyBuf) spEncKey.emplace_back(conv::stoi(f));
    Progress(i, fileSize);
    if (splitSize <= fileSize) b.reserve(splitSize);

    while (!in.eof())
    {
        in.read((char*)&a, 1);
        if (in.eof()) break;
        
        a ^= spEncKey[i % spEncKeySize];
        i++;
        b.emplace_back(a);

        if (i % splitSize == 0 && splitSize <= i)
        {
            for (size_t j = 0; j < splitSize; j++)
            {
                out.write((char*)&b[j], 1);
            }

            b.clear();
            Progress(i, fileSize);
        }
    }

    in.close();

    for (size_t j = 0, size = b.size(); j < size; j++)
    {
        out.write((char*)&b[j], 1);
    }

    Progress(i, fileSize);
    out.close();
    return 0;
}

int encdec::Decryption(string inFilePath, string outFilePath, string decKey)
{
    MEMORYSTATUSEX memoryBuf;
    memoryBuf.dwLength = sizeof(memoryBuf);
    GlobalMemoryStatusEx(&memoryBuf);
    auto memoryFreeSize = memoryBuf.ullAvailPhys;
    if (memoryFreeSize <= splitSize) splitSize = static_cast<size_t>(memoryFreeSize * 0.8);

    decKey = random::rand(decKey);
    ifstream in(inFilePath, ios::binary);
    if (!in) throw new exception("ファイルを開けませんでした");
    size_t fileSize = in.seekg(0, ios::end).tellg();
    in.clear();
    in.seekg(0, ios::beg);
    ofstream out(outFilePath, ios::trunc | ios::binary);
    if (!out) throw new exception("ファイルを出力できませんでした");
    auto [spDecKeyBuf, spDecKeySize] = conv::split(decKey, 2);
    uint8_t a;
    vector<uint8_t> b, spDecKey;
    size_t i = 0;
    for (auto f : spDecKeyBuf) spDecKey.emplace_back(conv::stoi(f));
    Progress(i, fileSize);
    if (splitSize <= fileSize) b.reserve(splitSize);

    while (!in.eof())
    {
        in.read((char*)&a, 1);
        if (in.eof()) break;

        a ^= spDecKey[i % spDecKeySize];
        i++;
        b.emplace_back(a);

        if (i % splitSize == 0 && splitSize <= i)
        {
            for (size_t j = 0; j < splitSize; j++)
            {
                out.write((char*)&b[j], 1);
            }

            b.clear();
            Progress(i, fileSize);
        }
    }

    in.close();

    for (size_t j = 0; j < b.size(); j++)
    {
        out.write((char*)&b[j], 1);
    }

    Progress(i, fileSize);
    out.close();
    return 0;
}

void encdec::Progress(const size_t& nowSize, const size_t& maxSize)
{
    cout << "\r" << flush;
    if (maxSize < 1000000) cout << nowSize << "B / " << maxSize << "B";
    else if (maxSize < 10000000) cout << nowSize / 1000 << "KB / " << maxSize / 1000 << "KB";
    else if (maxSize < 10000000000) cout << nowSize / 1000000 << "MB / " << maxSize / 1000000 << "MB";
    else cout << nowSize / 1000000000 << "GB / " << maxSize / 1000000000 << "GB";
    return;
}
