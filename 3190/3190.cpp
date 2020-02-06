#include <iostream>
#include <cstring>
#include <tuple>
#include <queue>

#define MAX 100

using namespace std;

enum direction {
    UP,
    RIGHT,
    LEFT,
    DOWN
};

int map[MAX][MAX]; // 0:empty 1:body 2:apple
int connectTo[MAX][MAX];
queue<tuple<int, char>> dirq;

int hx,hy;
int ty,tx;
int headDirection = RIGHT;
int n = 0;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

void rotatehD(char rotatingDirection) {
    if(rotatingDirection == 'D') headDirection = (headDirection+1) % 4;
    else headDirection = (headDirection+3) % 4;
}

bool isStop() {
    int nhy,nhx;
    nhy = hy + dy[headDirection];
    nhx = hx + dx[headDirection];
    if(nhy < 0 || nhy >= n || nhx < 0 || nhx >= n) return true;
    if(map[nhy][nhx] == 1) return true;
    else return false;

}

void move() {
    int nhy, nhx;
    int tailDirection;

    nhy = hy + dy[headDirection];
    nhx = hx + dx[headDirection];
    hy = nhy;
    hx = nhx;

    connectTo[hy][hx] = headDirection;

    if(map[nhy][nhx] == 0) {
        tailDirection = connectTo[ty][tx];
        map[ty][tx] = 0;
        connectTo[ty][tx] = -1;
        ty += dy[tailDirection];
        tx += dx[tailDirection];
    }
    map[nhy][nhx] = 1; 
}

int main() {
    int k,l,x;
    int ax, ay;
    int count = 0;
    char c;
    tuple<int, char> nextChange;

    hy = 0;
    hx = 0;
    ty = 0;
    tx = 0;

    for(int i = 0; i < MAX; i++) for(int j = 0; j < MAX; j++) map[i][j] = 0;
    for(int i = 0; i < MAX; i++) for(int j = 0; j < MAX; j++) connectTo[i][j] = -1;

    map[0][0] = 1;
    connectTo[0][0] = RIGHT;

    scanf("%d", &n);
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        scanf("%d %d", &ay, &ax);
        map[ay-1][ax-1] = 2;

    }
    scanf("%d", &l);
    for(int i = 0; i < l; i++) {
        scanf("%d %c", &x, &c);
        dirq.push(make_tuple(x,c));
    }

    while(!isStop()) {
        count++;
        move();
        nextChange = dirq.front();
        if(count == get<0>(nextChange)) {
            rotatehD(get<1>(nextChange));
            connectTo[hy][hx] = headDirection;
            dirq.pop();
        }
    }

    std::cout<<count+1;
}