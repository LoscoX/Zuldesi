//
// Created by LoscoX on 09/01/2023.
//

#ifndef ZULDESI_PRIMENUMEBERS_HPP
#define ZULDESI_PRIMENUMEBERS_HPP

#endif //ZULDESI_PRIMENUMEBERS_HPP

/**
 *
 * @param n
 * @return bool value which indicates if the number is a prime number.
 */
bool isPrime(int n);

/**
 *
 * @param n
 * @return bool value which indicates if the number is a prime number.
 */
int nextPrime(int n);

/**
 *
 * @param n
 * @return the previous prime number to the input.
 * @attention if n is equal or less than 2 it will return 2.
 */
int prevPrime(int n);

/**
 *
 * @param n
 * @return prime number in n position.
 */
int getPrime(int n);

/**
 *
 * @param n
 * @return quantity of prime numbers til n value.
 */
int countPrime(int n);

/**
 *
 * @param n
 * @return an array of the last 10 prime number til n value.
 * @attention if countPrime(n) is less than 10 the last elements will be set to 0.
 * @attention It creates an array stored in the heap. It must be deleted when it became useless.
 */
int* thelast10prime(int n);

