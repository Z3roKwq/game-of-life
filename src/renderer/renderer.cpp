//
// Created by Z3roKwq on 10/23/2024.
//

#include "renderer.h"
#include "../utils/console.h"

#include <cstring>
#include <utility>

Renderer::Renderer()
   : consoleSize(0, 0)
   , frameBufferSize(0)
   , frameBackBuffer(nullptr)
   , frameFrontBuffer(nullptr)
{
   Initialize();
}

Renderer::~Renderer() {
   delete[] frameBackBuffer;
   delete[] frameFrontBuffer;
}

void Renderer::Initialize() {
   consoleSize = Console::GetSize();

   frameBufferSize = consoleSize.first * consoleSize.second;

   delete[] frameBackBuffer;
   frameBackBuffer = new unsigned char[frameBufferSize + 1];
   memset(frameBackBuffer, ' ', frameBufferSize);
   frameBackBuffer[frameBufferSize] = '\0';

   delete[] frameFrontBuffer;
   frameFrontBuffer = new unsigned char[frameBufferSize + 1];
   memset(frameFrontBuffer, ' ', frameBufferSize);
   frameFrontBuffer[frameBufferSize] = '\0';
}

void Renderer::Update() {
   const std::pair<int, int> actualConsoleSize = Console::GetSize();
   if (consoleSize != actualConsoleSize)
      Initialize();
}

void Renderer::Clear() {
   Console::Clear();
   memset(frameBackBuffer, ' ', frameBufferSize);
}

void Renderer::SwapBuffers() {
   std::swap(frameFrontBuffer, frameBackBuffer);
}

void Renderer::Render() {
   Console::Print(frameFrontBuffer, frameBufferSize);
}