#include"Libraries.h"
#include"reward.h"
#include"player.h"
#include"Enemy.h"
using namespace std;
using namespace sf;
class Game {
	Maze m;
	Text text[4];
	Font font;
	int score;
	Player *p;
	Enemy* en;
	int e;
public:
	Game(): m{ 15,34 , 40, 12, 12 }{
		score = 0;
		p = new Player;
		en = new Enemy[4];
		e = 275;
	}
	bool up() {
		int n = this->m.l;
		for (int i = 0; i < n; i++) {
			int x = (p->sp.getPosition().y - 5) - this->m.py[i]+5;
			if ((p->sp.getPosition().x < (this->m.px[i]) + 40) && p->sp.getPosition().x >= this->m.px[i]) {
				if ( x >0&&x<10 ) {
					return false;
				}
			}
		}
		return true;
	}
	bool down() {
		int n = this->m.l1;
		for (int i = 0; i < n; i++) {
			int x = this->m.py1[i] - p->sp.getPosition().y-26;
			if ((p->sp.getPosition().x < (this->m.px1[i]) + 40) && p->sp.getPosition().x >= this->m.px1[i]) {
				if (x > 0 && x < 10) {
					return false;
				}
			}
		}
		return true;
	}
	void check(RenderWindow& w ,Circle cr[], Hexagon hx[], Triangle tri[], Rectangle rec[],int &s,Enemy *& l,Sword o[]) {
		for (int i = 0; i < 4; i++) {
			if (p->sp.getGlobalBounds().intersects(o[i].s.getGlobalBounds())) {
				o[i].setp(e, 130);
				e += 25;
				p->addtostore(o[i].val);
				p->store->inorder(p->store->root);
			}
		}
		for (int i = 0; i < 4; i++) {
			if (p->sp.getGlobalBounds().intersects(l[i].sp.getGlobalBounds())) {
				if (p->store->searchItem(100)) {
					p->store->deleteItem(100, p->store->root);
					l[i].dis = 0;
					l[i].setp(0, 0);
					for (int i = 0; i < 4; i++) {
						if (o[i].s.getPosition().y == 130) {
							o[i].collide = 1;
							o[i].setp(0, 0);
						}
					}
					return;
				}
				s -= 20;
				l[i].dis = 0;
				l[i].setp(0, 0);
			}
		}
		
		for (int i = 0; i < 6; i++) {
			if (p->sp.getGlobalBounds().intersects(cr[i].s.getGlobalBounds())) {
				cr[i].collide = 1;
				cr[i].setp(e, 130);
				e += 25;
				cr[i].addScore(s);
				p->addtostore(cr[i].val);
				p->store->inorder(p->store->root);
			}
		}
		for (int i = 0; i < 6; i++) {
			if (p->sp.getGlobalBounds().intersects(hx[i].s.getGlobalBounds())) {
				hx[i].collide = 1;
				hx[i].addScore(s);
				hx[i].setp(e, 130);
				e += 25;
				p->addtostore(cr[i].val);
				p->store->inorder(p->store->root);
			}
		}
		for (int i = 0; i < 6; i++) {
			if (p->sp.getGlobalBounds().intersects(tri[i].s.getGlobalBounds())) {
				tri[i].collide = 1;
				tri[i].addScore(s);
				tri[i].setp(e, 130);
				e += 25;
				p->addtostore(cr[i].val);
				p->store->inorder(p->store->root);
			}
		}

		for (int i = 0; i < 6; i++) {
			if (p->sp.getGlobalBounds().intersects(rec[i].s.getGlobalBounds())) {
				rec[i].collide = 1;
				rec[i].addScore(s);
				rec[i].setp(e, 130);
				e += 25;
				p->addtostore(cr[i].val);
				p->store->inorder(p->store->root);
			}
		}
		if (s <=0 ) {
			w.close();
			Sprite background; // Game background sprite
			Texture bg_texture;
			bg_texture.loadFromFile("images\\game.jpg");
			background.setTexture(bg_texture);
			RenderWindow window(VideoMode(1400, 800), "Menu");
			background.setScale(
				static_cast<float>(window.getSize().x) / bg_texture.getSize().x,
				static_cast<float>(window.getSize().y) / bg_texture.getSize().y
			);
			while (window.isOpen()) {
				Event e;
				while (window.pollEvent(e)) {
					if (e.type == Event::Closed)
						window.close();
				}
				window.clear(Color::White);
				window.draw(background);
				window.display();
			}
		}
	}
	void right() {
		int n = this->m.getnoofrec();
		for (int i = 0; i < n; i++) {
			if (p->sp.getGlobalBounds().intersects(this->m.getrec(i).getGlobalBounds())) {
				p->sp.move(-8.0, 0.0);
			}
		}
	}
   void left() {
		int n = this->m.getnoofrec();
		for (int i = 0; i < n; i++) {
			if (p->sp.getGlobalBounds().intersects(this->m.getrec(i).getGlobalBounds())) {
				p->sp.move(8.0, 0.0);
			}
		}
	}
	void showscreen(RenderWindow& w,int & s) {
		if (!font.loadFromFile("f1.ttf")) {
			cout << "Error Loading File" << endl;
		}
		else {
			text[0].setFont(font);
			text[0].setFillColor(Color::Black);
			text[0].setString("Score: ");
			text[0].setCharacterSize(35);
			text[0].setPosition(1100, 110);

			text[1].setFont(font);
			text[1].setFillColor(Color::Black);
			text[1].setString("Enchanted Labyrinth Explorer");
			text[1].setCharacterSize(40);
			text[1].setPosition(240, 4);

			text[2].setFont(font);
			text[2].setFillColor(Color::Black);
			text[2].setString("Inventory: ");
			text[2].setCharacterSize(35);
			text[2].setPosition(30, 110);

			text[3].setFont(font);
			text[3].setFillColor(Color::Black);
			text[3].setString(to_string(s));
			text[3].setCharacterSize(35);
			text[3].setPosition(1300, 110);

		}
		for (int i = 0; i < 4; i++) {
			w.draw(text[i]);
		}
	}
	void displayf(Circle cr[], Hexagon hx[],Triangle tri[],Rectangle rec[],Enemy * &en,Sword s[]) {
		int x = 0;
		int y = 0;
		bool b = 0;
		srand(time(0));
		for (int i = 0; i < 4; i++) {
			b = 0;
			while (b == 0) {
				int r = rand() % 12;
				int c = rand() % 33;
				x = this->m.getex(r, c) + 8;
				y = this->m.getey(r, c) + 8;
				if (this->m.getv(r, c)) {
					b = 1;
				}
			}
			s[i].setp(x, y);
		}
		for (int i = 0; i < 4; i++) {
			b = 0;
			while (b == 0) {
				int r = rand() % 12;
				int c = rand() % 33;
				x = this->m.getex(r, c) + 8;
				y = this->m.getey(r, c) + 8;
				if (this->m.getv(r, c)) {
					b = 1;
				}
			}
			en[i].setp(x, y);
		}
		for (int i = 0; i < 6; i++) {
			b = 0;
			while (b == 0) {
				int r = rand() % 12;
				int c = rand() % 33;
				x = this->m.getex(r, c) + 8;
				y = this->m.getey(r, c) + 8;
				if (this->m.getv(r, c)) {
					b = 1;
				}
			}
			cr[i].setp(x, y);
		}
		for (int i = 0; i < 6; i++) {
			b = 0;
			while (b == 0) {
				int r = rand() % 12;
				int c = rand() % 33;
				x = this->m.getex(r, c) + 8;
				y = this->m.getey(r, c) + 8;
				if (this->m.getv(r, c)) {
					b = 1;
				}
			}
			hx[i].setp(x, y);
		}
		for (int i = 0; i < 6; i++) {
			b = 0;
			while (b == 0) {
				int r = rand() % 12;
				int c = rand() % 33;
				x = this->m.getex(r, c) + 8;
				y = this->m.getey(r, c) + 8;
				if (this->m.getv(r, c)) {
					b = 1;
				}
			}
			tri[i].setp(x, y);
		}
		for (int i = 0; i < 6; i++) {
			b = 0;
			while (b == 0) {
				int r = rand() % 12;
				int c = rand() % 33;
				x = this->m.getex(r, c) + 8;
				y = this->m.getey(r, c) + 8;
				if (this->m.getv(r, c)) {
					b = 1;
				}
			}
			rec[i].setp(x, y);
		}

	}
	void d(RenderWindow& w, Circle cr[], Hexagon hx[], Triangle tri[], Rectangle rec[],Enemy* &en,Sword s[]) {
		for (int i = 0; i < 4; i++) {
			if(en[i].dis)
			w.draw(en[i].sp);
		}
		for (int i = 0; i < 4; i++) {
			if(!s[i].collide)
			w.draw(s[i].s);
		}
		for (int i = 0; i < 6; i++) {
			w.draw(cr[i].s);
		}
		for (int i = 0; i < 6; i++) {
			w.draw(hx[i].s);
		}
		for (int i = 0; i < 6; i++) {
			w.draw(tri[i].s);
		}
		for (int i = 0; i < 6; i++) {
			//if (!rec[i].collide)
			w.draw(rec[i].s);
		}
	}
	void play() {
		Circle cr[6] ;
		Hexagon hx[6]  ;
		Rectangle rec[6] ;
		Triangle tri[6] ;
		Sword sw[4];
		int score = 10;
		int i = 0;
		Music m;
		bool iskey = 0;
		RenderWindow w(VideoMode(1400, 800), "Game");
		if (!m.openFromFile("music.ogg")) {
			cout << "Error loading file" << endl;
		}
		m.play();
		while (w.isOpen()) {
			Event e;
			while (w.pollEvent(e)){
				if (e.type == Event::Closed)
					w.close();
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Up) {
						if (up()) {
							p->sp.move(0.0f, -7.0f);
						}
					}
				}
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Down) {
						if(down())
						p->sp.move(0.0f,7.0f);
					}
				}
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Right) {
						p->sp.move(8.0f, 0.0f);
						right();
					}
				}
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Left) {
						p->sp.move(-8.0f, 0.0f);
						left();
					}
				}
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::S) {
						iskey = 1;
					}
				}
			}
			if (!this->m.is_generated) {
				this->m.generatemaze();
			}
			else {
				if (i == 0) {
					displayf(cr, hx, tri, rec,en,sw);
					this->m.findshortestpath(this->m.getd(), 0, 0, 10,10 );
					i++;
				}
				w.clear(Color::White);
				if (iskey) {
					iskey = 0;
				}
				this->m.draw(w);
				showscreen(w,score);
				w.draw(p->sp);
				check(w,cr, hx, tri, rec,score,en,sw);
				d(w,cr, hx, tri, rec,en,sw);
				w.display();
			}
			
		}
	}
};
