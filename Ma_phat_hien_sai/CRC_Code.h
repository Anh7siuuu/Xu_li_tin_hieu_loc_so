#include <iostream>
#include <vector>
using namespace std;

vector<int> XOR(vector<int> dividend, vector<int> divisor);

// Tao ma CRC
vector<int> generateCRC(vector<int> &Data, vector<int> &divisor);

// Kiem tra ma CRC
bool checkCRC(vector<int> &receivedData, vector<int> &divisor);
