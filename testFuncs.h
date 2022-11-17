// Файл, содержащий функции для тестов
#ifndef TEST_FUNC_H
#define TEST_FUNC_H

#include<cmath>

template<typename Type>
Type func1(Type x){
    return x * x;
}

template<typename Type>
Type func2(Type x){
    return 1.0 / (1.0 + x * x);
}

template<typename Type>
Type func3(Type x){
    return 1.0 / std::atan(1.0 + 10.0 * x * x);
}

template<typename Type>
Type func4(Type x){
    return std::pow(4.0 * pow(x, 3) + 2.0 * pow(x, 2) - 4.0 * x + 2.0, std::sqrt(2.0)) + std::asin(1.0 / (5.0 + x - pow(x, 2)))  - 5.0;
}

template<typename Type>
Type func5(Type x){
    return 1.0;
}

#endif