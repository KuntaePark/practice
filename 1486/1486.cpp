#include <iostream>
#include <cstring>
#include <tuple>
#include <cmath>

#define MAX 25
#define VMAX 625
#define INF 1000001
//1486

int n, m, t, d;
int M[MAX][MAX];
int distM[VMAX][VMAX];

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int coordToN(int row, int col) {return row * m + col;}
std::tuple<int,int> NToCoord(int N) {return std::make_tuple(N/m, N%m);}

void initDistMap() {
    int ny, nx;
    int dest, start;
    int diff;
    int nm = n * m;
    for(int i = 0; i < nm; i++) for(int j = 0; j < nm; j++) distM[i][j] = INF;
    for(int i = 0; i < nm; i++) distM[i][i] = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        for(int k = 0; k < 4; k++) {
            ny = i + dy[k];
            nx = j + dx[k];
            if(ny < 0 || nx < 0 || ny >= n || nx >= m) {continue;}
            else {
                start = coordToN(i,j);
                dest = coordToN(ny, nx);
                diff = M[ny][nx] - M[i][j];
				if (std::abs(diff) <= t) {
					if (diff <= 0) distM[start][dest] = 1;
					else distM[start][dest] = diff * diff;
				}
            }
        }
    }
}

void calDist() {
    int nm = n * m;
    for(int k = 0; k < nm; k++) for(int i = 0; i < nm; i++) for(int j = 0; j < nm; j++) {
		if(distM[i][j] > distM[i][k] + distM[k][j]) distM[i][j] = distM[i][k] + distM[k][j];
    }
}

int getHighest() {
    int nm = n * m;
    int highest = 0;
    int temp, y, x;
    for(int i = 0; i < nm; i++) {
        temp = distM[0][i] + distM[i][0];
        if(temp > d) continue;
        else {
            std::tie(y,x) = NToCoord(i);
            if(M[y][x] > highest) highest = M[y][x];
        }
    }
    return highest;
}

int main() {
    char c;
    std::cin>>n>>m>>t>>d;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        std::cin>>c;
        if(c >= 97) {
            c -= 6;
        }
        M[i][j] = (int)(c-65);
    }
    initDistMap();
    calDist();
    std::cout<<getHighest();
}