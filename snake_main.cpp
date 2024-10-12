#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <ctime>
using namespace std;

//坐标结构体
struct Point {
	int x;
	int y;
	void setPoint(int px, int py) {
		this->x = px;
		this->y = py;
	}
};

//游戏框架类
class CGameFrame {
public:
	CGameFrame() {

	}
	virtual ~CGameFrame() {

	}

	virtual void OnInit() = 0;//初始化

	virtual void OnRun() = 0;//游戏运行

	virtual void OnDraw() = 0;//绘制

	virtual void OnClose() = 0;//游戏关闭

};

//双向链表节点
struct Node {
	struct Node* pNext;
	struct Node* pPre;
	Point pos;
	Node() {
		pNext = nullptr;
		pPre = nullptr;
	}
};

//双向链表
struct List {
	struct Node* pHead;
	struct Node* pTail;
	int length;
	List() {
		pHead = nullptr;
		pTail = nullptr;
		length = 0;
	}
};

//创建双向链表
void CreateList(List** L) {
	*L = new List;
	(*L)->length = 0;
}

//双向链表尾添加节点
void AddNode(List* L, Point p) {
	if (L->pHead == nullptr) {
		L->pHead = new Node;
		L->pHead->pos = p;
		L->pHead->pNext = L->pHead;
		L->pTail = L->pHead;
		L->length++;
	}
	else {
		Node* temp = new Node;
		temp->pos = p;
		L->pTail->pNext = temp;
		temp->pPre = L->pTail;
		L->pTail = temp;
		L->length++;
	}
}

//链表资源释放
void DeleteList(List* L) {
	Node* pNode = L->pHead;
	while (pNode != nullptr) {
		Node* temp = pNode;
		pNode = pNode->pNext;
		delete temp;
		temp = nullptr;
	}
	delete L;
	L = nullptr;
}

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3


//贪吃蛇类
class GreedySnake :public CGameFrame
{
private:
	bool m_isQuit;//游戏退出标识
	List* snake;//存储蛇
	int direct;//记录当前方向
	IMAGE map;
	IMAGE head_up;
	IMAGE head_down;
	IMAGE head_left;
	IMAGE head_right;
	IMAGE apple;
	IMAGE body;
	//屏幕大小
	int screenWidth;
	int screenHeight;
	//苹果坐标
	int appleX;
	int appleY;
	//格子大小
	int base;

	//蛇头坐标
	Point m_point;

public:
	GreedySnake() {
		m_isQuit = true;
		screenWidth = 600;
		screenHeight = 600;
		srand((unsigned)time(NULL));
		OnInit();
	}
	~GreedySnake() {

	}
	void OnInit() {

		direct = UP;
		base = 30;
		//初始化苹果
		appleX = rand() % 18 + 1;
		appleY = rand() % 18 + 1;

		//初始化蛇
		m_point.setPoint(9, 9);
		CreateList(&snake);//蛇初始化
		Point temp;
		temp.setPoint(9, 9);
		AddNode(snake, temp);
		temp.setPoint(9, 10);
		AddNode(snake, temp);
		temp.setPoint(9, 11);
		AddNode(snake, temp);

		//加载图片
		loadimage(&map, L".\\image\\map.bmp");
		loadimage(&head_right, L".\\image\\head0.bmp");//R
		loadimage(&head_up, L".\\image\\head1.bmp");//U
		loadimage(&head_left, L".\\image\\head2.bmp");//L
		loadimage(&head_down, L".\\image\\head3.bmp");//D
		loadimage(&apple, L".\\image\\apple.bmp");
		loadimage(&body, L".\\image\\body.bmp");

		initgraph(screenWidth, screenHeight);

	}

	void OnRun() {
		while (m_isQuit) {
			if (_kbhit())//处理键盘输入-----------
			{
				int k = _getch();

				switch (k)
				{
				case 'A':
				case 'a':
				case 75://左
					direct = LEFT;
					break;
				case 'S':
				case 's':
				case 80://下
					direct = DOWN;
					break;
				case 'D':
				case 'd':
				case 77://右
					direct = RIGHT;
					break;
				case 'W':
				case 'w':
				case 72://上
					direct = UP;
					break;
				}

			}//------------------------------------

			SnakeMove();
			if (!m_isQuit) {
				break;
			}
			OnDraw();

			Sleep(200);
		}
	}

	void OnDraw() {
		::BeginBatchDraw();

		putimage(0, 0, &map);
		putimage(appleX * base, appleY * base, &apple);
		Node* pNode = snake->pHead->pNext;
		//绘制蛇头
		switch (direct)
		{
		case UP:
			putimage(m_point.x * base, m_point.y * base, &head_up);
			break;
		case DOWN:
			putimage(m_point.x * base, m_point.y * base, &head_down);
			break;
		case LEFT:
			putimage(m_point.x * base, m_point.y * base, &head_left);
			break;
		case RIGHT:
			putimage(m_point.x * base, m_point.y * base, &head_right);
			break;
		}
		//绘制蛇身
		while (pNode != NULL) {
			putimage(pNode->pos.x * base, pNode->pos.y * base, &body);
			pNode = pNode->pNext;
		}

		::EndBatchDraw();
	}

	void OnClose() {

		DeleteList(snake);
	}

	void SnakeMove() {
		switch (direct)
		{
		case UP:
			m_point.y--;
			break;
		case DOWN:
			m_point.y++;
			break;
		case LEFT:
			m_point.x--;
			break;
		case RIGHT:
			m_point.x++;
			break;
		}

		if (m_point.x < 1 || m_point.x>18 || m_point.y < 1 || m_point.y>18) {
			m_isQuit = false;
			return;
		}
		if (appleX == m_point.x && appleY == m_point.y) {
			AddNode(snake, snake->pTail->pos);
			appleX = rand() % 18 + 1;
			appleY = rand() % 18 + 1;
		}

		Node* pNode = snake->pTail;
		while (pNode->pPre != NULL) {
			pNode->pos.x = pNode->pPre->pos.x;
			pNode->pos.y = pNode->pPre->pos.y;
			pNode = pNode->pPre;
		}
		snake->pHead->pos = m_point;


		pNode = snake->pHead->pNext;
		while (pNode != NULL) {
			if (pNode->pos.x == m_point.x && pNode->pos.y == m_point.y) {
				m_isQuit = false;
				return;
			}
			pNode = pNode->pNext;
		}
	}

};



int main() {
	GreedySnake* pGame = new GreedySnake;
	pGame->OnRun();
	pGame->OnClose();
	delete pGame;
	pGame = nullptr;
	return 0;
}
