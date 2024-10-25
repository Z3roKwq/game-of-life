//
// Created by Z3roKwq on 10/23/2024.
//

#ifndef CONSOLE_H
#define CONSOLE_H

#include <utility>

class Console {
public:
   static void Clear();
   static void Print(const unsigned char* buffer, unsigned int size);

   static std::pair<int, int> GetSize();
};

#endif //CONSOLE_H