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

random::Engine::Engine(const std::string& key) {
    Init(key);
    globalSalt = 0xDEADBEEFCAFEBABEULL;
}

random::Engine::Engine(const std::string& key, const std::vector<uint8_t>& iv) {
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

uint8_t random::Engine::GetNextByte(uint64_t position) {
    // 大域的な位置情報を用いた動的撹乱（オンザフライ生成）
    // position が変わるたびにステートが進化するため、周期性が消失する
    MixState(position ^ globalSalt);
    
    // ステートから1バイトを抽出
    uint64_t out = state[position % state.size()];
    // 折り畳みによるエントロピーの抽出
    return (uint8_t)((out ^ (out >> 32)) & 0xFF);
}

void random::Engine::UpdateIntegrity(uint8_t byte) {
    // 平文の情報を integrityState に蓄積し、MixState で拡散させる
    integrityState = ROTL(integrityState, 7) ^ byte;
    integrityState += state[byte % state.size()];
}

uint64_t random::Engine::GetIntegrityHash() {
    return integrityState;
}

