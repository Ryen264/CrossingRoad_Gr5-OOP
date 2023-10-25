#include "CLANE.h"
CLANE::CLANE(int width, int x, int y) {
    this->numberOfBlock = 1;
    this->x = x; this->y = y;

    //set buffers
    for (int i = 0; i < BLOCKLENGTH; i++)
        for (int j = 0; j < BLOCKHEIGHT; j++)
            this->block[i][j] = { FRAME[j][i], WHITE, LIGHT_GRAY };

    //set colors
    for (int i = 0; i < 16; i++)
        this->block[i][0].bgdColor = DARK_GREEN;
    for (int i = 0; i < 16; i++)
        if (i % 4 != 3) this->block[i][3].txtColor = BRIGHT_YELLOW;
}
void CLANE::DrawBlock(CGRAPHIC& layer) {
    if (this->numberOfBlock == 1) {
        for (int i = 0; i < BLOCKLENGTH; i++)
            for (int j = 0; j < BLOCKHEIGHT; j++)
                layer.screen[this->x + i][this->y + j] = block[i][j];
    }
}
