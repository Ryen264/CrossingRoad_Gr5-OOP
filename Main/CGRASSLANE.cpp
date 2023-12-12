#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int x, int y, vector<int> typeLane) : CLANE(x, y) {
    bool haveEgg = false, haveTree = false; int countTree = 0;
    if (typeLane.empty())
    {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            //Random push a egg or no more than 3 trees or NULL
            int random = rand() % 20;
            if (random == 0 && !haveEgg) {
                pushObject(EGG_ID);
                haveEgg = true;
            }
            else if (random % 5 == 0 && !haveTree) {
                pushObject((rand() % 2) ? TREE_DOUBLE_ID : TREE_SINGLE_ID);
                countTree++;
                if (countTree >= MAX_NUMBER_OF_TREE) haveTree = true;
            }
            else lane.push_front(NULL);
        }
    }
    else {
        for (int i = BOARD_WIDTH - 1; i >= 0; i--)
            if (typeLane[i] != 0) pushObject(typeLane[i]);
            else lane.push_front(NULL);
    }

    this->ID = GRASSLANE_ID;

    //set buffer
    for (int i = 0; i < BLOCK_WIDTH; i++)
        for (int j = 0; j < BLOCK_HEIGHT; j++)
            this->block[i][j] = { FRAME[j][i], DARK_GREEN, LIGHT_GREEN };
}

void CGRASSLANE::injuredPlayer(CPLAYER& player) {}
void CGRASSLANE::pushObject(int ID) {
    if (isMoveRight) {
        switch (ID) {
        case EGG_ID: {
            lane.push_front(new CEGG);
            break;
        }
        case TREE_DOUBLE_ID: {
            lane.push_front(new CTREE(0, this->y, true));
            break;
        }
        case TREE_SINGLE_ID: {
            lane.push_front(new CTREE(0, this->y, false));
            break;
        }
        default:
            lane.push_front(NULL);
        }
    }
    else {
        switch (ID) {
        case EGG_ID: {
            lane.push_back(new CEGG);
            break;
        }
        case TREE_DOUBLE_ID: {
            lane.push_back(new CTREE(0, this->y, true));
            break;
        }
        case TREE_SINGLE_ID: {
            lane.push_back(new CTREE(0, this->y, false));
            break;
        }
        default:
            lane.push_back(NULL);
        }
    }
    updatePosObj();
}
void CGRASSLANE::push_backObject(int ID) {
    switch (ID) {
    case EGG_ID: {
        lane.push_back(new CEGG);
        break;
    }
    case TREE_DOUBLE_ID: {
        lane.push_back(new CTREE(0, this->y, true));
        break;
    }
    case TREE_SINGLE_ID: {
        lane.push_back(new CTREE(0, this->y, false));
        break;
    }
    default:
        lane.push_back(NULL);
    }
    updatePosObj();
}
void CGRASSLANE::DrawLane(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++)
        if (rand() % 3 == 0) {
            for (int i = 0; i < BLOCK_WIDTH; i++)
                for (int j = 0; j < BLOCK_HEIGHT; j++)
                    layer.screen[x + i + k * BLOCK_WIDTH][y + j] = block[i][j];
        }
        else {
            for (int i = 0; i < BLOCK_WIDTH; i++)
                for (int j = 0; j < BLOCK_HEIGHT; j++)
                    layer.screen[x + i + k * BLOCK_WIDTH][y + j] = { L' ', LIGHT_GREEN, LIGHT_GREEN };
        }
}
