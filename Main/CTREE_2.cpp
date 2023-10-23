#include "CTREE_2.h"
CTREE_2::CTREE_2(int x, int y, int isRight) {
    this->x = x; this->y = y; this->isRight = isRight;
    vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;
    for (int i = 0; i < frame.size(); i++)
        for (int j = 0; j < frame[i].length(); j++)
            this->block[x + j][y + i] = { frame[i][j], BLACK, -1 };
    if (isRight) {
        
    }
    else {
        block[x][y].txtColor = DARK_RED;
        block[x][y].txtColor = DARK_RED;
        block[x + 1][y].txtColor = DARK_RED;
        block[x + 7][y].txtColor = DARK_RED;
        block[x + 8][y].txtColor = DARK_RED;
        block[x + 6][y].txtColor = SKY_BLUE;
        block[x + 9][y].txtColor = BRIGHT_YELLOW;
        block[x + 2][y + 1].txtColor = DARK_RED;
        block[x + 2][y + 1].bgdColor = RED;
        block[x + 3][y + 1].txtColor = DARK_RED;
        block[x + 3][y + 1].bgdColor = RED;
        block[x + 4][y + 1].txtColor = DARK_RED;
        block[x + 4][y + 1].bgdColor = RED;
        block[x + 5][y + 1].txtColor = DARK_RED;
        block[x + 5][y + 1].bgdColor = RED;
        block[x + 6][y + 1].txtColor = SKY_BLUE;
        block[x][y + 2].txtColor = DARK_RED;
        block[x + 1][y + 2].txtColor = DARK_RED;
        block[x + 6][y + 2].txtColor = DARK_RED;
        block[x + 2][y + 2].txtColor = DARK_RED;
        block[x + 2][y + 2].bgdColor = SKY_BLUE;
        block[x + 3][y + 2].txtColor = DARK_RED;
        block[x + 3][y + 2].bgdColor = SKY_BLUE;
        block[x + 4][y + 2].txtColor = DARK_RED;
        block[x + 4][y + 2].bgdColor = SKY_BLUE;
        block[x + 5][y + 2].txtColor = DARK_RED;
        block[x + 5][y + 2].bgdColor = SKY_BLUE;
        block[x + 7][y + 2].txtColor = DARK_RED;
        block[x + 7][y + 2].bgdColor = RED;
        block[x + 8][y + 2].txtColor = DARK_RED;
        block[x + 8][y + 2].bgdColor = RED;
        block[x + 9][y + 2].txtColor = BRIGHT_YELLOW;
        block[x + 9][y + 2].bgdColor = RED;
        block[x + 1][y + 3].txtColor = BLACK;
        block[x + 2][y + 3].txtColor = BLACK;
        block[x + 6][y + 3].txtColor = BLACK;
        block[x + 7][y + 3].txtColor = BLACK;
    }
}

