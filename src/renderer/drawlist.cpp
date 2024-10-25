//
// Created by Z3roKwq on 10/23/2024.
//

#include "drawlist.h"
#include "renderer.h"

#include <cstdio>
#include <cstring>

DrawList::DrawList(Renderer*& pRenderer)
   : m_pRenderer(pRenderer)
{ }

DrawList::~DrawList() = default;

void DrawList::DrawCenteredTitle() const {
   static constexpr int size = 5;
   static const char* title[size] = {
      "   _________    __  _________     ____  ______    __    ________________",
      "  / ____/   |  /  |/  / ____/    / __ \\/ ____/   / /   /  _/ ____/ ____/",
      " / / __/ /| | / /|_/ / __/______/ / / / /_______/ /    / // /_  / __/   ",
      "/ /_/ / ___ |/ /  / / /__/_____/ /_/ / __/_____/ /____/ // __/ / /___   ",
      "\\____/_/  |_/_/  /_/_____/     \\____/_/       /_____/___/_/   /_____/   "
   };

   for (int i = 0; i < size; i++) {
      const char* text = title[i];
      const int length = strlen(text);

      const int x = (m_pRenderer->consoleSize.first - length) / 2;
      const int y = (m_pRenderer->consoleSize.second - size) / 7 + i;

      for (int c = 0; c < length; c++)
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + c] = text[c];
   }
}

void DrawList::DrawCenteredText(const int id, const char* text, const bool highlighted) const {
   static int lastNumber = 0;
   if (id > lastNumber) lastNumber = id;

   const int length = strlen(text);

   const int x = (m_pRenderer->consoleSize.first - length) / 2;
   const int y = (m_pRenderer->consoleSize.second - lastNumber) / 2 + id + 1;

   for (int c = 0; c < length; c++) {
      if (!highlighted) {
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + c] = text[c];
      } else {
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x - 1] = '~';
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + c] = text[c];
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + length] = '~';
      }
   }
}

void DrawList::DrawCenteredTextWithCounter(const int id, const char* text, const bool highlighted, const int value, const int maxValue) const {
   static int lastNumber = 0;
   if (id > lastNumber) lastNumber = id;

   char buffer[256];
   snprintf(buffer, sizeof(buffer), "%s %d/%d", text, value, maxValue);
   const int length = strlen(buffer);

   const int x = (m_pRenderer->consoleSize.first - length) / 2;
   const int y = (m_pRenderer->consoleSize.second - lastNumber) / 2 + id + 1;

   for (int c = 0; c < length; c++) {
      if (!highlighted) {
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + c] = buffer[c];
      } else {
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x - 1] = '~';
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + c] = buffer[c];
         m_pRenderer->frameBackBuffer[y * m_pRenderer->consoleSize.first + x + length] = '~';
      }
   }
}