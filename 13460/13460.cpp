#include <iostream>
#include <string>
#include <tuple>
#include <queue>
#include <list>

#define MAX 10

char mapdata[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];

enum Direction {
	UP,
	LEFT,
	RIGHT,
	DOWN,
	LAST
};

typedef struct coords {
	int RCoord[2];
	int BCoord[2];
	int count;
	bool operator==(coords b) {
		if (std::tie(RCoord[0], RCoord[1], BCoord[0], BCoord[1]) == std::tie(b.RCoord[0], b.RCoord[1], b.BCoord[0], b.BCoord[1])) {
			return true;
		}
		else {
			return false;
		}
	}
}Coords;

Coords moveOneTo(Direction d, Coords a) {
	Coords b = a;
	switch (d) {
	case UP:
		b.RCoord[0]--;
		b.BCoord[0]--;
		break;
	case DOWN:
		b.RCoord[0]++;
		b.BCoord[0]++;
		break;
	case LEFT:
		b.RCoord[1]--;
		b.BCoord[1]--;
		break;
	case RIGHT:
		b.RCoord[1]++;
		b.BCoord[1]++;
		break;
	default:
		break;
	}
	return b;
}

int main() {
	//get input
	std::string a, b;
	int rows, cols;
	std::getline(cin, a, ' ');
	rows = atoi(a.c_str());
	std::getline(cin, b);
	cols = atoi(b.c_str());

	Coords start;

	std::string line;
	for (int i = 0; i < rows; i++) {
		std::getline(cin, line);
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
	std::queue<Coords> c_queue;
	c_queue.push(start);
	Coords current;
	Coords temp = current;
	while (1) {
		if (c_queue.empty()) { break; }
		current = c_queue.front();
		c_queue.pop();
		if (current.count >= 10) { break; }
		visited[current.RCoord[0]][current.RCoord[1]][current.BCoord[0]][current.BCoord[1]] = true;

		for (int i = UP; i < LAST; i++) {
			while (1) {
				temp = moveOneTo(i, temp);
				if () {

				}
				
				
			}
		}
	}
}