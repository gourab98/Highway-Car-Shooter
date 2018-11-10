#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<iostream>

using namespace sf;
using namespace std;

const double SCREEN_WIDTH=1280;
const double SCREEN_HEIGH=700;
const int borderLeft=245;
const int borderRight=975;
const int carWidth=75;
const int carHeight=70;
int getRandomNumber(int a,int b);
double gameSpeed=0.7,BackgroundY1=0,BackgroundY2=-700;
int obs1X,obs1Y;
Color notSelected(255,255,255),done(255,255,0);

int getRandomNumber(int a, int b)
{
    static bool first = true;
    if (first)
    {
        srand( time(NULL) );
        first = false;
    }
    int result=a + rand() % (( b + 1 ) - a);
    return result;
}

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1280,700),"Highway Car Shooter");
    ///    window.SetFramerateLimit(60);

    float time=0.0f;
    Clock key;
    Font style1,style2;
    double carX,carY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y;
    Text scoretxt,gameovertxt,lifetxt,mgzntxt,gametxt,newgametxt,highscoretxt,leveltxt,helptxt,exittxt,loadgametxt,note;
    Texture backgroundTexture,carTexture,obs1Texture,obs2Texture,obs3Texture,obs4Texture,game_fornt,game_overTexture;
    SoundBuffer gameSound;


     ///Font
    style1.loadFromFile("Fonts/Font1.ttf");
    gametxt.setFont(style1);
    gametxt.setString("Highway Car Shooter!!!");
    gametxt.setCharacterSize(100);
    gametxt.setScale(1.f,1.f);
    gametxt.setFillColor(Color::Black);

    style2.loadFromFile("Fonts/Font2.ttf");
    newgametxt.setFont(style2);
    newgametxt.setString("New Game ");
    newgametxt.setCharacterSize(80);
    newgametxt.setScale(0.7f,0.7f);
    newgametxt.setFillColor(notSelected);

    loadgametxt.setFont(style2);
    loadgametxt.setString("Load Game ");
    loadgametxt.setCharacterSize(80);
    loadgametxt.setScale(0.7f,0.7f);
    loadgametxt.setFillColor(notSelected);

    leveltxt.setFont(style2);
    leveltxt.setString("Levels ");
    leveltxt.setCharacterSize(80);
    leveltxt.setScale(0.7f,0.7f);
    leveltxt.setFillColor(notSelected);

    helptxt.setFont(style2);
    helptxt.setString("Instruction ");
    helptxt.setCharacterSize(80);
    helptxt.setScale(0.7f,0.7f);
    helptxt.setFillColor(notSelected);

    exittxt.setFont(style2);
    exittxt.setString("Exit ");
    exittxt.setCharacterSize(80);
    exittxt.setScale(0.7f,0.7f);
    exittxt.setFillColor(notSelected);

    note.setFont(style1);
    note.setString("#Please Press Space To Select#");
    note.setCharacterSize(50);
    note.setScale(0.7f,0.7f);
    note.setFillColor(Color::Green);


    ///Set racer and Obs position
    carX=SCREEN_WIDTH/2;
    carY=SCREEN_HEIGH-carHeight;
    Obs1X=getRandomNumber(borderLeft,borderRight);
    Obs2X=getRandomNumber(borderLeft,borderRight);
    Obs3X=getRandomNumber(borderLeft,borderRight);
    Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300;

    ///music:
    //Music gamemusic,menumusic;
    //gamemusic.openFromFile("sound/game.wav");
    //gamemusic.setVolume(1000);

    ///load files
    gameSound.loadFromFile("sound/game.wav");
    backgroundTexture.loadFromFile("Textures/background.png");
    game_overTexture.loadFromFile("Textures/Game_over.png");
    carTexture.loadFromFile("Textures/Car.png");
    obs1Texture.loadFromFile("Textures/obs1.png");
    obs2Texture.loadFromFile("Textures/obs2.png");
    obs3Texture.loadFromFile("Textures/obs3.png");
    obs4Texture.loadFromFile("Textures/obs4.png");
    game_fornt.loadFromFile("Textures/game_front.png");

     ///Initial game music
    Sound GameSound,menubutton;
    GameSound.setBuffer(gameSound);
    GameSound.play();
    GameSound.setLoop(true);

    ///create sprite
    Sprite background1(backgroundTexture);
    Sprite background2(backgroundTexture);
    Sprite game_over(game_overTexture);
    Sprite car(carTexture);
    Sprite obs1(obs1Texture);
    Sprite obs2(obs2Texture);
    Sprite obs3(obs3Texture);
    Sprite obs4(obs4Texture);
    Sprite game_front(game_fornt);
    //car.setPosition(Vector2f(600,600));
    ///obs1.setPosition(Vector2f(610,0));
     bool menu=true,game=false, gameover=false;

     int menuselect=1;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==event.Closed)
            {
                window.close();
            }
        }
       if(menu){
        gametxt.setPosition(20.f,3.f);
        newgametxt.setPosition(700.f,200.f);
        loadgametxt.setPosition(700.f,280.f);
        leveltxt.setPosition(700.f,360.f);
        helptxt.setPosition(700.f,440.f);
        exittxt.setPosition(700.f,520.f);
        note.setPosition(600.f,640.f);


        window.clear();
        game_front.setScale(1.f,1.f);

        window.draw(game_front);
        window.draw(gametxt);
        window.draw(newgametxt);
        window.draw(loadgametxt);
        window.draw(leveltxt);
        window.draw(helptxt);
        window.draw(exittxt);
        window.draw(note);
        window.display();
           time=key.getElapsedTime().asSeconds();

            if(Keyboard::isKeyPressed(Keyboard::Down) && time > 0.2)
            {
                menubutton.play();
                menuselect++;
                key.restart();
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) && time > 0.2)
            {
                menubutton.play();
                menuselect--;
                key.restart();
            }
        }
         if(menuselect%5==1)
            {
                newgametxt.setFillColor(done);
                loadgametxt.setFillColor(notSelected);
                leveltxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);

        if(Keyboard::isKeyPressed(Keyboard::Space) && game==false)
        {
           game=true;
           gameover=false;
           menu=false;
        }
            }
            else if(menuselect%5==2)
            {
                loadgametxt.setFillColor(done);
                leveltxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
            }
            else if(menuselect%5==3)
            {
                leveltxt.setFillColor(done);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
            }
            else if(menuselect%5==4)
            {
                helptxt.setFillColor(done);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
                leveltxt.setFillColor(notSelected);
            }
            else if(menuselect%5==0)
            {
                exittxt.setFillColor(done);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
                leveltxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);

        if(Keyboard::isKeyPressed(Keyboard::Space) && game==false)
        {
           return 0;
        }
            }


     if(game){
          if(Keyboard::isKeyPressed(Keyboard::Escape) && game==true)
        {
           game=false;
           gameover=false;
           menu=true;
        }
         ///gamemusic.play();
         ///gamemusic.setLoop(true);

        ///Create scrolling background
        background1.setPosition(0,BackgroundY1);
        background2.setPosition(0,BackgroundY2);
        if (BackgroundY2>0)
        {
            BackgroundY1=0;
            BackgroundY2=BackgroundY1-700;
        }
        BackgroundY1+=0.3;
        BackgroundY2+=0.3;

        ///Set car position
        car.setPosition(carX,carY);
        obs1.setPosition(Obs1X,Obs1Y);
        obs2.setPosition(Obs2X,Obs2Y);
        obs3.setPosition(Obs3X,Obs3Y);
        obs4.setPosition(Obs4X,Obs4Y);

        ///Set Obs LOOP
        if (Obs1Y>SCREEN_HEIGH)
        {
            Obs1Y=0;
            Obs1X=getRandomNumber(borderLeft,borderRight);
            ///score++;
        }
        else
        {
            Obs1Y=Obs1Y+gameSpeed;
        }
        if (Obs2Y>SCREEN_HEIGH)
        {
            Obs2Y=0;
            Obs2X=getRandomNumber(borderLeft,borderRight);
            ///score++;
        }
        else
        {
            Obs2Y=Obs2Y+gameSpeed;
        }
        if (Obs3Y>SCREEN_HEIGH)
        {
            Obs3Y=0;
            Obs3X=getRandomNumber(borderLeft,borderRight);
            ///score++;
        }
        else
        {
            Obs3Y=Obs3Y+gameSpeed;
        }
        if (Obs4Y>SCREEN_HEIGH)
        {
            Obs4Y=0;
            Obs4X=getRandomNumber(borderLeft,borderRight);
            ///score++;
        }
        else
        {
            Obs4Y=Obs4Y+gameSpeed;
        }

        while(window.pollEvent(event))
        {
            if(event.type==event.Closed)
            {
                window.close();
            }
        }
         if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                if(carX>borderLeft)
                {
                    carX-=.7;
                    car.move(-10.f,0.0f);///.3

                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Right))
            {

                if(carX<borderRight)
                {
                    carX=carX+.7;
                    car.move(10.f,0.0f);///.3
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                if(carY>0)
                {
                    carY=carY-.5;
                    car.move(0.0f,-10.f);///.4
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                if(carY<SCREEN_HEIGH-70)
                {
                    carY=carY+.5;
                    car.move(0.0f,10.f);///.4
                }
            }

            ///Check if accident happen
        if (((carX>=(Obs1X-30)) &&(carX<=(Obs1X+30)))&&((carY>=(Obs1Y-30)) &&(carY)<=(Obs1Y+30)))
        {
            ///GameSound.stop();
            gameover=true;
        };
        if (((carX>=(Obs2X-30)) &&(carX<=(Obs2X+30)))&&((carY>=(Obs2Y-30)) &&(carY)<=(Obs2Y+30)))
        {
            ///GameSound.stop();
            gameover=true;
        };
        if (((carX>=(Obs3X-30)) &&(carX<=(Obs3X+30)))&&((carY>=(Obs3Y-30)) &&(carY)<=(Obs3Y+30)))
        {
            ///GameSound.stop();
            gameover=true;
        };
        if (((carX>=(Obs4X-30)) &&(carX<=(Obs4X+30)))&&((carY>=(Obs4Y-30)) &&(carY)<=(Obs4Y+30)))
        {
            ///GameSound.stop();
            gameover=true;
        };

        window.clear();
        window.draw(background1);
        window.draw(background2);
        window.draw(car);
        window.draw(obs1);
        window.draw(obs2);
        window.draw(obs3);
        window.draw(obs4);
        window.display();
     }
     if(gameover)
     {   game=false;
         menu=false;
       GameSound.stop();

         window.draw(game_over);
         window.display();
         if(Keyboard::isKeyPressed(Keyboard::Space))
        {
           menu=true;
           game=false;
           gameover=false;
        }
     }
    }
    return 0;
}
