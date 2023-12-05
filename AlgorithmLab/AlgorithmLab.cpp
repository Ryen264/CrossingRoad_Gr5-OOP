//#include "CGAME.h"
#include <deque>
#include <iostream>
using namespace std;
ostream& operator<<(ostream& out, const deque<int>& arr) {
    for (int i = 0; i < (int)arr.size(); i++)
        out << arr[i] << " ";
    return out;
}
void move(deque<int>& arr, int redPoint) {
    int size = (int)arr.size();
    //push after
    if (redPoint < size - 1) {
        arr.insert(arr.begin() + redPoint + 1, 0);
        arr.pop_back();
    }
    //push front
    int id = redPoint - 1;
    for (; id >= 0 && arr[id] != 0; id--);
    if (id >= 0) {
        arr.erase(arr.begin() + id);
        arr.push_front(9);
    }
}

ostream& operator<<(ostream& out, const deque<int*>& arr) {
    for (int i = 0; i < (int)arr.size(); i++)
        out << ((arr[i] != NULL) ? *arr[i] : 0) << " ";
    return out;
}
void move(deque<int*>& arr, bool isRight = true, int redPoint = -1) {
    //push normally
    if (redPoint < 0) {
        int val = rand() % 2;
        (isRight) ? arr.push_front((val != 0) ? new int(val) : NULL) : arr.push_back((val != 0) ? new int(val) : NULL);
        (isRight) ? arr.pop_back() : arr.pop_front();
    }
    int size = (int)arr.size();
    //push after
    if (redPoint < size - 2) {
        (isRight) ? arr.insert(arr.begin() + redPoint + 1, NULL) : arr.insert(arr.begin() + redPoint - 1, NULL);
        (isRight) ? arr.pop_back() : arr.pop_front();
    }
    //push front
    int id = redPoint;
    if (isRight) {
        for (; id >= 0 && arr[id] != NULL; id--);
        if (id >= 0) {
            arr.erase(arr.begin() + id);
            int val = rand() % 2;
            arr.push_front((val != 0) ? new int(val) : NULL);
        }
    }
    else {
        for (; id < size && arr[id] != NULL; id++);
        if (id < size) {
            arr.erase(arr.begin() + id);
            int val = rand() % 2;
            arr.push_back((val != 0) ? new int(val) : NULL);
        }
    }
}
deque<int*> initDeque(const deque<int>& src) {
    deque<int*> arr{};
    for (int i = 0; i < (int)src.size(); i++)
        arr.push_back((src[i] != 0) ? new int(src[i]) : NULL);
    return arr;
}
void deleteDeque(deque<int*>& arr) {
    int size = (int)arr.size();
    while (!arr.empty()) {
        int* tmp = arr.back();
        arr.pop_back();
        if (tmp != NULL) delete tmp;
    }
    arr.clear();
}

/*
        v
0 1 2 3 4 5 6 7 8 9
x   x   x     x x
y x   x x       x x

x   x   x     x x
  x     x   x x   y
*/

void push(deque<int>& lane, bool isMoveRight, int lightPos) {
    //push after
    if (lane[lightPos] != NULL && lane[lightPos] == 3) {
        if (isMoveRight) {
            if (lightPos > 0) lane.insert(lane.begin() + lightPos - 1, 0);
            else lane.push_front(4);
        }
        else {
            if (lightPos < 10 - 2) lane.insert(lane.begin() + lightPos + 2, 0);
            else if (lightPos == 10 - 2) lane.push_back(0);
            else lane.push_back(4);
        }
    }
    else {
        if (isMoveRight) lane.insert(lane.begin() + lightPos, 0);
        else {
            if (lightPos < 10 - 1) lane.insert(lane.begin() + lightPos + 1, 0);
            else lane.push_back(0);
        }
    }
    if (isMoveRight) lane.pop_back();
    else lane.pop_front();
    //push before
    if (isMoveRight) {
        int id = lightPos - 1;
        for (; id >= 0 && lane[id] != 0; id--);
        if (id >= 0) {
            lane.erase(lane.begin() + id);
            if (isMoveRight) lane.push_front(8);
            else lane.push_back(8);
        }
    }
    else {
        int id = lightPos + 1;
        for (; id < 10 && lane[id] != 0; id++);
        if (id < 10) {
            lane.erase(lane.begin() + id);
            if (isMoveRight) lane.push_front(8);
            else lane.push_back(8);
        }
    }
}

int main() {
    srand(0);
    //                              v
    deque<int> arr1 = { 1, 0, 2, 4, 0, 0, 0, 0, 9, 0 };
    deque<int> arr2 = { 0, 9, 0, 1 ,0, 4, 0, 2, 0, 1 };
    //deque<int*> brr = initDeque(arr);

    bool isRight = true;
    int lightPos = 4;

    cout << arr1 << endl;
    for (int i = 0; i < 5; i++) {
        push(arr1, true, lightPos);
        cout << arr1 << endl;
    }

    cout << endl << endl;

    cout << arr2 << endl;
    for (int i = 0; i < 5; i++) {
        push(arr2, false, lightPos);
        cout << arr2 << endl;
    }

    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;
    //move(brr, false, 4);
    //cout << brr << endl;

    //deleteDeque(brr);

    /*CGAME testGame;
    testGame.start();*/
    return 0;
}