#include"SFML/Graphics.hpp"
#include<unistd.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;
bool die=false;
struct Snake
{
    int x,y;

} s[100];

struct Fruit{
    int x,y;
}f;

int N=50, M=30, size=20;
int w=size*N+200, h=size*M;
int direct=3, num=10,p=0;

stringstream point;
RenderWindow window(VideoMode(w,h),"Snake");
RectangleShape background(Vector2f(size,size));
RectangleShape endgame(Vector2f((w-200)/2,h/2));
RectangleShape fruit(Vector2f(size,size));
RectangleShape snake(Vector2f(size,size));
RectangleShape headSnake(Vector2f(size,size));
RectangleShape Point_table(Vector2f(10*size,10*size));
Font font;
Text text_point,text_endgame;

string numtostr(int n){
    string s="";
    while (n)
    {
        s=s+char((n%10)+'0');
        n/=10;
    }
    reverse(s.begin(),s.end());
    return "YOUR POINT: "+s;
    
}

void init(){
    snake.setFillColor(Color::Yellow);
    headSnake.setFillColor(Color::Cyan);
    background.setFillColor(Color::Green);
    background.setOutlineThickness(3);
    fruit.setFillColor(Color::Red);
    endgame.setFillColor(Color::Blue);
    Point_table.setFillColor(Color::White);
    Point_table.setPosition(N*size,0);
    font.loadFromFile("Font.ttf");
    text_point.setFont(font);
    text_point.setCharacterSize(20);
    text_point.setFillColor(Color::Red);
    text_point.setStyle(Text::Bold);
    text_point.setPosition(N*size,0);
    text_endgame.setFont(font);
    text_endgame.setCharacterSize(30);
    text_endgame.setFillColor(Color::White);
    text_endgame.setStyle(Text::Bold);
    text_endgame.setPosition(17*size,13*size);
    f.x=rand()%N;
    f.y=rand()%M;
}

void move(){
    for(int i=num;i>0;i--){
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    if(direct==1) s[0].x-=1;
    if(direct==2) s[0].y-=1;
    if(direct==3) s[0].x+=1;
    if(direct==4) s[0].y+=1;
    if(s[0].x==f.x && s[0].y==f.y){
        ++num;
        p++;
        f.x=rand()%N;
        f.y=rand()%M;
    }
    //cham bien
    if(s[0].x>=N) s[0].x=0;
    if(s[0].x<0) s[0].x=N-1;
    if(s[0].y>=M) s[0].y=0;
    if(s[0].y<0) s[0].y=M;
    for(int i=1;i<num;i++){
        if(s[0].x==s[i].x && s[0].y==s[i].y) 
            die=true;
    }
}

void control(){
    if(Keyboard::isKeyPressed(Keyboard::Left)){
        if(direct==3) direct=3;
        else direct=1;
    }
    if(Keyboard::isKeyPressed(Keyboard::Up)){
        if(direct==4) direct=4;
        else direct=2;
    } 
    if(Keyboard::isKeyPressed(Keyboard::Right)){
        if(direct==1) direct=1;
        else direct=3;
    }
    if(Keyboard::isKeyPressed(Keyboard::Down)) {
        if(direct==2) direct=2;
        else direct=4;
    }
}

void drawBackground(){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            background.setPosition(i*size,j*size);
            window.draw(background);
        }
    }
    string P="";
    P=P+numtostr(p);
    text_point.setString(P);
    window.draw(Point_table);
    window.draw(text_point);
}

void drawSnake(){
    headSnake.setPosition(s[0].x*size,s[0].y*size);
    window.draw(headSnake);
    for(int i=1;i<num;i++){
        snake.setPosition(s[i].x*size,s[i].y*size);
        window.draw(snake);
    }
}

void drawFruit(){
    int i=0;
    fruit.setPosition(f.x*size,f.y*size);
    window.draw(fruit);
}

void drawEndgame(){
    endgame.setPosition(11*size,7*size );
    window.draw(endgame);
    string P="";
    P=P+"Congratulation\n"+numtostr(p);
    text_endgame.setString(P);
    window.draw(text_endgame);
}

int main(){
    srand(time(0));
    init();
    Clock clock;
    float timer=0, delay=0.1;
    while(window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        Event evnt;
        while(window.pollEvent(evnt)){
            if(evnt.type==Event::Closed)
                window.close();
        }
        control();
        if(timer>delay){
            timer=0;
            move();
        }
        if(die) {
            for(int i=0;i<10;i++){
                window.clear();
                if(i%2==0) background.setFillColor(Color::Magenta);
                else background.setFillColor(Color::Green);
                drawBackground();
                drawSnake();
                drawFruit();
                drawEndgame();
                window.display();
                sleep(1);
                
            }
            window.close();
        }
        else{
            window.clear();
            drawBackground();
            drawSnake();
            drawFruit();
            window.display();
        }
    }
    return 0;
}
