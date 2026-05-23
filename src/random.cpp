#include "random.h"

void random::Engine::Init(const std::string& key) {
    // 1. ステートの初期化
    // 鍵の全情報を保持するため、鍵の長さに応じた可変長ステートを採用（最低512bit / 8 * uint64_t）
    size_t stateSize = (key.length() / 8) + 1;
    if (stateSize < 8) stateSize = 8;
    state.resize(stateSize, 0x5555555555555555ULL);

    // 2. 鍵情報の吸収 (Absorb)
    for (size_t i = 0; i < key.length(); ++i) {
        state[i % stateSize] ^= (static_cast<uint64_t>(key[i]) << ((i % 8) * 8));
        MixState(state[i % stateSize]);
    }
}

random::Engine::Engine(const std::string& key, bool legacyAlgorithm)
    : legacyAlgorithm(legacyAlgorithm) {
    Init(key);
    globalSalt = 0xDEADBEEFCAFEBABEULL;
}

random::Engine::Engine(const std::string& key, const std::vector<uint8_t>& iv,
                      bool legacyAlgorithm)
    : legacyAlgorithm(legacyAlgorithm) {
    Init(key);
    
    // IVをglobalSaltとして使用（128bit以上ある場合はハッシュ化して縮約するか、MixStateで混ぜ込む）
    // 今回は簡易的にIVの最初の8バイトと次の8バイトをXORして64bit saltにする
    // 本来は128bit以上のIVをフル活用すべきだが、現状のアーキテクチャ(64bit salt)に合わせて縮約する
    uint64_t ivPart1 = 0, ivPart2 = 0;
    if (iv.size() >= 16) {
        memcpy(&ivPart1, iv.data(), 8);
        memcpy(&ivPart2, iv.data() + 8, 8);
    }
    globalSalt = ivPart1 ^ ivPart2;
    
    // さらにIV全体をStateにMixする
    MixState(ivPart1);
    MixState(ivPart2);
}

void random::Engine::MixState(uint64_t mixVal) {
    // ARX (Addition, Rotation, XOR) アーキテクチャによる撹乱
    for (size_t i = 0; i < state.size(); ++i) {
        size_t next = (i + 1) % state.size();
        
        state[i] += mixVal;
        state[i] = ROTL(state[i], (int)((i + 1) % 63));
        state[i] ^= state[next];
        
        // 対称性を高めるための逆方向への拡散
        state[next] ^= ROTL(state[i], 31);
    }
}

void random::Engine::GenerateBlock(uint64_t blockIndex) {
    size_t blockSize = state.size() * 8;
    keyStreamBuffer.resize(blockSize);

    // ブロック開始位置のオフセットを利用してステートを撹乱
    uint64_t blockStartOffset = blockIndex * blockSize;
    MixState(blockStartOffset ^ globalSalt);

    // かき混ぜられたステート全体からバイト列をバッファに抽出
    for (size_t i = 0; i < state.size(); ++i) {
        uint64_t val = state[i];
        for (int j = 0; j < 8; ++j) {
            keyStreamBuffer[i * 8 + j] = static_cast<uint8_t>((val >> (j * 8)) & 0xFF);
        }
    }
    
    currentBlockIndex = blockIndex;
}

uint8_t random::Engine::GetNextByte(uint64_t position) {
    if (legacyAlgorithm) {
        // v2.0/v2.1 の旧方式: 位置ごとにステートを更新して1バイト生成する
        MixState(position ^ globalSalt);
        uint64_t out = state[position % state.size()];
        return static_cast<uint8_t>((out ^ (out >> 32)) & 0xFF);
    }

    size_t blockSize = state.size() * 8;
    uint64_t blockIndex = position / blockSize;
    size_t offset = position % blockSize;

    if (blockIndex != currentBlockIndex) {
        GenerateBlock(blockIndex);
    }

    return keyStreamBuffer[offset];
}

void random::Engine::UpdateIntegrity(uint8_t byte) {
    // 平文の情報を integrityState に蓄積し、MixState で拡散させる
    integrityState = ROTL(integrityState, 7) ^ byte;
    integrityState += state[byte % state.size()];
}

uint64_t random::Engine::GetIntegrityHash() {
    return integrityState;
}

