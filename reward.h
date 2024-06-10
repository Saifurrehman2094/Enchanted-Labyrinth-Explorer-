#ifndef Reward_h
#define Reward_h
#include"Libraries.h"
using namespace sf;
#include <SFML/Graphics.hpp>
using namespace sf;

class reward {
public:
	Texture te;
	Sprite s;
	float x_axis, y_axis;
	int val;
	bool collide;
public:
	reward() :x_axis(0), y_axis(0), val(0), collide(0) {}

	virtual int addScore(int& score)=0;


};
class Rectangle : public reward {

public:
	Rectangle() :reward() {
		te.loadFromFile("images\\sprite.jpg");
		s.setTexture(te);
		s.setScale(1, 0.8);
		val = 10 + rand() % 20;
	}
	void setp(int x, int y) {
		this->s.setPosition(x, y);
	}

	int addScore(int& score)override {
		score = score + 10;
		return score;
	}


};
class Circle : public reward {

public:
	Circle() :reward() {
		te.loadFromFile( "images\\sprite4.jpg" );
		s.setTexture(te);
		s.setScale(1, 0.8);
		val = 10 + rand() % 20;
	}
	void setp(int x, int y) {
		this->s.setPosition(x, y);
	}
	int addScore(int& score)override {
		score = score + 20;
		return score;
	}


};
class Triangle :public reward {

public:
	Triangle() :reward() {
		te.loadFromFile({ "images\\sprite3.jpg" });
		s.setTexture(te);
		s.setScale(1, 0.8);
		val = 10 + rand() % 20;
	}
	void setp(int x, int y) {
		this->s.setPosition(x, y);
	}

	int addScore(int& score)override {
		score = score + 30;
		return score;
	}


};
class Hexagon :public reward {

public:
	Hexagon() :reward() {
		te.loadFromFile( "images\\sprite2.jpg" );
		s.setTexture(te);
		s.setScale(1, 0.8);
		val = 10 + rand() % 20;
	}
	void setp(int x, int y) {
		this->s.setPosition(x, y);
	}
	int addScore(int& score)override {
		score = score + 40;
		return score;
	}


};
class Sword :public reward {
public:
	Sword() :reward() {
		te.loadFromFile("images\\sword.jpg");
		s.setTexture(te);
		s.setScale(1, 0.8);
		val = 100;
	}
	void setp(int x, int y) {
		this->s.setPosition(x, y);
	}
	int addScore(int &a) {
		return 0;
	}
};
#endif // !Reward_h
