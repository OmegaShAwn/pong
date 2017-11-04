#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<sstream>
using namespace sf;

int ww, wh, m1, m2;
Text s1, s2;
float rad, len, x, y, sx, sy; 
ContextSettings settings;
RenderWindow window;
CircleShape ball;

class paddle{
	public:
	CircleShape l;
	CircleShape r;
	RectangleShape b;
	float x, y;
	paddle(){
	}
	paddle(float px, float py){						//initializes the paddles;
		x = px;
		y = py;
		l.setRadius(rad);
		r.setRadius(rad);
		b.setSize(Vector2f(len, rad*2));
		l.setPosition(x,y);
		r.setPosition(x+len, y);
		b.setPosition(x+rad, y);
		b.setOutlineColor(Color::Black);
		b.setOutlineThickness(1);
		l.setOutlineColor(Color::Black);
		l.setOutlineThickness(1);
		r.setOutlineColor(Color::Black);
		r.setOutlineThickness(1);
	}
	void setpos(){								//draws the paddle to window;
		window.draw(l);
		window.draw(r);
		window.draw(b);
	}
	void setcol(int q, int w, int e){					//function to set color to paddle;
		l.setFillColor(Color(q, w, e));
		r.setFillColor(Color(q, w, e));
		b.setFillColor(Color(q, w, e));
	}
	void mov(int i){							//movement of paddle;
		if(i < 0 && x <= 0);
		else if(i > 0 && x+2*rad+len >= ww);
		else{
			x += i*1;
			l.setPosition(x,y);
			r.setPosition(x+50, y);
			b.setPosition(x+10, y);
		}
	}
};
paddle player1, player2;

void reset(){									//resets to initial position

	x = ww/2-6;
	y = wh/2-6;
	ball.setPosition(x, y);
	player1 = paddle(ww/2-(len+2*rad)/2, 20.0f);
	player2 = paddle(ww/2-(len+2*rad)/2, wh-2*rad-20);
	player1.setcol(255, 0, 0);
	player2.setcol(0, 0, 255);
	sx = 0;
	sy = .5;
}

void setwin(){
	
	window.clear(Color::White);
	player1.setpos();
	player2.setpos();
	window.draw(ball);
	std::ostringstream sp1, sp2;
	sp1 << m1;
	s1.setString(sp1.str());
	window.draw(s1);
	if(m2 > 9)
		s2.setPosition(ww-50, wh/2 - 25);
	sp2<< m2;
	s2.setString(sp2.str());
	window.draw(s2);
	window.display();
}

int main(){
	ww = 900;
	wh = 600;
	rad = 10;
	len = 50;
	x = ww/2-6;
	y = wh/2-6;
	sx = 0;
	sy = .5;
	m1 = 0;
	m2 = 0;
	Font font;
	font.loadFromFile("28 Days Later.ttf");
	s1.setFont(font);
	s1.setCharacterSize(50);
	s1.setColor(Color::Red);
	s1.setPosition(10,wh/2 - 25);
	s2.setFont(font);
	s2.setCharacterSize(50);
	s2.setColor(Color::Blue);
	s2.setPosition(ww-30, wh/2 - 25);
	settings.antialiasingLevel = 8;
	window.create(VideoMode(ww, wh), "Pong", Style::Default, settings);
	player1 = paddle(ww/2-(len+2*rad)/2, 20.0f);
	player2 = paddle(ww/2-(len+2*rad)/2, wh-2*rad-20);
	player1.setcol(255, 0, 0);
	player2.setcol(0, 0, 255);
	ball.setRadius(4);
	ball.setFillColor(Color(0, 255, 0));
	ball.setOutlineColor(Color::Black);
	ball.setOutlineThickness(3);
	ball.setPosition(x, y);

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Left))			//Keyboard buttons left and right for player1;
			player1.mov(-1);
		if(Keyboard::isKeyPressed(Keyboard::Right))
			player1.mov(1);
		if(Keyboard::isKeyPressed(Keyboard::A))				//Keys a and d for player 2;
			player2.mov(-1);
		if(Keyboard::isKeyPressed(Keyboard::D))
			player2.mov(1);
		if(y <= 0 || y >= wh-12){					//if ball reaches the top or bottom;
			if(y <=0)
				m2++;
			else
				m1++;
			if(m1 == 15){
				m1 = 0;
				m2 = 0;
				//
			}
			if(m2 == 15){
				m1 = 0;
				m2 = 0;
				//
			}
			reset();
		}
		if(sy >= 20)							//if ball crosses the maximum speed;
			reset();
		if(y >= player1.y && y <= player1.y + rad*2 && x + 6 >= player1.x && x + 6 <= player1.x+2*rad+len){		//collision p1;
			y = player1.y + rad * 2;
			sy = -sy;
			sx = ((x + 6) - (player1.x + rad + len/2)) * 0.01;
		}
		if(y + 12 >= player2.y && y + 12 <= player2.y + rad*2 && x + 6 >= player2.x && x + 6 <= player2.x+2*rad+len){	//collision p2
			y = player2.y - 12;
			sy = -sy;
			sx = ((x + 6) - (player2.x + rad + len/2)) * 0.01;
		}
		if(x < 0 || x + 12 > ww)					//reflection of ball from wall;
			sx = -sx;
		sy *= 1.00001;
		ball.setPosition(x+=sx, y+=sy);
		setwin();							//clear draw and display;
	}
}
