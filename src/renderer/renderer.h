//
// Created by Z3roKwq on 10/23/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <utility>

class Renderer {
   friend class DrawList;
   friend class Game;

public:
   Renderer();
   ~Renderer();

   void Update();
   void Clear();
   void SwapBuffers();
   void Render();

private:
   void Initialize();

protected:
   std::pair<int, int> consoleSize;
   unsigned int frameBufferSize;
   unsigned char* frameBackBuffer;
   unsigned char* frameFrontBuffer;
};

#endif //RENDERER_H