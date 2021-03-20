#include "Patterns.h"

namespace Patterns{
      const char SQUARE_ORIENTATION[4][4][2] = {
            {{0,0}, {0,1}, {1,0}, {1,1}},
            {{0,0}, {0,1}, {1,0}, {1,1}},
            {{0,0}, {0,1}, {1,0}, {1,1}},
            {{0,0}, {0,1}, {1,0}, {1,1}}
      };
      const char LINE_ORIENTATION[4][4][2] = {
            {{0,0}, {1,0}, {2,0}, {3,0}},
            {{2,-1}, {2,0}, {2,1}, {2,2}},
            {{0,0}, {1,0}, {2,0}, {3,0}},
            {{2,-1}, {2,0}, {2,1}, {2,2}}
      };
      const char T_ORIENTATION[4][4][2] = {
            {{0,1}, {1,1}, {1,0}, {2,1}},
            {{1,0}, {1,1}, {1,2}, {2,1}},
            {{0,1}, {1,1}, {1,2}, {2,1}},
            {{0,1}, {1,0}, {1,1}, {1,2}}
      };
      const char L_ORIENTATION[4][4][2] = {
            {{0,0}, {1,0}, {2,0}, {2,1}},
            {{1,-1}, {1,0}, {1,1}, {2,-1}},
            {{0,0}, {0,-1}, {1,0}, {2,0}},
            {{0,1}, {1,-1}, {1,0}, {1,1}}
      };
      const char RL_ORIENTATION[4][4][2] = {
            {{0,0}, {1,0}, {2,0}, {0,1}},
            {{1,-1}, {1,0}, {1,1}, {2,1}},
            {{0,0}, {2,-1}, {1,0}, {2,0}},
            {{0,-1}, {1,-1}, {1,0}, {1,1}}
      };
      const char S_ORIENTATION[4][4][2] = {
            {{0,0}, {1,0}, {1,1}, {2,1}},
            {{1,1}, {1,2}, {2,0}, {2,1}},
            {{0,0}, {1,0}, {1,1}, {2,1}},
            {{1,1}, {1,2}, {2,0}, {2,1}}
      };
      const char Z_ORIENTATION[4][4][2] = {
            {{1,0}, {2,0}, {0,1}, {1,1}},
            {{1,0}, {1,1}, {2,1}, {2,2}},
            {{1,0}, {2,0}, {0,1}, {1,1}},
            {{1,0}, {1,1}, {2,1}, {2,2}}
      };
}