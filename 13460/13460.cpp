#include <iostream>
#include <string>
#include <tuple>
#include <queue>
#include <list>

#define MAX 10

char mapdata[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];

typedef struct coords {
	int RCoord[2] = {0,0};
	int BCoord[2] = {0,0};
	int count = 0;
	bool operator==(coords b) {
		if (RCoord[0] == b.RCoord[0] && RCoord[1] == b.RCoord[1] && BCoord[0] == b.BCoord[0] && BCoord[1] == b.BCoord[1]) {
			return true;
		}
		else {
			return false;
		}
	}
}Coords;

int main() {
	//get input
	std::string a, b;
	int rows, cols;
	std::getline(std::cin, a, ' ');
	rows = atoi(a.c_str());
	std::getline(std::cin, b);
	cols = atoi(b.c_str());

	Coords start;

	std::string line;
	for (int i = 0; i < rows; i++) {
		std::getline(std::cin, line);
		for (int j = 0; j < cols; j++) {
			if (line[j] == 'R') {
				start.RCoord[0] = i;
				start.RCoord[1] = j;
				mapdata[i][j] = '.';
			}
			else if (line[j] == 'B') {
				start.BCoord[0] = i;
				start.BCoord[1] = j;
				mapdata[i][j] = '.';
			}
			else {
				mapdata[i][j] = line[j];
			}
		}
	}
	
	for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) for (int k = 0; k < MAX; k++) for (int l = 0; l < MAX; l++) visited[i][j][k][l] = false;
	
	//bfs
	int dy[4] = {-1, 1, 0, 0};
	int dx[4] = {0, 0, -1, 1};

	std::queue<Coords> c_queue;
	c_queue.push(start);
	Coords current;

	int count = 0;
	bool hit = false;

	while (1) {
		Coords temp;

		if (c_queue.empty()) { break; }
		current = c_queue.front();
		c_queue.pop();
		if (current.count >= 10) { break; }
		visited[current.RCoord[0]][current.RCoord[1]][current.BCoord[0]][current.BCoord[1]] = true;

		for (int i = 0; i < 4; i++) {
			bool Rstop = false;
			bool Bstop = false;
			bool Rhit = false;
			bool Bhit = false;
			temp = current;

			while(1) {
				temp.RCoord[0] += dy[i];
				temp.RCoord[1] += dx[i];
				temp.BCoord[0] += dy[i];
				temp.BCoord[1] += dx[i];

				if(mapdata[temp.BCoord[0]][temp.BCoord[1]] == '#') {
					temp.BCoord[0] -= dy[i];
					temp.BCoord[1] -= dx[i];
					Bstop = true;
				}else if(mapdata[temp.BCoord[0]][temp.BCoord[1]] == 'O') {
					//when blue ball hits
					Bhit = true;
				}

				if(mapdata[temp.RCoord[0]][temp.RCoord[1]] == '#') {
					temp.RCoord[0] -= dy[i];
					temp.RCoord[1] -= dx[i];
					Rstop = true;
				}else if(mapdata[temp.RCoord[0]][temp.RCoord[1]] == 'O') {
					//when red ball hits
					Rhit = true;
				}

				if(temp.RCoord[0] == temp.BCoord[0] && temp.RCoord[1] == temp.BCoord[1]) {
					//overlap condition
					if(Rstop) {
						temp.BCoord[0] -= dy[i];
						temp.BCoord[1] -= dx[i];
						Bstop = true;
					} else {
						temp.RCoord[0] -= dy[i];
						temp.RCoord[1] -= dx[i];
						Rstop = true;
					}
				}

				if(Rstop && Bstop) {
					if(!visited[temp.RCoord[0]][temp.RCoord[1]][temp.BCoord[0]][temp.BCoord[1]]) {
						temp.count++;
						if(Bhit) {
							break;
						} else if(Rhit) {
							hit = true;
							count = temp.count;
							break;
						}
						c_queue.push(temp);
					}
					break;
				}            
			}				
		}
		if(hit) { break; }
	}

	if(!hit) {count = -1;}
	std::cout<<count;
}
