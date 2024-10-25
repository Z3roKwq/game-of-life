#include "game.h"

Game* g_pGame;

int main() {
   g_pGame = new Game();

   g_pGame->Process();

   delete g_pGame;
}