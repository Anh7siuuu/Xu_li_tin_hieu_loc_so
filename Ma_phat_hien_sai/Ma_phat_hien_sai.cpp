#include "Hamming_Code.cpp"
#include "CRC_Code.h"
#include "Convolutional_Code.h"

int main(){
    vector<int> Data = {1, 0, 1, 1};
    vector<int> hammingCodeOut = hammingCode(Data);
    Display_HammingCode(hammingCodeOut);
    vector<int> DataIn = {0, 1, 0, 0, 0, 1, 1};
    vector<int> True_Data = decodeHammingCode(DataIn);
    Display_HammingCode(True_Data);
}