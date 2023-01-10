//
// Created by LoscoX on 09/01/2023.
//

#include "Primenumebers.hpp"

bool isPrime(int n){

    if(n == 1 || n == 0) return false;

    for(int i = 2; i < n; i++)
    {
        if(n % i == 0) return false;
    }

    return true;
}

int nextPrime(int n){
    int x = n+1;

    while (!isPrime(x)){
        ++x;
    }
    return x;
}

int prevPrime(int n){
    if (n<= 2){
        return 2;
    }else{
        int x = n-1;
        while (!isPrime(x)){
            --x;
        }
        return x;
    }
}

int getPrime(int n){
    int x = 0;
    for (int i = 0; i<n; i++){
        x += 1;
        while (!isPrime(x)){
            x += 1;
        }
    }
    return x;
}

int countPrime(int n){
    int counter = 0;
    for (int i = 0; i<=n; i++){
        if (isPrime(i)){
            ++counter;
        }
    }
    return counter;
}

int* thelast10prime(int n){
    int* arr = new int[10];
    int y;
    if (countPrime(n)<10){
        y = 2;
        for (int i = 0; i<10; i++){
            if (y<=n){
                arr[i] = nextPrime(y);
                y = arr[i];
            }else{
                arr[i]= 0;
            }
        }
    }else{
        y = n+1;
        for (int i = 9; i>=0; i--){
            arr[i] = prevPrime(y);
            y = prevPrime(y);
        }
    }
    return arr;
}