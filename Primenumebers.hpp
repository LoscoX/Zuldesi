//
// Created by LoscoX on 09/01/2023.
//

#ifndef ZULDESI_PRIMENUMEBERS_HPP
#define ZULDESI_PRIMENUMEBERS_HPP

#endif //ZULDESI_PRIMENUMEBERS_HPP

/*
 *  @return bool value which indicates if the number is a prime number.
 */
bool isPrime(int n);

/*
 *  @return the next prime number to the input number.
 */
int nextPrime(int n);

/*
 *  @return the previous prime number to the input
 *  note: if n<=2 it will return 2.
 */
int prevPrime(int n);

/*
 *
 * @return prime number in n position
 */
int getPrime(int n);

/*
 *  @return quantity of prime numbers til n value
 */
int countPrime(int n);

/*
 * @return an array of the last 10 prime number til n value
 * note: if countPrime(n)<10 the last elements will be set to 0.
 */
int* thelast10prime(int n);

