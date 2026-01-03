#pragma once
#include "pch.h"
#include <vector>
#include <string>
#include <tuple>

namespace legacy {
    class v1_3 {
    public:
        // v1.3 形式の復号を実行する
        // Convertからヘッダー読み取り後の状態で呼び出されることを想定
        static void Decrypt(std::ifstream& in, std::ofstream& out, std::string key, size_t fileSize);

    private:
        // v1.3 当時の疑似乱数生成ロジック
        static std::string rand(const std::string& a);
        static uint64_t stoiorder(const std::string& a);
        static std::string randjoin(const std::string& a);
        
        // 進捗表示（当時の仕様を維持）
        static void PrintProgress(const size_t& nowSize, const size_t& maxSize);

        // 内部ユーティリティ（旧 conv から移植）
        static uint8_t stoi(const std::string& a);
        static std::tuple<std::vector<std::string>, unsigned long long> split(const std::string& a, const unsigned long long& b);
    };
}
