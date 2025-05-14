#include "Hamming_Code.h"
using namespace std;

void hammingCode(int Data[], int m, int hammingCodeOut[]){
    int numberOfParityBits = 0;
    while(pow(2, numberOfParityBits) < m + numberOfParityBits + 1){
        numberOfParityBits++;
    }

    int totalBits = m + numberOfParityBits;
    int j = 0;
    for(int i = 1; i <= totalBits; i++){
        if((i & (i - 1)) != 0){
            hammingCodeOut[i - 1] = Data[j++]; 
        }
    }

    for(int i = 0; i < numberOfParityBits; i++){
        int parityPosition = pow(2, i);
        int parity = 0;
        for(int k = parityPosition - 1; k < totalBits; k += 2 * parityPosition){
            for(int bit = 0; bit < parityPosition && k + bit < totalBits; bit++){
                parity ^= hammingCodeOut[k + bit];
            }
        }
        hammingCodeOut[parityPosition - 1] = parity;
    }
}

void decodeHammingCode(int hammingCodeOut[], int totalBits){
    int errorPosition = 0;
    int numberOfParityBits = 0;
    while(pow(2, numberOfParityBits) < totalBits + 1){
        numberOfParityBits++;
    }

    for(int i = 0; i < numberOfParityBits; i++){
        int parityPosition = pow(2, i);
        int parityCheck = 0;
        for(int k = parityPosition - 1; k < totalBits; k += 2 * parityPosition){
            for(int bit = 0; bit < parityPosition && k + bit < totalBits; bit++){
                parityCheck ^= hammingCodeOut[k + bit];
            }
        }
        if(parityCheck != 0){
            errorPosition += parityPosition;
        }
    }

    if(errorPosition == 0){
        cout << "Code doesn't have error <3" << endl;
    }else{
        hammingCodeOut[errorPosition - 1] ^= 1;
        cout << "Code error at this position: " << errorPosition << endl;
    }
}

void Display_HammingCode(int hammingCodeOut[], int totalBits){
    for(int i = 0; i < totalBits; i++){
        cout << hammingCodeOut[i];
    }
    cout << endl;
}
