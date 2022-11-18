#include<vector>
#include"methods.cpp"
#include"ioData.cpp"
#include"filePath.h"
#include<iomanip>
#include"testFuncs.h"
#include<algorithm>

// Процедура проверки полиномов Лагранжа
template<typename Type>
void checkTestLagrange(std::size_t numOfFinElems, Type (*f)(Type x), Type firstX, Type lastX,
const std::string &U_IN_FILE_PATH, const std::string &CH_IN_FILE_PATH, const std::string &L_U_OUT_FILE_PATH, const std::string &L_CH_OUT_FILE_PATH, 
const std::string &L_U_ERROR_FILE_PATH, const std::string &L_CH_ERROR_FILE_PATH, std::size_t numOfErrors = 100, Type accuracy = 1e-10){
    std::vector<Type> xGrid, fGrid;

    getUniformGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    writeValueTable(xGrid, fGrid, U_IN_FILE_PATH);
    std::vector<Type> xVec;
    std::vector<Type> fVec;
    Type tempX = xGrid[0];
    Type h = (xGrid[numOfFinElems] - xGrid[0]) / (2.0 * numOfErrors);
    while (tempX <= xGrid[numOfFinElems] + accuracy){
        xVec.push_back(tempX);
        tempX += h;
    }
    getLagrangeInterpolation(xVec, fVec, xGrid, fGrid);
    writeValueTable(xVec, fVec, L_U_OUT_FILE_PATH);

    getChebyshevGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    writeValueTable(xGrid, fGrid, CH_IN_FILE_PATH);
    xVec.clear();
    fVec.clear();
    tempX = xGrid[0];
    h = (xGrid[numOfFinElems] - xGrid[0]) / (2.0 * numOfErrors);
    while (tempX <= xGrid[numOfFinElems] + accuracy){
        xVec.push_back(tempX);
        tempX += h;
    }
    getLagrangeInterpolation(xVec, fVec, xGrid, fGrid);
    writeValueTable(xVec, fVec, L_CH_OUT_FILE_PATH);

    std::vector<Type> uniErr;
    getInterpolationErrorsLagrangeUniform(f, firstX, lastX, numOfErrors, uniErr, accuracy);
    writeVectorFile(uniErr, L_U_ERROR_FILE_PATH);

    std::vector<Type> chebErr;
    getInterpolationErrorsLagrangeChebyshev(f, firstX, lastX, numOfErrors, chebErr, accuracy);
    writeVectorFile(chebErr, L_CH_ERROR_FILE_PATH);
}

// Процедура проверки кубических сплайнов
template<typename Type>
void checkTestSpline(std::size_t numOfFinElems, Type (*f)(Type x), Type firstX, Type lastX,
const std::string &S_U_OUT_FILE_PATH, const std::string &S_CH_OUT_FILE_PATH, const std::string &S_U_ERROR_FILE_PATH, 
const std::string &S_CH_ERROR_FILE_PATH, std::size_t numOfErrors = 100, Type accuracy = 1e-10){
    std::vector<Type> xGrid, fGrid;

    getUniformGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    std::vector<Type> xVec, fVec;
    Type tempX = xGrid[0];
    Type h = (xGrid[numOfFinElems] - xGrid[0]) / (2.0 * numOfErrors);
    while (tempX <= xGrid[numOfFinElems] + accuracy){
        xVec.push_back(tempX);
        tempX += h;
    }
    getCubeSplineInterpolation(xVec, fVec, xGrid, fGrid, accuracy);
    writeValueTable(xVec, fVec, S_U_OUT_FILE_PATH);

    getChebyshevGrid(xGrid, fGrid, f, firstX, lastX, numOfFinElems);
    xVec.clear();
    fVec.clear();
    tempX = xGrid[0];
    h = (xGrid[numOfFinElems] - xGrid[0]) / (2.0 * numOfErrors);
    while (tempX <= xGrid[numOfFinElems] + accuracy){
        xVec.push_back(tempX);
        tempX += h;
    }
    getCubeSplineInterpolation(xVec, fVec, xGrid, fGrid, accuracy);
    writeValueTable(xVec, fVec, S_CH_OUT_FILE_PATH);

    std::vector<Type> uniErr;
    getInterpolationErrorsLagrangeUniform(f, firstX, lastX, numOfErrors, uniErr, accuracy);
    writeVectorFile(uniErr, S_U_ERROR_FILE_PATH);

    std::vector<Type> chebErr;
    getInterpolationErrorsLagrangeChebyshev(f, firstX, lastX, numOfErrors, chebErr, accuracy);
    writeVectorFile(chebErr, S_CH_ERROR_FILE_PATH);
}

template<typename Type>
void temp_main(){
    std::size_t numOfFinElems = 3; 

    checkTestLagrange(numOfFinElems, func1, -1.0, 1.0, U_IN_FILE_PATH_1, CH_IN_FILE_PATH_1, L_U_OUT_FILE_PATH_1, L_CH_OUT_FILE_PATH_1, L_U_ERROR_FILE_PATH_1, L_CH_ERROR_FILE_PATH_1);
    checkTestSpline(numOfFinElems, func1, -1.0, 1.0, S_U_OUT_FILE_PATH_1, S_CH_OUT_FILE_PATH_1, S_U_ERROR_FILE_PATH_1, S_CH_ERROR_FILE_PATH_1);

    checkTestLagrange(numOfFinElems, func2, -1.0, 1.0, U_IN_FILE_PATH_2, CH_IN_FILE_PATH_2, L_U_OUT_FILE_PATH_2, L_CH_OUT_FILE_PATH_2, L_U_ERROR_FILE_PATH_2, L_CH_ERROR_FILE_PATH_2);
    checkTestSpline(numOfFinElems, func2, -1.0, 1.0, S_U_OUT_FILE_PATH_2, S_CH_OUT_FILE_PATH_2, S_U_ERROR_FILE_PATH_2, S_CH_ERROR_FILE_PATH_2);

    checkTestLagrange(numOfFinElems, func3, -3.0, 3.0, U_IN_FILE_PATH_3, CH_IN_FILE_PATH_3, L_U_OUT_FILE_PATH_3, L_CH_OUT_FILE_PATH_3, L_U_ERROR_FILE_PATH_3, L_CH_ERROR_FILE_PATH_3);
    checkTestSpline(numOfFinElems, func3, -3.0, 3.0, S_U_OUT_FILE_PATH_3, S_CH_OUT_FILE_PATH_3, S_U_ERROR_FILE_PATH_3, S_CH_ERROR_FILE_PATH_3);

    checkTestLagrange(numOfFinElems, func4, -1.0, 1.0, U_IN_FILE_PATH_4, CH_IN_FILE_PATH_4, L_U_OUT_FILE_PATH_4, L_CH_OUT_FILE_PATH_4, L_U_ERROR_FILE_PATH_4, L_CH_ERROR_FILE_PATH_4);
    checkTestSpline(numOfFinElems, func4, -1.0, 1.0, S_U_OUT_FILE_PATH_4, S_CH_OUT_FILE_PATH_4, S_U_ERROR_FILE_PATH_4, S_CH_ERROR_FILE_PATH_4);

    checkTestLagrange(numOfFinElems, func5, -1.0, 1.0, U_IN_FILE_PATH_5, CH_IN_FILE_PATH_5, L_U_OUT_FILE_PATH_5, L_CH_OUT_FILE_PATH_5, L_U_ERROR_FILE_PATH_5, L_CH_ERROR_FILE_PATH_5);
    checkTestSpline(numOfFinElems, func5, -1.0, 1.0, S_U_OUT_FILE_PATH_5, S_CH_OUT_FILE_PATH_5, S_U_ERROR_FILE_PATH_5, S_CH_ERROR_FILE_PATH_5);

    // Проверка ошибки экстрополяции экспоненты на [0; 2]
    std::vector<Type> xGrid;
    std::vector<Type> fGrid;
    getUniformGrid(xGrid, fGrid, func6, 0.0, 2.0, 10);
    std::cout << "Значение многочлена Лагранжа в точке x = 2.2: " << LagrangePolynom(2.2, xGrid, fGrid) << '\n';
    std::cout << "Ошибка экстрополяции в точке x = 2.2: " << std::abs(LagrangePolynom(2.2, xGrid, fGrid) - func6(2.2)) << '\n';
}

int main(){
    temp_main<double>();
    
}