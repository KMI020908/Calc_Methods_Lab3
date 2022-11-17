#include<vector>
#include"methods.cpp"
#include"ioData.cpp"
#include"filePath.h"
#include<iomanip>
#include"testFuncs.h"
#include<algorithm>

// Процедура проверки алгоритмов
template<typename Type>
void checkTestLagrange(std::size_t numOfFinElems, Type (*f)(Type x), Type firstX, Type lastX,
const std::string &U_IN_FILE_PATH, const std::string &CH_IN_FILE_PATH, const std::string &L_U_OUT_FILE_PATH, const std::string &L_CH_OUT_FILE_PATH){
    std::vector<Type> xGrid, fGrid;

    getUniformGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    writeValueTable(xGrid, fGrid, U_IN_FILE_PATH);
    std::vector<Type> xVec;
    std::vector<Type> fVec;
    for (std::size_t i = 1; i < numOfFinElems + 1; i++){
        Type tempX = xGrid[i - 1];
        xVec.push_back(tempX);
        tempX = xGrid[i - 1] + 0.5 * (xGrid[i] - xGrid[i - 1]);
        xVec.push_back(tempX);
    }
    xVec.push_back(xGrid[numOfFinElems]);
    getLagrangeInterpolation(xVec, fVec, xGrid, fGrid);
    writeValueTable(xVec, fVec, L_U_OUT_FILE_PATH);

    getChebyshevGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    writeValueTable(xGrid, fGrid, CH_IN_FILE_PATH);
    xVec.clear();
    fVec.clear();
    for (std::size_t i = 1; i < numOfFinElems + 1; i++){
        Type tempX = xGrid[i - 1];
        xVec.push_back(tempX);
        tempX = xGrid[i - 1] + 0.5 * (xGrid[i] - xGrid[i - 1]);
        xVec.push_back(tempX);
    }
    xVec.push_back(xGrid[numOfFinElems]);
    getLagrangeInterpolation(xVec, fVec, xGrid, fGrid);
    writeValueTable(xVec, fVec, L_CH_OUT_FILE_PATH);
}

template<typename Type>
void checkTestSpline(std::size_t numOfFinElems, Type (*f)(Type x), Type firstX, Type lastX,
const std::string &S_U_OUT_FILE_PATH, const std::string &S_CH_OUT_FILE_PATH){
    std::vector<Type> xGrid, fGrid;

    getUniformGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    std::vector<Type> xVec, fVec;
    for (std::size_t i = 1; i < numOfFinElems + 1; i++){
        Type tempX = xGrid[i - 1];
        xVec.push_back(tempX);
        tempX = xGrid[i - 1] + 0.5 * (xGrid[i] - xGrid[i - 1]);
        xVec.push_back(tempX);
    }
    xVec.push_back(xGrid[numOfFinElems]);
    getCubeSplineInterpolation(xVec, fVec, xGrid, fGrid);
    writeValueTable(xVec, fVec, S_U_OUT_FILE_PATH);

    getChebyshevGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    xVec.clear();
    fVec.clear();
    for (std::size_t i = 1; i < numOfFinElems + 1; i++){
        Type tempX = xGrid[i - 1];
        xVec.push_back(tempX);
        tempX = xGrid[i - 1] + 0.5 * (xGrid[i] - xGrid[i - 1]);
        xVec.push_back(tempX);
    }
    xVec.push_back(xGrid[numOfFinElems]);
    getCubeSplineInterpolation(xVec, fVec, xGrid, fGrid);
    writeValueTable(xVec, fVec, S_CH_OUT_FILE_PATH);
}

template<typename Type>
void temp_main(){
    std::size_t numOfFinElems = 100; 

    checkTestLagrange(numOfFinElems, func1, -1.0, 1.0, U_IN_FILE_PATH_1, CH_IN_FILE_PATH_1, L_U_OUT_FILE_PATH_1, L_CH_OUT_FILE_PATH_1);
    checkTestSpline(numOfFinElems, func1, -1.0, 1.0, S_U_OUT_FILE_PATH_1, S_CH_OUT_FILE_PATH_1);

    checkTestLagrange(numOfFinElems, func2, -1.0, 1.0, U_IN_FILE_PATH_2, CH_IN_FILE_PATH_2, L_U_OUT_FILE_PATH_2, L_CH_OUT_FILE_PATH_2);
    checkTestSpline(numOfFinElems, func2, -1.0, 1.0, S_U_OUT_FILE_PATH_2, S_CH_OUT_FILE_PATH_2);

    checkTestLagrange(numOfFinElems, func3, -3.0, 3.0, U_IN_FILE_PATH_3, CH_IN_FILE_PATH_3, L_U_OUT_FILE_PATH_3, L_CH_OUT_FILE_PATH_3);
    checkTestSpline(numOfFinElems, func3, -3.0, 3.0, S_U_OUT_FILE_PATH_3, S_CH_OUT_FILE_PATH_3);

    checkTestLagrange(numOfFinElems, func4, -1.0, 1.0, U_IN_FILE_PATH_4, CH_IN_FILE_PATH_4, L_U_OUT_FILE_PATH_4, L_CH_OUT_FILE_PATH_4);
    checkTestSpline(numOfFinElems, func4, -1.0, 1.0, S_U_OUT_FILE_PATH_4, S_CH_OUT_FILE_PATH_4);

    checkTestLagrange(numOfFinElems, func5, -1.0, 1.0, U_IN_FILE_PATH_5, CH_IN_FILE_PATH_5, L_U_OUT_FILE_PATH_5, L_CH_OUT_FILE_PATH_5);
    checkTestSpline(numOfFinElems, func5, -1.0, 1.0, S_U_OUT_FILE_PATH_5, S_CH_OUT_FILE_PATH_5);
}

int main(){
    temp_main<double>();
    std::vector<double> xVec = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> fVec = {1.0, 4.0, 9.0, 16.0};
    std::vector<double> a, b, c, d;

    findSplineCoefs(xVec, fVec, a, b, c, d);
    std::cout << a << '\n';
    std::cout << b << '\n';
    std::cout << c << '\n';
    std::cout << d << '\n' << '\n';
}