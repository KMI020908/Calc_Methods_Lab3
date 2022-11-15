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
    std::size_t n = 60; 
    std::vector<Type> xVec, fVec;
    getUniformGrid(xVec, fVec, func2, -1.0, 1.0, n);
    writeValueTable(xVec, fVec, U_IN_FILE_PATH_1);
    std::vector<Type> resXVec;
    std::vector<Type> resYVec;
    Type h = (xVec[n] - xVec[0]) / n;
    for (std::size_t i = 0; i < 2 * n + 1; i++){
        Type tempX = xVec[0] + h / 2 * i;
        resXVec.push_back(tempX);
        resYVec.push_back(LagrangePolynom(tempX, xVec, fVec));
    }
    writeValueTable(resXVec, resYVec, L_U_OUT_FILE_PATH_1);

    n = 200;
    getChebyshevGrid(xVec, fVec, func2, -1.0, 1.0, n);
    writeValueTable(xVec, fVec, CH_IN_FILE_PATH_1);
    resXVec.clear();
    resYVec.clear();
    h = (xVec[n] - xVec[0]) / n;
    for (std::size_t i = 0; i < 2 * n + 1; i++){
        Type tempX = xVec[0] + h / 2 * i;
        resXVec.push_back(tempX);
        resYVec.push_back(LagrangePolynom(tempX, xVec, fVec));
    }
    writeValueTable(resXVec, resYVec, L_CH_OUT_FILE_PATH_1);
}

int main(){
    //temp_main<double>();
    std::vector<double> diag = {2.0, 4.0, -3.0};
    std::vector<double> lDiag = {5.0, 1.0};
    std::vector<double> uDiag = {-1.0, 2.0};
    std::vector<double> rDiag = {3.0, 6.0, 2.0};
    std::vector<double> solution;
    tridiagonalAlgoritm(diag, lDiag, uDiag, rDiag, solution);
    std::cout << solution;
}