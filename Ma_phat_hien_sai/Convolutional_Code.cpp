#include "Convolutional_Code.h"
using namespace std;

// Hàm tạo mã chập (Convolutional Code)
vector<vector<int>> convolutionalEncode(vector<int> &Data) {
    // Trạng thái ban đầu của thanh ghi dịch
    vector<int> shiftRegister(2, 0);  // Giả sử 2 bit thanh ghi dịch
    
    vector<vector<int>> encodedData;
    
    // Định nghĩa bộ tạo (generator)
    vector<int> G1 = {1, 1, 1};  // Bộ tạo 1 (ví dụ: 111)
    vector<int> G2 = {1, 0, 1};  // Bộ tạo 2 (ví dụ: 101)
    
    for (int bit : Data) {
        // Dịch các bit trong thanh ghi
        shiftRegister.insert(shiftRegister.begin(), bit);
        shiftRegister.pop_back();
        
        // Tính toán bit đầu ra theo từng bộ tạo
        int output1 = (shiftRegister[0] * G1[0]) ^ (shiftRegister[1] * G1[1]) ^ (0 * G1[2]);
        int output2 = (shiftRegister[0] * G2[0]) ^ (shiftRegister[1] * G2[1]) ^ (0 * G2[2]);
        
        // Lưu bit đầu ra
        encodedData.push_back({output1, output2});
    }
    return encodedData;
}

// Hiển thị mã chập
void Display_ConvolutionalCode(vector<vector<int>> &encodedData) {
    for (auto &bitPair : encodedData) {
        cout << bitPair[0] << bitPair[1] << " ";
    }
    cout << endl;
}

