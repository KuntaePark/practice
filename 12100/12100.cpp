#include <iostream>
#include <cstring>
#include <string>

#define MAX 20
//12100
int max = 0;
int dyx[2][4] ={{-1,1,0,0},{0,0,-1,1}};

void printArray(int map[][MAX], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cout<< map[i][j] << " ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void move(int _map[][MAX], int size, int n) {

    int map[MAX][MAX];
    bool merged[MAX][MAX];
    std::cout<<n<<std::endl;
    printArray(_map, size);

    if(n >= 5) {return;}

    for(int i = 0; i < 4; i++) {
        //std::cout<<"direction: "<<i<<std::endl;
        std::copy(&_map[0][0], &_map[0][0] + MAX * MAX, &map[0][0]);
        for(int a = 0; a < MAX; a++) for (int b = 0; b < MAX; b++) {merged[a][b] = false;}

        for(int j = 0; j < size; j++) for(int k = 0; k < size; k++) {
            int y,x,ny,nx;

            y = (size-1) * (((1+dyx[0][i])/2) + ((1-dyx[1][i])/2)) - dyx[0][i] * j + dyx[1][i] * k;
            x = (size-1) * (((1+dyx[1][i])/2) + ((1+dyx[0][i])/2)) - dyx[1][i] * j - dyx[0][i] * k;
//            std::cout<<y<<","<<x<<std::endl;
            ny = y + dyx[0][i];
            nx = x + dyx[1][i];

            while(1) {
                if(map[y][x] == 0) {break;}
                if(ny < 0 || ny >= size || nx < 0 || nx >= size) {
                    break;
                } else {
                    if(map[ny][nx] == map[y][x]) {
                        if(!merged[ny][nx]) {
                            map[ny][nx] *= 2;
                            merged[ny][nx] = true;
                            map[y][x] = 0;
                            if(map[ny][nx] > max) {max = map[ny][nx]; }
                            break;
                        }
                    }else if(map[ny][nx] == 0) {
                        map[ny][nx] = map[y][x];
                        map[y][x] = 0;
                    } else {
                        break;
                    }
                    y = ny;
                    x = nx;
                    ny = y + dyx[0][i];
                    nx = x + dyx[1][i];
                    //printArray(map,size);
                }
            }
        }
        std::cout<<"direction: "<<i<<std::endl;
        move(map, size, n+1);
    }
}

int main() {
    int n;
    int map[MAX][MAX];
    scanf("%d",&n);

    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        scanf("%d", &map[i][j]);
        if(map[i][j] > max) {max = map[i][j];}

    }

    move(map,n,0);

    std::cout<<max;

}