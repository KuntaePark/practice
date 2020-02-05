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
int to[MAX][MAX];
queue<tuple<int, char>> dirq;
int head[2] = {0,0};
int tail[2] = {0,0};
int hd = RIGHT;
int n = 0;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

bool move() {
    int hy, hx, nhy, nhx;
    int td = -1;
    hy = head[0];
    hx = head[1];
    nhy = hy + dy[hd];
    nhx = hx + dx[hd];
    if(nhy < 0 || nhy >= n || nhx < 0 || nhx >= n) return false;
    if(map[nhy][nhx] == 1) return false;

    head[0] = nhy;
    head[1] = nhx;
    to[hy][hx] = hd;
    if(map[nhy][nhx] == 0) {
        td = to[tail[0]][tail[1]];
        map[tail[0]][tail[1]] = 0;
        to[tail[0]][tail[1]] = -1;
        tail[0] += dy[td];
        tail[1] += dx[td];
    }
    map[nhy][nhx] = 1; 
    return true;

}

int main() {
    int k,l,x;
    int ax, ay;
    int count = 0;
    char c;
    tuple<int, char> cur;

    for(int i = 0; i < MAX; i++) for(int j = 0; j < MAX; j++) map[i][j] = 0;
    for(int i = 0; i < MAX; i++) for(int j = 0; j < MAX; j++) to[i][j] = -1;

    map[0][0] = 1;
    to[0][0] = RIGHT;

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

    while(1) {
        count++;
        if(!move()) break;
        cur = dirq.front();
        if(count == get<0>(cur)) {
            if(get<1>(cur) == 'D') hd =(hd+1) % 4;
            else hd = (hd+3) % 4;
            to[head[0]][head[1]] = hd;
            dirq.pop();
        }

    }

    std::cout<<count;
}