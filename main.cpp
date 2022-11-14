#include<vector>
#include"methods.cpp"
#include"ioData.cpp"
#include"filePath.h"
#include<iomanip>
#include"testFuncs.h"

// Процедура проверки алгоритмов
template<typename Type>
void checkTest(std::vector<std::vector<Type>> &valTable,
const std::string &IN_FILE_PATH, const std::string &L_OUT_FILE_PATH, const std::string &S_OUT_FILE_PATH, Type accuracy = 1e-6){
    
}

template<typename Type>
void temp_main(){
    std::vector<Type> xVec, fVec;
    getUniformGrid(xVec, fVec, func1, -1.0, 1.0, 50);
    writeValueTable(xVec, fVec, U_IN_FILE_PATH_1);

    getChebyshevGrid(xVec, fVec, func1, -1.0, 1.0, 50);
    writeValueTable(xVec, fVec, CH_IN_FILE_PATH_1);
}

int main(){
    temp_main<double>();

    std::cout << (2.0 * 0 + 1.0) * M_PI;
}