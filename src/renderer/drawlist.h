//
// Created by Z3roKwq on 10/23/2024.
//

#ifndef DRAWLIST_H
#define DRAWLIST_H

class Renderer;

class DrawList {
   Renderer*& m_pRenderer;

public:
   explicit DrawList(Renderer*& pRenderer);
   ~DrawList();

   void DrawCenteredTitle() const;
   void DrawCenteredText(int id, const char* text, bool highlighted) const;
   void DrawCenteredTextWithCounter(int id, const char* text, bool highlighted, int value, int maxValue) const;
};

#endif //DRAWLIST_H