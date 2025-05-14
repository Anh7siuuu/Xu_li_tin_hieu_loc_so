#include "CRC_Code.h"
using namespace std;

void XOR(int dividend[], int divisor[], int dividendSize, int divisorSize) {
    for (int i = 0; i <= dividendSize - divisorSize; i++) {
        if (dividend[i] == 1) {
            for (int j = 0; j < divisorSize; j++) {
                dividend[i + j] ^= divisor[j];
            }
        }
    }
}

// Tạo mã CRC
void generateCRC(int Data[], int dataSize, int divisor[], int divisorSize, int appendedData[]) {
    int n = divisorSize;
    for (int i = 0; i < dataSize; i++) {
        appendedData[i] = Data[i];
    }
    for (int i = dataSize; i < dataSize + n - 1; i++) {
        appendedData[i] = 0;
    }

    XOR(appendedData, divisor, dataSize + n - 1, divisorSize);
}
/*
// Kiểm tra mã CRC
bool checkCRC(int receivedData[], int receivedSize, int divisor[], int divisorSize) {
    int remainder[receivedSize];
    for (int i = 0; i < receivedSize; i++) {
        remainder[i] = receivedData[i];
    }
    XOR(remainder, divisor, receivedSize, divisorSize);

    for (int i = 0; i < receivedSize; i++) {
        if (remainder[i] == 1) return false;
    }
    return true;
}
*/
