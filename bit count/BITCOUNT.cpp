#include <iostream>
#include <vector> 
#include <algorithm>
#include <ctime>

using namespace std;

unsigned int getBitCount1(unsigned int num) {
    int count = 0;
    
    while(num) {
        if(num & 0x01)
            count++;
        
        num >>= 1;
    }
    
    return count;
}



unsigned int getBitCount2(unsigned int num) {
    int count = 0;
    
    while(num) {
        count++;
        
        num = num & (num - 1);
    }
    
    return count;
} 

static const unsigned char bitsinbyte[256] = {
    //0000 0000 - 0000 0001
    0,1,
    
    //0000 0010 - 0000 0011
    1,2,
    
    //0000 0100 - 0000 0111
    1,2,2,3,
    
    //0000 1000 - 0000 1111
    1,2,2,3,2,3,3,4,
    
    //0001 0000 - 0001 1111
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    
    //0010 0000 - 0011 1111
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    
    //0100 0000 - 0111 1111
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    
    //1000 0000 - 1111 1111
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

unsigned int getBitCount3(unsigned int num) {
    unsigned char n1 = num;
    unsigned char n2 = num >> 8;
    unsigned char n3 = num >> 16;
    unsigned char n4 = num >> 24;
    
    return bitsinbyte[n1] + bitsinbyte[n2] +
        bitsinbyte[n3] + bitsinbyte[n4];
} 

unsigned int getBitCount4(unsigned int num) {
    num = (num & 0x55555555) + ((num >> 1) & 0x55555555);
    
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    
    num = (num & 0x0F0F0F0F) + ((num >> 4) & 0x0F0F0F0F);
    
    num = (num * 0x01010101 >> 24);
    
    return num;
} 
int main() {
    vector<int> vec;
    std::random_device rd;
      
    for(int i = 0; i < 100000000; i++)
        vec.push_back(rd());       
    
    double dur[4][8] = {0};
    int sum[4][8] = {0};
    clock_t start,end;
    int index = 0;
    
    for(int j = 10; j<=100000000; j *= 10) { 
        //test 1-------------
        start = clock();
        for(int i = 0; i < j; i++) {
            sum[0][index] += getBitCount1(vec[i]);
        }
        end = clock();
        dur[0][index] = (double)(end - start);
        //------------------
        
        
        //test 2-------------
        start = clock();
        for(int i = 0; i < j; i++) {
            sum[1][index] += getBitCount2(vec[i]);
        }
        end = clock();
        dur[1][index] = (double)(end - start);
        //-------------------
        
        
        //test 3-------------
        start = clock();
        for(int i = 0; i < j; i++) {
            sum[2][index] += getBitCount3(vec[i]);
        }
        end = clock();
        dur[2][index] = (double)(end - start);
        //---------------------
        
        
        //test 3-------------
        start = clock();
        for(int i = 0; i < j; i++) {
            sum[3][index] += getBitCount4(vec[i]);
        }
        end = clock();
        dur[3][index] = (double)(end - start);
        //---------------------
        
        index++;
    }
    
    
    for(int i = 0; i < 4; i++){
        cout << "½â·¨"<< i + 1 << endl;
        cout  << "time:" << endl;
        for(int j = 0; j < 8; j++){
            cout << dur[i][j] << " ";
        }
        cout << endl;
        
        cout  << "sum:" << endl;
        for(int j = 0; j < 7; j++){
            cout << sum[i][j] << " ";
        }
        cout << endl;  
    }
    
    return 0;
}

