#include <queue>
#include <vector>
#include <iostream>
using namespace std;

//4 directions
int directions[4][2] = { { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 0 } };

//Mark of a node
enum Mark
{
	BLOCKED,
	OPEN,
	UNVISITED
};

//G is the Current cost of the node
//H is the Estimated cost of the node: actual node(x,y), destination node(x0,y0), Manhattan distance H=|x-x0|+|y-y0|
//F is the knowledge-plus-heuristic cost of the node: F=G+H
typedef struct node
{
	int _x, _y;//Node coordinate(x,y)
	int _G;//Current cost G
	int _H;//Estimated cost H
	int _F;//Priority _F=_G+_H
	struct node *pre; //Previous node
}Node;

//struct _marks[][], stores nodes' marks(BLOCKED or OPEN), and the pointer of the node if it is OPEN
typedef struct
{
	Mark mark;
	Node *point;
}Marks;

//=============A* algorithm class=============
//Members of the class:
//1.core of A* algorithm									void A()
//2.function that calculates the Manhattan distance H		int H(int x, int y)
//3.fuction that allows to input the maze					void input()
//4.length & width of the maze								int _len, _wid
//5.blocked queue											Marks **_marks
//6.open queue												priority_queue<Queue_Node *,vector<Queue_Node *>,cmp> _open
//7.the "map" of the maze									unsigned char **_maze
//8.initial node & destination node							int _ix, _iy, _dx, _dy
//9.function that calculates the absolute value				int ab(int i)
//10.function that determines if a node is at border		bool notBorder(int x, int y)
//11.function that prints the path							void print(Node *p)
class A_Star
{
private:
	//compare by F
	struct cmp
	{
		bool operator()(Node *n1, Node *n2)
		{
			return n1->_F > n2->_F;
		}
	};
	priority_queue<Node *, vector<Node *>, cmp> _open;//priority queue of node compared with operator cmp
	int _len, _wid;//length & width of the maze
	int _ix, _iy, _dx, _dy;//initial node, destination node
	Marks **_marks;//stores nodes' marks(BLOCKED or OPEN), and the pointer of the node if it is OPEN
	unsigned char **_maze;//map of the maze

public:
	//Constructor, print informations
	A_Star()
	{
		cout << "Here is a program that solves a maze using A* algorithm" << endl;
		cout << "The program firstly allows you to input the maze detail, then calculates the solution" << endl;
		input();
	}
	//Destructor
	~A_Star()
	{

	}
	//Input the maze
	void input()
	{
		cout << "Input: length & width. Example: 5 5" << endl;
		cin >> _len >> _wid;
		_marks = new Marks*[_len + 1];
		_maze = new unsigned char*[_len + 1];
		for (int i = 0; i <= _len; ++i)
		{
			_marks[i] = new Marks[_wid + 1];
			_maze[i] = new unsigned char[_wid + 1];
		}
		cout << "input the maze" << endl;
		for (int i = 1; i <= _len; ++i)
		{
			for (int j = 1; j <= _wid; ++j)
			{
				cin >> _maze[i][j];
				_marks[i][j].mark = UNVISITED;
				_marks[i][j].point = NULL;
			}
		}
		cout << "Input the coordinate of initial node & destination node. Example: 1 1 5 5" << endl;
		cin >> _ix >> _iy >> _dx >> _dy;
		if (_maze[_ix][_iy] == '1' || _maze[_dx][_dy] == '1' || notBorder(_ix, _iy) == false || notBorder(_dx, _dy) == false)
		{
			cout << "Input Error" << endl;
			return;
		}
		cout << "Calculating solution with A star algorithm:" << endl;
		A();
	}
	//Core of A* algorithm
	void A()
	{
		//push initial node into the open queue
		Node *p_node = new Node;
		p_node->pre = NULL;
		p_node->_H = H(_ix, _iy);
		p_node->_G = 0;
		p_node->_x = _ix;
		p_node->_y = _iy;
		p_node->_F = p_node->_H + p_node->_G;
		_open.push(p_node);
		_marks[_ix][_iy].mark = OPEN;
		_marks[_ix][_iy].point = p_node;
		//A* search
		while (!_open.empty())
		{
			p_node = _open.top();
			_open.pop();
			int x = p_node->_x;
			int y = p_node->_y;
			_marks[x][y].mark = BLOCKED;

			for (int i = 0; i<4; ++i)
			{
				int tx = x + directions[i][0];
				int ty = y + directions[i][1];
				if (notBorder(tx, ty) == false || _maze[tx][ty] == '1' || _marks[tx][ty].mark == BLOCKED)//ignore the node that is border, wall, or blocked
				{
					continue;
				}
				if (_marks[tx][ty].mark == UNVISITED)
				{
					if (tx == _dx && ty == _dy)
					{
						print(p_node);
						cout << "(" << tx << "," << ty << ")" << endl;
						cout << "Steps count: " << p_node->_F << endl;
						return;
					}
					Node *temp = new Node;
					_marks[tx][ty].mark = OPEN;
					_marks[tx][ty].point = temp;
					temp->pre = p_node;
					temp->_G = p_node->_G + 1;
					temp->_x = tx;
					temp->_y = ty;
					temp->_H = H(tx, ty);
					temp->_F = temp->_G + temp->_H;
					_open.push(temp);
				}
				else
				{
					Node *temp = _marks[tx][ty].point;
					if (p_node->_G + 1<temp->_G)
					{
						temp->_G = p_node->_G + 1;
						temp->pre = p_node;
						temp->_F = temp->_G + temp->_H;
					}
				}
			}
		}
		cout << "No path from(" << _ix << "," << _iy << ") to " << "(" << _dx << "," << _dy << ")." << endl;
	}
	//Print the path
	void print(Node *p)
	{
		if (p == NULL)
		{
			return;
		}
		print(p->pre);
		cout << "(" << p->_x << "," << p->_y << "),";
	}
	//Border or not
	bool notBorder(int x, int y)
	{
		return (x <= _len) && (x >= 1) && (y <= _wid) && (y >= 1);
	}
	//Manhattan distance
	int H(int x, int y)
	{
		return ab(x - _dx) + ab(y - _dy);
	}
	//absolute value
	int ab(int i)
	{
		return i<0 ? -i : i;
	}

};


int main()
{
	A_Star a_star;
	getchar();
	getchar();
	return 0;
}