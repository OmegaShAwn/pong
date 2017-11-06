#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<cmath>
#include<sstream>
using namespace sf;

int ww, wh, m1, m2, status, cpu, r, level;
Text s1, s2, start, op, ex, playerwins;
Texture star;
Sprite diff1, diff2, diff3;
SoundBuffer sb;
Sound sound;
Music music;
float rad, len, x, y, sx, sy, d; 
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

void setwin(){
	
	window.clear(Color::White);
	player1.setpos();
	player2.setpos();
	window.draw(ball);
	std::ostringstream sp1, sp2;
	sp1 << m1;
	s1.setString(sp1.str());
	window.draw(s1);
	s1.setPosition(20,wh/2 - s1.getLocalBounds().height/2);
	s2.setPosition(ww- s2.getLocalBounds().width - 20, wh/2 - s2.getLocalBounds().height/2);
	sp2<< m2;
	s2.setString(sp2.str());
	window.draw(s2);
	window.display();
}

void reset(){									//resets to initial position

	x = ww/2-r;
	y = wh/2-r;
	ball.setPosition(x, y);
	player1 = paddle(ww/2-(len+2*rad)/2, 20);
	player2 = paddle(ww/2-(len+2*rad)/2, wh-2*rad-20);
	player1.setcol(255, 0, 0);
	player2.setcol(0, 0, 255);
	sx = 0;
	if(sy < 0)
		sy = -0.5;
	else
		sy = 0.5;
}

int main(){
	int o = 0;
	window.setVerticalSyncEnabled(true);
	r = 4;
	status = 0;
	ww = 900;
	wh = 600;
	rad = 10;
	len = 50;
	x = ww/2-r;
	y = wh/2-r;
	sx = 0;
	sy = .5;
	m1 = 0;
	m2 = 0;
	Font font;
	font.loadFromFile("28 Days Later.ttf");
	music.openFromFile("calm.wav");
	music.setLoop(true);
	sb.loadFromFile("ball.wav");
	sound.setBuffer(sb);
	sound.setVolume(30);
	s1.setFont(font);
	s1.setCharacterSize(50);
	s1.setColor(Color::Red);
	s2.setFont(font);
	s2.setCharacterSize(50);
	s2.setColor(Color::Blue);
	settings.antialiasingLevel = 8;
	window.create(VideoMode(ww, wh), "Pong", Style::Default, settings);
	player1 = paddle(ww/2-(len+2*rad)/2, 20.0f);
	player2 = paddle(ww/2-(len+2*rad)/2, wh-2*rad-20);
	player1.setcol(255, 0, 0);
	player2.setcol(0, 0, 255);
	ball.setRadius(r);
	ball.setFillColor(Color(0, 255, 0));
	ball.setOutlineColor(Color::Black);
	ball.setOutlineThickness(3);
	ball.setPosition(x, y);
	start.setCharacterSize(50);
	start.setFont(font);
	start.setPosition(ww/2, wh/2-75);
	start.setString("Vs CPU");
	op.setString("Vs Player");
	op.setCharacterSize(50);
	op.setFont(font);
	op.setPosition(ww/2, wh/2-175);
	ex.setString("Exit");
	ex.setCharacterSize(50);
	ex.setFont(font);
	ex.setPosition(ww/2, wh/2+25);
	playerwins.setFont(font);
	playerwins.setCharacterSize(50);
	int E, U, D, L, R, ESC;
	cpu = 0;
	CircleShape mball(150);
	mball.setFillColor(Color::Green);
	mball.setOutlineThickness(30);
	mball.setOutlineColor(Color::Black);
	mball.setPosition(wh/4-100, wh/2-150);
	level = 1;
	star.loadFromFile("star1.png");
	star.setSmooth(true);
	diff1.setTexture(star);
	diff1.setScale(0.15, 0.15);
	diff2.setTexture(star);
	diff2.setScale(0.15, 0.15);
	diff3.setTexture(star);
	diff3.setScale(0.15, 0.15);
	music.play();
	
	while(window.isOpen()){
		Event event;
		E = 0;
		U = 0;
		D = 0;
		L = 0;
		R = 0;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Return)
					E = 1;
			if(event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Up)
					U = 1;
			if(event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Down)
					D = 1;
			if(event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Left)
					L = 1;
			if(event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Right)
					R = 1;
			if(event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Escape)
					ESC = 1;
		}
		if(status == 0){
			window.clear(Color::White);
			window.draw(mball);
			if(D == 1)
				if(o < 2)
					o++;
			if(U == 1)
				if(o > 0)
					o--;
			if(o == 0){
				start.setColor(Color(0, 0, 0, 100));
				op.setColor(Color(0, 0, 0, 255));
				ex.setColor(Color(0, 0, 0, 100));
				if(E == 1){
					status = 1;
					cpu = 0;
					start.setString("Resume");
					ex.setString("Main Menu");
				}
			}
			if(o == 1){
				start.setColor(Color(0, 0, 0, 255));
				op.setColor(Color(0, 0, 0, 100));
				ex.setColor(Color(0, 0, 0, 100));
				diff1.setColor(Color(0, 0, 0, 255));
				diff1.setPosition(ww/2 + 170, wh/2 - 90);
				if(level < 3)
					if(R == 1){
						level++;
						sound.play();
					}
				if(level > 1)
					if(L == 1){
						level--;
						sound.play();
					}
				if(level < 2)
					diff2.setColor(Color(0, 0, 0, 100));
				else
					diff2.setColor(Color(0, 0, 0, 255));
				diff2.setPosition(ww/2 + 250, wh/2 - 90);
				if(level < 3)
					diff3.setColor(Color(0, 0, 0, 100));
				else
					diff3.setColor(Color(0, 0, 0, 255));
				diff3.setPosition(ww/2 + 330, wh/2 - 90);
				window.draw(diff1);
				window.draw(diff2);
				window.draw(diff3);
				if(E == 1){
					status = 1;
					cpu = 1;
					o = 0;
					start.setString("Resume");
					ex.setString("Main Menu");
				}
				
			}
			if(o == 2){
				start.setColor(Color(0, 0, 0, 100));
				op.setColor(Color(0, 0, 0, 100));
				ex.setColor(Color(0, 0, 0, 255));
				if(E == 1){
					window.close();
				}
			}
			window.draw(start);
			window.draw(op);
			window.draw(ex);
			window.display();
		}
		if(status == 1){
			if(Keyboard::isKeyPressed(Keyboard::Left))			//Keyboard buttons left and right for player1;
				player1.mov(-1);
			if(Keyboard::isKeyPressed(Keyboard::Right))
				player1.mov(1);
			if(cpu == 0){
				if(Keyboard::isKeyPressed(Keyboard::A))			//Keys a and d for player 2;
					player2.mov(-1);
				if(Keyboard::isKeyPressed(Keyboard::D))
					player2.mov(1);
			}
			else{
				if(level == 1){
					if(y < 580 && x + r - player2.x - rad - len/4 < 0)
						player2.mov(-1);
					else if(y < 580 && x + r - player2.x - rad - 3*len/4 > 0)
						player2.mov(1);
				}
				if(level == 2){
					if(sy < 0 && ww/2 - player2.x - rad - len/2 < 0)
						player2.mov(-1);
					else if(sy < 0 && ww/2 - player2.x - rad - len/2 > 0)
						player2.mov(1);
					else if(y < 580 && x + r - player2.x - rad < 0)
						player2.mov(-1);
					else if(y < 580 && x + r - player2.x - rad - len > 0)
						player2.mov(1);
					else
						player2.mov(rand()%2-1);
				}
				if(level == 3){
					if(sy > 0){
						d = (((player2.y - y)/sy) * sx) + x;
						while(d < 0 || d > ww-2*r){
							d = -d;
							if(d > ww-2*r)
								d = d - ww+2*r;
						}
					}
					if(sy < 0 && ww/2 - player2.x - rad - len/2 < 0)
						player2.mov(-1);
					else if(sy < 0 && ww/2 - player2.x - rad - len/2 > 0)
						player2.mov(1);
					else if(y < 580 && d - player2.x - rad < 0)
						player2.mov(-1);
					else if(y < 580 && d - player2.x - rad - len > 0)
						player2.mov(1);
					else
						player2.mov(rand()%2-1);
				}
			}
			if(ESC == 1){
				ESC = 0;
				status = 2;
			}
			if(y <= 0 || y >= wh-2*r){					//if ball reaches the top or bottom;
				if(y <=0)
					m2++;
				else
					m1++;
				if(m1 == 15){
					m1 = 0;
					m2 = 0;
					window.clear(Color::White);
					if(cpu == 0)
						playerwins.setString("Player 1 Wins");
					else
						playerwins.setString("Player Wins");
					playerwins.setPosition(ww/2-playerwins.getLocalBounds().width/2, wh/2-playerwins.getLocalBounds().height/2);
					playerwins.setColor(Color::Red);
					window.draw(playerwins);
					window.display();
					sleep(seconds(2));
					status = 0;
					start.setString("Vs CPU");
					op.setString("Vs Player");
					ex.setString("Exit");
				}
				if(m2 == 15){
					m1 = 0;
					m2 = 0;
					window.clear(Color::White);
					playerwins.setColor(Color::Blue);
					if(cpu == 0)
						playerwins.setString("Player 2 Wins");
					else
						playerwins.setString("CPU Wins");
					playerwins.setPosition(ww/2-playerwins.getLocalBounds().width/2, wh/2-playerwins.getLocalBounds().height/2);
					window.draw(playerwins);
					window.display();
					sleep(seconds(2));
					status = 0;
					start.setString("Vs CPU");
					op.setString("Vs Player");
					ex.setString("Exit");
				}
				reset();
				setwin();
				sleep(seconds(.5));
			}
			if(sy >= 20){							//if ball crosses the maximum speed;
				reset();
				setwin();
				sleep(seconds(.5));
			}
			if(y >= player1.y && y <= player1.y + rad*2 && x + r >= player1.x && x + r <= player1.x+2*rad+len){		//collision p1;
				y = player1.y + rad * 2;
				sy = -sy;
				sound.play();
				sx = ((x + r) - (player1.x + rad + len/2)) * 0.035;
			}
			if(y + 2*r >= player2.y && y + 2*r <= player2.y + rad*2 && x + r >= player2.x && x + r <= player2.x+2*rad+len){	//collision p2
				y = player2.y - 2*r;
				sy = -sy;
				sound.play();
				sx = ((x + r) - (player2.x + rad + len/2)) * 0.035;
			}
			if(x < 0 || x + 2*r > ww)					//reflection of ball from wall;
				sx = -sx;
			sy *= 1.00003;
			ball.setPosition(x+=sx, y+=sy);
			setwin();							//clear draw and display;
		}
		if(status == 2){
			if(ESC == 1){
				ESC = 0;
				status = 1;
			}
			window.clear(Color::White);
			window.draw(mball);
			if(Keyboard::isKeyPressed(Keyboard::Down))
				o = 1;
			if(Keyboard::isKeyPressed(Keyboard::Up))
				o = 0;
			if(o == 0){
				start.setColor(Color(0, 0, 0, 255));
				ex.setColor(Color(0, 0, 0, 100));
				if(E == 1)
					status = 1;
			}
			if(o == 1){
				start.setColor(Color(0, 0, 0, 100));
				ex.setColor(Color(0, 0, 0, 255));
				if(E == 1){
					o = 0;
					status = 0;
					reset();		
					m1 = 0;
					m2 = 0;
					start.setString("Vs CPU");
					op.setString("Vs Player");
					ex.setString("Exit");
				}
			}
			window.draw(start);
			window.draw(ex);
			window.display();
		}
	}
}
