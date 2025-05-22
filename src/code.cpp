#include <iostream>
#include <bitset>
#include <random>
#include <algorithm>

using namespace std;

typedef uint64_t block;
typedef uint64_t key;   
const int ROUNDS = 32;
const int BLOCK_SIZE = 64;
const int KEY_SIZE = 128;

key generateRandomKey() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<key> dis(0, numeric_limits<key>::max());
    return dis(gen);
}

void generateRoundKeys(key mainKey, key roundKeys[ROUNDS]) {
    for (int i = 0; i < ROUNDS; ++i) {
        key randomPart = generateRandomKey();
        mainKey ^= randomPart;
        roundKeys[i] = mainKey;
        mainKey = ((mainKey << 61) | (mainKey >> 3));
        mainKey = ((mainKey & 0xFFFFFFFFFFFFFF00ULL) | i);
        mainKey ^= (0xC000000000000000ULL << 64);
    }
}

block presentEncrypt(block plaintext, key mainKey) {
    key roundKeys[ROUNDS];
    generateRoundKeys(mainKey, roundKeys);
    block state = plaintext;
    for (int round = 0; round < ROUNDS; ++round) {
        state = ((state & 0xF000000000000000ULL) | ((state >> 4) & 0x0FFFFFFFFFFFFFFFULL));
        state = ((state & 0xFF00FFFFFFFFFFFFULL) | ((state >> 8) & 0x0000FFFFFFFFFF00ULL));
        state = ((state & 0xFFFF0000FFFFFFFFULL) | ((state >> 16) & 0x00000000FFFF0000ULL));
        state = ((state & 0xFFFFFFFF0000FFFFULL) | ((state >> 32) & 0x000000000000FFFFULL));
        state = ((state << 1) | (state >> 63)); 
        state ^= roundKeys[round];
    }
    return state;
}

block presentDecrypt(block ciphertext, key mainKey) {
    key roundKeys[ROUNDS];
    generateRoundKeys(mainKey, roundKeys);
    block state = ciphertext;
    reverse(begin(roundKeys), end(roundKeys));
    for (int round = 0; round < ROUNDS; ++round) {
        state ^= roundKeys[round];
        state = ((state >> 1) | (state << 63)); 
        state = ((state & 0x0FFFFFFFFFFFFFFFULL) | ((state << 4) & 0xF000000000000000ULL));
        state = ((state & 0x0000FFFFFFFFFF00ULL) | ((state << 8) & 0xFF00FFFFFFFFFFFFULL));
        state = ((state & 0x00000000FFFF0000ULL) | ((state << 16) & 0xFFFF0000FFFFFFFFULL));
        state = ((state & 0x000000000000FFFFULL) | ((state << 32) & 0xFFFFFFFF0000FFFFULL));
    }
    return state;
}

int main() {
    cout << "Enter plaintext (64-bit hexadecimal value): ";
    block plaintext;
    cin >> hex >> plaintext;
    key mainKey = generateRandomKey();
    block ciphertext = presentEncrypt(plaintext, mainKey);
    block decryptedText = presentDecrypt(ciphertext, mainKey);
    cout << "Plaintext: " << hex << plaintext << endl;
    cout << "Randomly Generated Key: " << mainKey << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}
