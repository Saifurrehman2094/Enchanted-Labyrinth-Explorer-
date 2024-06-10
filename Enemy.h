#ifndef Enemy_h
#define Enemy_h
#include"Libraries.h"
class Enemy {
public:
	Sprite sp;
	Texture tx;
	Vector2u txs;
	bool dis = 1;
	Enemy() {
		txs = tx.getSize();
		tx.loadFromFile("images\\en.jpg");
		sp.setTexture(tx);
		sp.setScale(1, 0.95);
		sp.setOrigin((float)txs.x / 2, (float)txs.y / 2);
	}
	void setp(int a, int b) {
		sp.setPosition(a, b);
	}
};
#endif // !Enemy_h

