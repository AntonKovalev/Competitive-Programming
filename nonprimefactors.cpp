    #include <algorithm>
    #include <vector>
    #include <iostream>
    #include <stdio.h>
    //#include <cmath>
    #include <math.h> /* log10 */
    #include <unordered_map>
    #include <cstdint>
    #include <memory>
    #include <array>
    #include <string>
    #include <sstream>
    #include <set>
    #include <array>
    #include<limits>

using namespace std;

//! Example: if the number is 120, the prime factorizaton gives:
//! 2^3 * 3^1 * 5^1. The number of factors in this number is therefore:
//! (3+1)*(1+1)*(1+1) = 16.
//! The number of non-prime factors is:
//! 16 - 3 = 13, where 3 is the number of prime factors in 120.
//! 
//! The solution revolves around finding the exponents of each prime factor.
//! For that, you'll need to find all the prime factors.
//! But we need to try prime factors only up to sqrt(number), i.e. 2,3,5,...,<=sqrt(number).
//! By trying to divide every input number with the prime number, in increasing order,
//! we'll be able to find all the prime factors of that number, together with the exponents.
//!
//!
//! Example:
//!
//! Assume you have a number 43*2*3 = 258. Sqrt(258) ~ 16.
//! Starting with the smallest factor, we try 258 mod 2 == 0. This returns true.
//! We calculate 258/2 = 129, then we check if 129 is a prime number.
//! It is not, so we continue. Lets see if 129 mod 2 == 0.
//! It returns false, so the first prime_factor^exponent = 2^1.
//! Now, try the next largest prime factor, 3. 129 mod 3 == 0, yes. 
//! 129/3 = 43. 43 mod 3 != 0. So, we have found another
//! prime_factor^exponent = 3^1. Now, again, check if 43 is a prime number. It is!
//! Then, we have factorized the whole number and found the last prime_factor^exponent = 43^1.
//! Note that we should check that 43 > sqrt(258). If it is, then 43 can only appear once in 258.
//! The factorization of 258 is = 2^1 * 3^1 * 43^1.
//! The answer is (1+1)*(1+1)*(1+1) - (prime factor1 + prime factor2 + prime factor3) = 5.
//!
//! A simpler, an probably more efficient way of solving this problem is 
//! to modify Sieve of Eratosthenes and cross out all the prime numbers.
//! Then, you'll be left with non-prime factors. The rest of the calculations is trivial.

/*algorithm Sieve of Eratosthenes is
    input: an integer n > 1.
    output: all prime numbers from 2 through n.

    let A be an array of Boolean values, indexed by integers 2 to n,
    initially all set to true.
    
    for i = 2, 3, 4, ..., not exceeding √n do
        if A[i] is true
            for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n do
                A[j] := false

    return all i such that A[i] is true.*/

    template<int32_t SIZE>
    void sieve(array<bool, SIZE>& primeArray)
    {
        primeArray.fill(true);
        for(int i = 2; i <= sqrt(SIZE); ++i)
        {
            if(primeArray[i])
            {
                for(int j = 2*i; j <= SIZE; j = j + i)
                {
                    primeArray[j] = false;
                }
         }
        }
    }

int main()
{
    // Since the number of inputs is 3M, and the largest input number is 2M, there will be duplicates.
    // Using the map, we can do lookups and retrieve answers to numbers which already have been processed. 
    unordered_map<int,int> mapWithValues;

    std::array<bool,2000001> primeArray; 
    sieve<2000001>(primeArray);
    const int nrOfPrimesUpToSqrt = 350; // Approximate amount of prime numbers up to sqrt(2M)
    std::array<int, nrOfPrimesUpToSqrt> primesUpToSqrt2M;
    
    int j = 0;
    for(int i = 2; i <= sqrt(2000001); ++i) // sqrt(2M) = 1414.2
    {
        if(primeArray[i])
        {
            primesUpToSqrt2M[j] = i;
            j++;
        }
    }
    for(int i = j; j < nrOfPrimesUpToSqrt; ++j)
    {
        primesUpToSqrt2M[j] = numeric_limits<int>::max();
    } 

    int n;
    scanf("%d", &n);
    int num;
    int originalNum;
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &num);
        originalNum = num;
        auto it = mapWithValues.find(originalNum); // Try to see if we already have processed this number.
        if(it != mapWithValues.end())
        {
            printf("%d \n", it->second);
            continue;
        }
            // This vector contains the exponents for each prime factor.
            // The answer should be all (exponent1 + 1)*(exponent2 +1)*... minus the number of exponents.
            vector<int> exponents;
            exponents.reserve(7); 
            int k = 0;
            int sqrtNum = sqrt(num);
            int numberOfThesamePrime = 1;
            while(primesUpToSqrt2M[k] <= sqrtNum)
            {
                while(num % primesUpToSqrt2M[k] == 0)
                {
                    numberOfThesamePrime++;
                    num /= primesUpToSqrt2M[k];

                    if(primeArray[num] && primesUpToSqrt2M[k] == num) // This number is the same prime we are dividing with.
                    {
                        numberOfThesamePrime++;
                        exponents.push_back(numberOfThesamePrime);
                        break; // We have come to a prime, i.e. we have found all prime numbers.
                    }
                    else if(primeArray[num] && num > sqrtNum)// This number is a prime, larger tahn sqrt.
                    {
                        exponents.push_back(numberOfThesamePrime);
                        // If a prime is larger than sqrt of the number, it cannot be a factor which appears more than once.
                        exponents.push_back(2); 
                        break;
                    } 
                    else if(num % primesUpToSqrt2M[k] != 0)
                    {
                        exponents.push_back(numberOfThesamePrime);
                        break;// Cannot divide the number with this prime factor anymore.
                    } 
                }
                numberOfThesamePrime = 1;
                k++;
            }
            int ans = 1;
            for(int j = 0; j < exponents.size(); ++j)
            {
                ans *= exponents[j];
            }

            int res = ans-exponents.size();
            
            printf("%d \n", res);
            mapWithValues.insert({originalNum,res});
    }

    return 0;
}