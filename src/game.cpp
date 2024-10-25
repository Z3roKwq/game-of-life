//
// Created by Z3roKwq on 10/23/2024.
//

#include "game.h"
#include "renderer/renderer.h"
#include "renderer/drawlist.h"
#include "utils/keyboard.h"

#include <cstring>
#include <thread>
#include <chrono>
#include <random>

Game::Game()
   : isRunning(false)
   , paragraph(0)
   , generations(1000)
   , generationTimeout(1)
   , probabilityLife(50)
{
   #if defined(__linux__) || defined(__APPLE__)
      Keyboard::SetNonCanonicalMode(true);
   #endif

   m_pRenderer = new Renderer();
   m_pDrawList = new DrawList(m_pRenderer);
}

Game::~Game() {
   #if defined(__linux__) || defined(__APPLE__)
      Keyboard::SetNonCanonicalMode(false);
   #endif

   delete m_pDrawList;
   delete m_pRenderer;
}

void Game::Process() {
   isRunning = true;
   while (isRunning) {
      m_pRenderer->Update();
      m_pRenderer->Clear();

      if (paragraph == MENU) {
         static int id{1};

         switch (Keyboard::GetPressedKey()) {
            case (KEY_UP): { if (id > 1) --id; break; }
            case (KEY_DOWN): { if (id < 3) ++id; break; }

            case (KEY_ENTER): {
               if (id == 1) paragraph = PLAY;
               if (id == 2) paragraph = SETTINGS;
               if (id == 3) paragraph = isRunning = false;
               break;
            }

            default: { break; }
         }

         m_pDrawList->DrawCenteredTitle();
         m_pDrawList->DrawCenteredText(1, "Launch",   (id == 1));
         m_pDrawList->DrawCenteredText(2, "Settings", (id == 2));
         m_pDrawList->DrawCenteredText(3, "Quit",     (id == 3));
      } else if (paragraph == PLAY) {
         const unsigned int size = m_pRenderer->frameBufferSize;
         unsigned char* grid = new unsigned char[size + 1];
         memset(grid, ' ', size);
         grid[size] = '\0';

         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_real_distribution<float>dis(0.0, 1.0);
         for (int y = 0; y < m_pRenderer->consoleSize.second; y++) {
            for (int x = 0; x < m_pRenderer->consoleSize.first; x++)
               grid[y * m_pRenderer->consoleSize.first + x] = (dis(gen) < (probabilityLife * 0.01)) ? '@' : ' ';
         }

         const auto countAliveNeighbors = [&](const int cx, const int cy) {
            int count = 0;
            for (int dy = -1; dy <= 1; dy++) {
               for (int dx = -1; dx <= 1; dx++) {
                  if (dx == 0 && dy == 0) continue;
                  int nx = cx + dx, ny = cy + dy;
                  if ((nx > 0 && nx < m_pRenderer->consoleSize.first) && (ny > 0 && ny < m_pRenderer->consoleSize.second) && (grid[ny * m_pRenderer->consoleSize.first + nx] != ' ')) ++count;
               }
            }
            return count;
         };

         for (int i = 0; i < generations; i++) {
            m_pRenderer->Clear();

            auto* newGrid = new unsigned char[size + 1];
            memcpy(newGrid, grid, size);

            for (int y = 0; y < m_pRenderer->consoleSize.second; y++) {
               for (int x = 0; x < m_pRenderer->consoleSize.first; x++) {
                  const int aliveNeighbors = countAliveNeighbors(x, y);
                  if (newGrid[y * m_pRenderer->consoleSize.first + x] != ' ')
                     newGrid[y * m_pRenderer->consoleSize.first + x] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? '@' : ' ';
                  else
                     newGrid[y * m_pRenderer->consoleSize.first + x] = (aliveNeighbors == 3) ? '@' : ' ';
               }
            }

            memcpy(m_pRenderer->frameBackBuffer, newGrid, size);
            memcpy(grid, newGrid, size);
            delete[] newGrid;

            m_pDrawList->DrawCenteredTextWithCounter(0, "Generation:", false, i, generations);

            m_pRenderer->SwapBuffers();
            m_pRenderer->Render();

            std::this_thread::sleep_for(std::chrono::milliseconds(generationTimeout));
         }

         delete[] grid;

         paragraph = MENU;
      } else if (paragraph == SETTINGS) {
         static constexpr int maxGenerations{10000};
         static constexpr int maxGenerationTimeout{100};
         static constexpr int maxProbabilityAppearingLife{70};

         static int id{1};

         switch (Keyboard::GetPressedKey()) {
            case (KEY_UP): { if (id > 1) --id; break; }
            case (KEY_DOWN): { if (id < 4) ++id; break; }

            case (KEY_LEFT): {
               if (id == 1) if (generations > 10) --generations;
               if (id == 2) if (generationTimeout > 1) --generationTimeout;
               if (id == 3) if (probabilityLife > 1) --probabilityLife;
               break;
            }
            case (KEY_RIGHT): {
               if (id == 1) if (generations < maxGenerations) ++generations;
               if (id == 2) if (generationTimeout < maxGenerationTimeout) ++generationTimeout;
               if (id == 3) if (probabilityLife < maxProbabilityAppearingLife) ++probabilityLife;
               break;
            }
            case (KEY_ENTER): {
               if (id == 4) paragraph = MENU;
               break;
            }

            default: { break; }
         }

         m_pDrawList->DrawCenteredTitle();
         m_pDrawList->DrawCenteredTextWithCounter(1, "Number of generations:", (id == 1), generations, maxGenerations);
         m_pDrawList->DrawCenteredTextWithCounter(2, "Generation timeout (in ms.):", (id == 2), generationTimeout, maxGenerationTimeout);
         m_pDrawList->DrawCenteredTextWithCounter(3, "Probability appearing life (in %):", (id == 3), probabilityLife, maxProbabilityAppearingLife);
         m_pDrawList->DrawCenteredText(4, "Back", (id == 4));
      }

      m_pRenderer->SwapBuffers();
      m_pRenderer->Render();

      std::this_thread::sleep_for(std::chrono::milliseconds(1));
   }
}