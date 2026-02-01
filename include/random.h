#pragma once
#include "pch.h"
#include <vector>
#include <string>

class random
{
public:
    // v2.0 オンザフライ生成エンジン
    class Engine {
    public:
        Engine(const std::string& key);
        Engine(const std::string& key, const std::vector<uint8_t>& iv);
        
        // 指定した位置におけるキーストリームの1バイトを取得
        uint8_t GetNextByte(uint64_t position);

        // 整合性検証用ハッシュの更新
        void UpdateIntegrity(uint8_t byte);
        // 現在の整合性ハッシュを取得
        uint64_t GetIntegrityHash();

    private:
        // 内部ステート（広帯域：鍵の長さに応じて可変、最低512bit）
        std::vector<uint64_t> state;
        
        // 整合性検証用ハッシュ
        uint64_t integrityState = 0;

        // 撹乱用のソルト（大域的な位置依存性を持たせるため）
        uint64_t globalSalt;

        // ステートをかき混ぜる内部関数 (ARXアーキテクチャ)
        void MixState(uint64_t mixVal);

        // 共通初期化処理
        void Init(const std::string& key);

        // ビット回転 (Circular Shift)
        inline uint64_t ROTL(uint64_t x, int n) {
            return (x << n) | (x >> (64 - n));
        }
    };
};
