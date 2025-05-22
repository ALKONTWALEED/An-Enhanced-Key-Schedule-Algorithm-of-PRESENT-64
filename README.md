# An Enhanced Key Schedule Algorithm of PRESENT-64

This project implements a modified version of the key schedule algorithm for the lightweight PRESENT-64 block cipher. The aim is to enhance the diffusion and randomness of round keys while keeping the algorithm efficient and suitable for resource-constrained devices.

## 🔐 Algorithm Overview

- **Block size**: 64 bits  
- **Key size**: 128 bits  
- **Rounds**: 32  
- **Enhancement**: Uses a combination of rotation, round-dependent mutation, and additional randomization in the key schedule.

## 🧠 Motivation

Standard PRESENT-64 key scheduling is linear and deterministic. This enhanced version introduces randomness and structural mutation to make the key expansion less predictable, increasing resistance to certain cryptanalytic attacks.

## 📁 Project Structure

```
Enhanced-PRESENT64/
├── src/
│   └── present64.cpp      // Full source code
├── README.md              // Project description
├── .gitignore             // Build/cache files ignored by Git
└── LICENSE                // License file
```

## 🧪 Example Run

```bash
Enter plaintext (64-bit hexadecimal value): 1234567890ABCDEF
Plaintext: 1234567890abcdef
Randomly Generated Key: 9c63f0029ee4371e
Ciphertext: 7d9d8b019eabc02e
Decrypted Text: 1234567890abcdef
```

## ⚙️ Build & Run

To compile the code using `g++`:

```bash
g++ src/present64.cpp -o present64
./present64
```

## 🧾 License

This project is licensed under the MIT License. You are free to use, modify, and distribute the code.

## 🧠 Author

Developed by **Waleed Manea Saleh** as part of research in lightweight cryptographic algorithms.
