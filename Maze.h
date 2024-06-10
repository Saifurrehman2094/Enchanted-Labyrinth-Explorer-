#ifndef Maze_h
#define Maze_h
#include"Libraries.h"
#include<limits>
#include<queue>
#include<stack>
using namespace sf;
using namespace std;
const int inf = numeric_limits<int>::max();
struct Cell{
	bool visited = 0;
	bool top = 1;
	bool bottom = 1;
	bool left = 1;
	bool right = 1;
};
struct c {
	bool visited = 0;
	int x;
	int y;
	c() {
		x = 0;
		y = 0;
		visited = 0;
	}
	c(int a, int b) {
		x = a;
		y = b;
		visited = 0;
	}
};
struct Cellpoint {
	int x;
	int y;
	Cellpoint() {
		x = 0;
		y = 0;
	}
	Cellpoint(int a,int b) {
		x = a;
		y = b;
	}
};
class Maze {
	int count;
	int row;
	int col;
	int cell_size;
	Cellpoint position{ 0,0 };
	Cell** data;
	Cell* current;
	stack<Cellpoint> path;
	int noofRec;
	RectangleShape *rectangle;
	c** e;
public:
	int* px = 0;
	int* py = 0;
	int* px1 = 0;
	int* py1 = 0;
	int l = 0;
	int l1 = 0;
	bool is_generated;
	
	Maze(int row, int col, int cellsize, int start_x, int start_y)
		:position{ start_x, start_y } {
		srand(time(NULL));
		position.x = rand() % 12;
		position.y = rand() % 12;
		this->row = row;
		this->col = col;
		e = new c * [row];
		for (int i = 0; i < row; i++) {
			e[i] = new c[col]();
		}
		data = new Cell * [row];
		for (int i = 0; i < row; i++) {
			data[i] = new Cell[col]();
		}
		this->cell_size = cellsize;
		current = &data[position.y][position.x];
		current->visited = true;
		path.push(position);
		is_generated = false;
		count = 0;
		noofRec = 4*row*col;
		rectangle = 0;
	}
	Cell**& getd() {
		return data;
	}
	void findshortestpath(Cell**& data, int startx, int starty, int endx, int endy) {
		int dx[] = { -1,1,0,0 };
		int dy[] = { 0,0,-1,1 };

		int** dt = new int* [row];
		for (int i = 0; i < row; i++) {
			dt[i] = new int[col];
			for (int j = 0; j < col; j++) {
				dt[i][j] = inf;
			}
		}
		priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> p;

		dt[0][0] = 0;
		p.push({ 0,0,0 });

		while (!p.empty()) {
			int d, x, y;
			tie(d, x, y) = p.top();
			p.pop();

			if (x == endx && y == endy) {
				break;
			}

			for (int i = 0; i < 4; i++) {
				int newX = x + dx[i];
				int newY = y + dy[i];
				if (newX >= 0 && newX < col && newY >= 0 && newY < row) {
					if (y == newY) {
						if (x < newX && data[y][x].right == 0) {
							if (dt[newY][newX] > dt[y][x] + 1) {
								dt[newY][newX] = dt[y][x] + 1;
								p.push({ dt[newY][newX], newX, newY });
							}
						}
						else if (x > newX && data[y][x].left == 0) {
							if (dt[newY][newX] > dt[y][x] + 1) {
								dt[newY][newX] = dt[y][x] + 1;
								p.push({ dt[newY][newX], newX, newY });
							}
						}
					}
					else if (x == newX) {
						 if (y < newY && data[y][x].bottom == 0) {
							if (dt[newY][newX] > dt[y][x] + 1) {
								dt[newY][newX] = dt[y][x] + 1;
								p.push({ dt[newY][newX], newX, newY });
							}
						}
						else if (y > newY && data[y][x].top == 0) {
							if (dt[newY][newX] > dt[y][x] + 1) {
								dt[newY][newX] = dt[y][x] + 1;
								p.push({ dt[newY][newX], newX, newY });
							}
						}
					}
				}
			}
		}
		stack<pair<int, int>> path;
		int x = endx, y = endy;
		while (x != startx || y != starty) {
			path.push({ x,y });
			for (int i = 0; i < 4; i++) {
				int newX = x + dx[i];
				int newY = y + dy[i];
				if (newX >= 0 && newX < row && newY >= 0 && newY < col && dt[newX][newY] + 1 == dt[x][y]) {
					x = newX;
					y = newY;
					break;
				}
			}
		}
		path.push({ startx, starty });
		while (!path.empty()) {
			int x, y;
			tie(x, y) = path.top();
			cout << "(" << x << ", " << y << ") ";
			path.pop();
		}
		cout << endl;

		// Free memory allocated for dist
		for (int i = 0; i < row; ++i) {
			delete[] dt[i];
		}
		delete[] dt;

	}
	int getex(int r, int c) {
		e[r][c].visited = 1;
		return e[r][c].x;
	}
	bool getv(int r, int c) {
		return e[r][c].visited;
	}
	int getey(int r, int c) {
		e[r][c].visited = 1;
		return e[r][c].y;
	}
	inline int getnoofrec() {
		return noofRec;
	}
	inline RectangleShape& getrec(int ind) {
		return rectangle[ind];
	}
	void generatemaze() {
		if (is_generated) {
			return;
		}
		Cellpoint pos = nextcell();
		if (pos.x>-1&&pos.y>-1) {
			count++;
			if (count == row * col-1) {
				is_generated = 1;
			}
			Cell* next = &data[pos.y][pos.x];
			next->visited = true;
			if (position.x > pos.x) {
				current->left = false;
				next->right = false;
				noofRec--;
			}
			if (position.x < pos.x) {
				current->right = false;
				next->left = false;
				noofRec--;
			}
			if (position.y > pos.y) {
				current->top = false;
				next->bottom = false;
				noofRec--;
			}
			if (position.y < pos.y) {
				current->bottom = false;
				next->top = false;
				noofRec--;
			}
			position = pos;
			current = next;
			path.push(position);
		}
		else {
			if (!path.empty()) {
				pos = path.top();
				position = pos;
				current = &data[position.y][position.x];
				path.pop();
			}
		}
		if (is_generated) {
			array();
		}
	}
	void array() {
		for (int y = 0; y < row; y++) {
			for (int x = 0; x < col; x++) {
				int gx = (x + 0.3) * cell_size;
				int gy = (y + 4) * cell_size;
				e[y][x].x = gx;
				e[y][x].y = gy;
				Cell* cell = &data[y][x];
				if (cell->top) {
					l++;
				}
				if (cell->bottom) {
					l1++;
				}
			}
		}
		int ind = 0;
		int ind1 = 0;
		px = new int[l] {0};
		py = new int[l] {0};
		px1 = new int[l1] {0};
		py1 = new int[l1] {0};
		for (int y = 0; y < row; y++) {
			for (int x = 0; x < col; x++) {
				int gx = (x + 0.3) * cell_size;
				int gy = (y + 4) * cell_size;
				Cell* cell = &data[y][x];
				if (cell->top) {
					px[ind] = gx;
					py[ind] = gy;
					ind++;
				}
				if (cell->bottom) {
					px1[ind1] = gx;
					py1[ind1] = gy + cell_size - 2;
					ind1++;
				}
			}
		}
	}
	Cellpoint nextcell() {
		Cellpoint next;
		stack <Cellpoint> a;
		Cellpoint* arr{};
		if (position.x - 1 >= 0) {
			if (!data[position.y][position.x - 1].visited) {
				next.x = position.x-1;
				next.y = position.y;
				a.push(next);
			}
		}
		if (position.y - 1 >=0) {
			if (!data[position.y - 1][position.x].visited) {
				next.x = position.x;
				next.y = position.y-1;
				a.push(next);
			}
		}
		if (position.x + 1 < col) {
			if (!data[position.y][position.x + 1].visited) {
				next.x = position.x + 1;
				next.y = position.y;
				a.push(next);
			}
		}
		if (position.y +1< row) {
			if (!data[position.y + 1][position.x].visited) {
				next.x = position.x;
				next.y = position.y + 1;
				a.push(next);
			}
		}
		int index = 0;

		if (a.size() != 0) {
			//srand(time(NULL));
			int n = a.size();
			index = rand() % n;
			arr = new Cellpoint[n];
			for (int i = 0; i < n; i++) {
				arr[i] = a.top();
				a.pop();
			}
			return arr[index];
		}
		next.x = -2;
		next.y = -2;
		return next;
	}
	void draw(RenderWindow& w) {
	    rectangle = new RectangleShape[noofRec];
		int ind = 0;
		for (int y = 0; y < row; y++) {
			for (int x = 0; x < col; x++) {
				//sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
				//rectangle[ind].setOrigin(rectangle[ind].getLocalBounds().width / 2, rectangle[ind].getLocalBounds().height / 2);
				int gx = (x+0.3) * cell_size;
				int gy = (y+4) * cell_size;
				Cell* cell = &data[y][x];
				
				if (cell->top) {
					rectangle[ind].setFillColor(Color::Black);
					rectangle[ind].setSize(Vector2f(cell_size, 4));
					rectangle[ind].setPosition(gx, gy);
					/*if (x == 0 && y == 0) {
						cout << rectangle[ind].getPosition().x << "  " << rectangle[ind].getPosition().y << endl;
					}*/
					w.draw(rectangle[ind]);
				}
				if (cell->bottom) {
					rectangle[ind].setFillColor(Color::Black);
					rectangle[ind].setSize(Vector2f(cell_size, 4));
					rectangle[ind].setPosition(gx, gy + cell_size - 1);
					w.draw(rectangle[ind]);
				}
				if (cell->left) {
					rectangle[ind].setFillColor(Color::Black);
					rectangle[ind].setSize(Vector2f(4, cell_size));
					rectangle[ind].setPosition(gx, gy);
					w.draw(rectangle[ind]);
				}
				if (cell->right) {
					rectangle[ind].setFillColor(Color::Black);
					rectangle[ind].setSize(Vector2f(4, cell_size));
					rectangle[ind].setPosition(gx + cell_size - 1, gy);
					w.draw(rectangle[ind]);
				}
				ind++;
			}
		}
	}
};


#endif // !Maze_h

