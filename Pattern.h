#pragma once

struct Pattern{
      Pattern(int, const bool [4][4][4]);

      int colour;
      const bool (*orientation)[4][4];
};