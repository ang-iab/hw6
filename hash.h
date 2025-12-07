#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        int pairs = static_cast<int>((k.length() + 5) / 6);

        for (int i = 0; i < pairs; ++i)
        {
            int end = static_cast<int>(k.length() - 6 * i);
            int start = std::max(0, end - 6);
            std::string substr = k.substr(start, end - start);

            w[4 - i] = convert36ToDec(substr);
        }

        return rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
    }

    // Convert Base-36 to Decimal
    unsigned long long convert36ToDec(const std::string str) const
    {
        unsigned long long decimal = 0;
        int j = 6 - static_cast<int>(str.length());

        for (int i = 0; i < 6; ++i)
        {
            HASH_INDEX_T d;

            if (i < j) d = 0;
            else d = letterDigitToNumber(str[i - j]);
            
            decimal = decimal * 36 + d;
        }

        return decimal;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T n;
        letter = static_cast<char>(std::tolower(letter));

        if (letter > '9')
        {
            n = letter -  'a'; 
        }
        else
        {
            n = letter - '0' + 26;
        }

        return n;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
