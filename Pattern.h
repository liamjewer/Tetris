#pragma once

struct Pattern{
      Pattern(int, const char [4][4][2]);

      int colour;
      int rotation;
      int minX;
      int minY;
      int maxX;
      int maxY;

      const char (*pattern)[4][2];
      void calcMinX();
      void calcMaxX();
      void calcMinY();
      void calcMaxY();
      void rotate();
};