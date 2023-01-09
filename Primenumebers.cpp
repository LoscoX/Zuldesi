//
// Created by LoscoX on 09/01/2023.
//

#include "Primenumebers.hpp"

bool isPrime(int n){
    // Since 0 and 1 is not
    // prime return false.
    if(n == 1 || n == 0) return false;

    // Run a loop from 2 to n-1
    for(int i = 2; i < n; i++)
    {
        // if the number is divisible by i,
        // then n is not a prime number.
        if(n % i == 0) return false;
    }
    // Otherwise n is a prime number.
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
        while (!isPrime(x)){
            x++;
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
        y = n -1;
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