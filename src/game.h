//
// Created by Z3roKwq on 10/23/2024.
//

#ifndef GAME_H
#define GAME_H

class Renderer;
class DrawList;

class Game {
   Renderer* m_pRenderer;
   DrawList* m_pDrawList;

public:
   Game();
   ~Game();

   void Process();

private:
   enum Paragraphs {
      MENU,
      PLAY,
      SETTINGS
   };

   bool isRunning;
   int paragraph;
   int generations;
   int generationTimeout;
   int probabilityLife;
};

#endif //GAME_H