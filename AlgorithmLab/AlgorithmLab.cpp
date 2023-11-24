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

int main() {
    srand(0);
    deque<int> arr = { 1, 0, 2, 3, 3, 0, 0, 0, 9, 0 };
    deque<int*> brr = initDeque(arr);

    cout << arr << endl;
    arr.insert(arr.begin() + 4, 9);
    cout << arr << endl;

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

    deleteDeque(brr);

    /*CGAME testGame;
    testGame.start();*/
    return 0;
}