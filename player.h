#ifndef player_h
#define player_h
#include"Avl.h"
using namespace sf;
class Player {
public:
	Sprite sp;
	Texture tx;
	Vector2u txs;
	BalancedTree<int> *store;
	Player() {
		txs = tx.getSize();
		tx.loadFromFile("images\\spt.jpg");
		sp.setTexture(tx);
		sp.setScale(1, 0.95);
		sp.setPosition(24, 170);
		sp.setOrigin((float)txs.x / 2, (float)txs.y / 2);
		store = new BalancedTree<int>;
	}
	void addtostore(int val) {
		store->root = store->insertItem(val, store->root);
	}
};
#endif // !player_h