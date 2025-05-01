#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
      
      unsigned long long w[5] = {0, 0, 0, 0, 0};
      int trackSize = k.length();
      
      // For the number of groups of 6 characters
      int totalGroups = 4;
      // For the starting position in the array
      int index = trackSize - 1;

      while (totalGroups >= 0 && index >= 0) {

        unsigned long long now = 0;
        // For the formula
        unsigned long long exponent = 1;

        for (int i = 0; i < 6 && index >= 0; i++) {

          HASH_INDEX_T add = letterDigitToNumber(k[index]);
          now += add * exponent;
          exponent *= 36;

          index--;
        }
        
        w[totalGroups] = now;
        totalGroups--;
      }

      unsigned long long output = 0;

      for (int i = 0; i < 5; i++) {
        output += w[i] * rValues[i];
      }

      return output;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      
      // First we must convert all lowercase letters to uppercase to keep our
      // conversions and checks consistent
      if (letter >= 'A' && letter <= 'Z') {
        letter = letter - 'A' + 'a';
      }
       
      // Now we must assign the letter to actual numbers based on if they are
      // letters or numbers (use ASCII)
      if (letter >= 'a' && letter <= 'z') {
        return letter - 'a';
      } 
      // Strings are said to only contain letters or numbers, so this branch is
      // for numbers
      else  {
        return letter - '0' + 26;
      }

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
