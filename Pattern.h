#pragma once

struct Pattern{
      Pattern(int, const char [4][4][2]);

      int colour;
      int rotation;
      const char (*pattern)[4][2];
      int getWidth();
      void rotate();
};