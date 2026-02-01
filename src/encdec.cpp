#include "encdec.h"
#include "LegacyDecoder.h"
#include "random.h"
#include <filesystem>
#include <memory>
#include <random>

namespace fs = std::filesystem;

int encdec::Convert(string inFilePath, string outFilePath, string key)
{
    // 1. ファイルオープン
    if (!fs::exists(inFilePath)) throw exception(("Input file not found: " + inFilePath).c_str());
    if (fs::is_directory(inFilePath)) throw exception("The input path is a directory, not a file.");
    
    ifstream in(inFilePath, ios::binary);
    if (!in) throw exception("Access denied or file is locked by another process.");

    // 2. ヘッダーの確認 (5 bytes)
    Header::header h;
    in.read((char*)&h, sizeof(h));
    
    bool isEncrypted = false;
    if (in.gcount() == sizeof(h) && 
        h.identifier[0] == IDENTIFIER[0] && 
        h.identifier[1] == IDENTIFIER[1] && 
        h.identifier[2] == IDENTIFIER[2]) 
    {
        isEncrypted = true;
    }

    // 3. 出力ファイルの準備
    if (fs::exists(outFilePath) && fs::is_directory(outFilePath)) throw exception("The output path is a directory.");
    
    ofstream out(outFilePath, ios::trunc | ios::binary);
    if (!out) throw exception("Failed to create output file. Check permissions or if the disk is full.");

    // 4. バージョン判定とルーティング
    size_t fileSize = in.seekg(0, ios::end).tellg();
    in.clear();

    vector<uint8_t> iv;
    random::Engine* enginePtr = nullptr;

    if (isEncrypted) {
        if (h.version[0] == 1 && h.version[1] == 3) {
            // --- v1.3 後方互換復号 ---
            in.seekg(sizeof(h), ios::beg);
            legacy::v1_3::Decrypt(in, out, key, fileSize - sizeof(h));
            return static_cast<int>(Header::match::Match);
        } 
        else if (h.version[0] == 2 && h.version[1] == 0) {
            // --- v2.0 レガシー復号 (IVなし) ---
            in.seekg(sizeof(h), ios::beg);
            fileSize -= sizeof(h);
            enginePtr = new random::Engine(key); // v2.0用初期化
        }
        else if (h.version[0] == MAJOR && h.version[1] == MINOR) {
            // --- v2.1 最新復号 (IVあり) ---
            in.seekg(sizeof(h), ios::beg);
            
            // IV読み込み
            iv.resize(IV_SIZE);
            in.read((char*)iv.data(), IV_SIZE);
            
            fileSize -= (sizeof(h) + IV_SIZE);
            enginePtr = new random::Engine(key, iv); // v2.1用初期化
        } 
        else {
            string ver = to_string((int)h.version[0]) + "." + to_string((int)h.version[1]);
            throw exception(("The file version (" + ver + ") is not supported by this tool.").c_str());
        }
    } 
    else {
        // --- v2.1 新規暗号化 ---
        in.seekg(0, ios::beg);
        Header::HeaderWrite(h);
        out.write((char*)&h, sizeof(h));
        
        
        // IV生成と書き込み
        iv.resize(IV_SIZE);
        
        // Use std::random_device for better entropy
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int> dis(0, 255);
        
        for(size_t i=0; i<IV_SIZE; ++i) {
            iv[i] = static_cast<uint8_t>(dis(gen));
        }
        
        out.write((char*)iv.data(), IV_SIZE);
        
        enginePtr = new random::Engine(key, iv); // v2.1用初期化
    }

    // Smart pointer would be better, but sticking to manual management to match existing style broadly
    unique_ptr<random::Engine> engine(enginePtr);

    // 5. コアループ (オンザフライ・ビット撹乱エンジン)
    uint8_t a;
    size_t processed = 0;
    
    // 復号時はフッター分を除いたサイズを処理
    size_t dataSize = isEncrypted ? (fileSize - sizeof(uint64_t)) : fileSize;

    // バッファリング
    const size_t internalBufSize = 64 * 1024; // 64KB
    vector<uint8_t> buf;
    buf.reserve(internalBufSize);

    while (processed < dataSize && !in.eof()) {
        in.read((char*)&a, 1);
        if (in.eof()) break;

        uint8_t plaintext;
        if (!isEncrypted) {
            plaintext = a;
            a ^= engine->GetNextByte(processed); // 暗号化
        } else {
            a ^= engine->GetNextByte(processed); // 復号
            plaintext = a;
        }

        engine->UpdateIntegrity(plaintext);
        processed++;
        buf.push_back(a);

        if (buf.size() >= internalBufSize) {
            out.write((char*)buf.data(), buf.size());
            buf.clear();
            // Show progress every 1MB to avoid excessive stdout pressure
            if (processed % (1024 * 1024) < internalBufSize) {
                PrintProgress(processed, dataSize);
            }
        }
    }
    if (!buf.empty()) {
        out.write((char*)buf.data(), buf.size());
    }
    
    // 6. 整合性検証・フッター処理
    if (!isEncrypted) {
        // 暗号化時：フッター（ハッシュ）を書き込む
        uint64_t hash = engine->GetIntegrityHash();
        out.write((char*)&hash, sizeof(hash));
    } else {
        // 復号時：フッターを読み込んで計算値と比較
        uint64_t storedHash;
        in.read((char*)&storedHash, sizeof(storedHash));
        if (storedHash != engine->GetIntegrityHash()) {
            throw exception("Decryption failed. Cause: The key is incorrect OR the file data has been tampered with.");
        }
    }

    PrintProgress(processed, dataSize);
    in.close();
    out.close();

    return 0; // Success
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
