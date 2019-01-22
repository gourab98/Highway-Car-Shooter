    #include<bits/stdc++.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
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
    double BackgroundY1=0,BackgroundY2=-700;
    int obs1X,obs1Y;
    Color notSelected(255,255,255),done(0,255,0);

    class Bullet1
    {
    public:
        Sprite shape;

        Bullet1(Texture *texture, Vector2f pos)
        {
            pos.x=pos.x+30;
            shape.setTexture(*texture);
            shape.setScale(2.0f, 2.0f);
            shape.setPosition(pos);
        }

    };

    class Bullet2
    {
    public:
        Sprite shapeo;

        Bullet2(Texture *texture, Vector2f pos)
        {
            pos.x=pos.x+30;
            pos.y=pos.y+140;
            shapeo.setTexture(*texture);
            shapeo.setScale(2.0f, 2.0f);
            shapeo.setPosition(pos);
        }

    };

    int getRandomNumber(int a, int b)
    {
        static bool first = true;
        if (first)
        {
            srand( time(NULL) );
            srand( time(NULL) );
            first = false;
        }
        int result=a + rand() % (( b + 1 ) -a);
        return result;
    }
     vector<Bullet1> bullet;
     vector<Bullet2> bullet2;

    int main()
    {
        srand(time(NULL));

        RenderWindow window(VideoMode(1280,700),"Highway Car Shooter");

        float time=0.0f;
        Clock key;
        Font style1,style2,style3;
        double carX,carY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y,gameSpeed=0.6,Obs5X,Obs5Y,Obs6X,Obs6Y;
        Text scoretxt,lifetxt,mgzntxt,gametxt,newgametxt,leveltxt,helptxt,exittxt,loadgametxt,note,gameovertxt,helptext,highscoretxt,level1txt;
        Texture backgroundTexture,carTexture,obs1Texture,obs2Texture,obs3Texture,obs4Texture,obs5Texture,obs6Texture,game_fornt,game_overTexture,bullet1,bulleto,game_fornt2;
        SoundBuffer gameSound,crashSound,bulletSound;

        ///Font
        style1.loadFromFile("Fonts/Font1.ttf");
        gametxt.setFont(style1);
        gametxt.setString("Highway Car Shooter!!!");
        gametxt.setCharacterSize(100);
        gametxt.setScale(1.f,1.f);
        gametxt.setFillColor(Color::Yellow);

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
        leveltxt.setString("Highscore ");
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


        scoretxt.setFont(style1);
        scoretxt.setCharacterSize(20);
        scoretxt.setScale(1.5,1.5);
        scoretxt.setFillColor(Color::Cyan);
        scoretxt.setPosition(5.0f,0.0f);

        ///style3.loadFromFile("Fonts/Font3.ttf");
        gameovertxt.setFont(style2);
        gameovertxt.setString("GAME OVER!!! ");
        gameovertxt.setCharacterSize(150);
        gameovertxt.setScale(0.7f,0.7f);
        gameovertxt.setFillColor(Color::Black);

        ///instruction
        helptext.setFont(style2);
        helptext.setString("Press 'up arrow' to go up.\n Press 'down arrow' to down.\n Press 'right arrow' to go right.\n Press 'left arrow' to go left. \n Press 'z' to shoot.\n Press 'Esc' to go to main menu. \n\n Level will be upgraded after certain scores.\n\n Think twice before shooting a police car.");
        helptext.setCharacterSize(50);
        helptext.setScale(0.7f,0.7f);
        helptext.setFillColor(Color::White);

        highscoretxt.setFont(style1);
        highscoretxt.setCharacterSize(50);
        highscoretxt.setScale(1.5,1.5);
        highscoretxt.setFillColor(Color::White);
        highscoretxt.setPosition(500.0f,250.0f);

        level1txt.setFont(style1);
        level1txt.setCharacterSize(20);
        level1txt.setScale(1.5,1.5);
        level1txt.setFillColor(Color::Yellow);
        level1txt.setPosition(1100.0f,0.0f);


        ///Set racer and Obs position
        carX=SCREEN_WIDTH/2;
        carY=SCREEN_HEIGH-carHeight;
        Obs1X=getRandomNumber(borderLeft,borderRight);
        Obs2X=getRandomNumber(borderLeft,borderRight);
        Obs3X=getRandomNumber(borderLeft,borderRight);
        Obs4X=getRandomNumber(borderLeft,borderRight);
        Obs5X=getRandomNumber(borderLeft,borderRight);
        Obs6X=getRandomNumber(borderLeft,borderRight);
        Obs1Y=-200,Obs2Y=-400,Obs3Y=-600,Obs4Y=-800;Obs5Y=-1000,Obs6Y=-1200;

        ///load files
        crashSound.loadFromFile("sound/crash.wav");
        gameSound.loadFromFile("sound/game.wav");
        bulletSound.loadFromFile("sound/bullet.wav");
        backgroundTexture.loadFromFile("Textures/background.png");
        game_overTexture.loadFromFile("Textures/Game_over.png");
        carTexture.loadFromFile("Textures/Car.png");
        obs1Texture.loadFromFile("Textures/obs1.png");
        obs2Texture.loadFromFile("Textures/obs2.png");
        obs3Texture.loadFromFile("Textures/obs3.png");
        obs4Texture.loadFromFile("Textures/obs4.png");
        obs5Texture.loadFromFile("Textures/obs5.png");
        obs6Texture.loadFromFile("Textures/obs6.png");
        game_fornt.loadFromFile("Textures/game_front.png");
        bullet1.loadFromFile("Textures/bullet.png");
        bulleto.loadFromFile("Textures/bullet1.png");
        game_fornt2.loadFromFile("Textures/game_front2.png");

        ///Initial game music
        Sound GameSound,menubutton;
        GameSound.setBuffer(gameSound);
        GameSound.play();
        GameSound.setLoop(true);

         ///Initial game music
        Sound CrashSound;
        CrashSound.setBuffer(crashSound);

         Sound BulletSound;
        BulletSound.setBuffer(bulletSound);


        ///create sprite
        Sprite background1(backgroundTexture);
        Sprite background2(backgroundTexture);
        Sprite game_over(game_overTexture);
        Sprite car(carTexture);
        Sprite obs1(obs1Texture);
        Sprite obs2(obs2Texture);
        Sprite obs3(obs3Texture);
        Sprite obs4(obs4Texture);
        Sprite obs5(obs5Texture);
        Sprite obs6(obs6Texture);
        Sprite game_front(game_fornt);
        Sprite game_front21(game_fornt2);

        bool menu=true,game=false,help=false, gameover=false,highscoreg=false;
        Clock  guli, clock,cl,gou;
        float gulii,tym,gu;
        gulii=guli.getElapsedTime().asSeconds();
        gu=gou.getElapsedTime().asSeconds();
        tym=clock.getElapsedTime().asSeconds();

        int menuselect=1,score=0,highscore,level1=1,i=1,j=0,m=7,k=1;

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
            if(menu)
            {
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
                    level1=1,i=1,j=0,m=7,score=0,k=1;
                    gameSpeed=0.4;
                    game=true;
                    gameover=false;
                    menu=false;
                    CrashSound.stop();

                }
            }
            else if(menuselect%5==2)
            {
                loadgametxt.setFillColor(done);
                leveltxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                if(Keyboard::isKeyPressed(Keyboard::Space) && game==false)
                {
                    game=true;
                    gameover=false;
                    menu=false;
                    CrashSound.stop();
                }
            }
            else if(menuselect%5==3)
            {
                leveltxt.setFillColor(done);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
                if(Keyboard::isKeyPressed(Keyboard::Space))
                {
                   highscoreg=true;
                }
            }
            else if(menuselect%5==4)
            {
                helptxt.setFillColor(done);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
                leveltxt.setFillColor(notSelected);
                if(Keyboard::isKeyPressed(Keyboard::Space))
                {
                   help=true;
                }
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


            if(game)
            {
                 if(score==0)
                 {level1=1;}
                 level1txt.setString("Level: "+ std::to_string(level1));

                if(Keyboard::isKeyPressed(Keyboard::Escape) && game==true)
                {
                    game=false;
                    gameover=false;
                    menu=true;
                    CrashSound.stop();
                }


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
                obs5.setPosition(Obs5X,Obs5Y);
                obs6.setPosition(Obs6X,Obs6Y);

                if(score==0)
                {
                gameSpeed=0.6;

                }

                if(score%m==0  && score>0)
                {
                 i++;

                 m=m+10;
                 level1=i;
                }
                 if(i>j)
                 {
                   j=i;
                   gameSpeed+=.2;
                   BackgroundY1+=0.2;
                   BackgroundY2+=0.2;

                 }

                scoretxt.setPosition(5.0f,0.0f);
                scoretxt.setCharacterSize(20);

                ///Set Obs LOOP
                if (Obs1Y>SCREEN_HEIGH)
                {
                    Obs1Y=-200;
                    Obs1X=getRandomNumber(borderLeft,borderRight);
                    ///score++;
                }
                else
                {
                    Obs1Y=Obs1Y+gameSpeed;
                }
                if (Obs2Y>SCREEN_HEIGH)
                {
                    Obs2Y=-400;
                    Obs2X=getRandomNumber(borderLeft,borderRight);
                    ///score++;
                }
                else
                {
                    Obs2Y=Obs2Y+gameSpeed;
                }
                if (Obs3Y>SCREEN_HEIGH)
                {
                    Obs3Y=-600;
                    Obs3X=getRandomNumber(borderLeft,borderRight);
                    ///score++;
                }
                else
                {
                    Obs3Y=Obs3Y+gameSpeed;
                }
                if (Obs4Y>SCREEN_HEIGH)
                {
                    Obs4Y=-800;
                    Obs4X=getRandomNumber(borderLeft,borderRight);
                    ///score++;
                }
                else
                {
                    Obs4Y=Obs4Y+gameSpeed;
                }
                 if (Obs5Y>SCREEN_HEIGH)
                {
                    Obs5Y=-1000;
                    Obs5X=getRandomNumber(borderLeft,borderRight);
                    ///score++;
                }
                else
                {
                    Obs5Y=Obs5Y+gameSpeed;
                }
                 if (Obs6Y>SCREEN_HEIGH)
                {
                    Obs6Y=-1000;
                    Obs6X=getRandomNumber(borderLeft,borderRight);
                    ///score++;
                }
                else
                {
                    Obs6Y=Obs6Y+gameSpeed;
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
                gulii=guli.getElapsedTime().asSeconds();
                if(Keyboard::isKeyPressed(Keyboard::Z) && gulii > 0.2f)
                {
                       bullet.push_back(Bullet1(&bullet1,Vector2f(car.getPosition())));
                       guli.restart();
                       BulletSound.play();
                       gulii=0.0;
                }
                for(int kl=0;kl<bullet.size();kl++)
                {
                    bullet[kl].shape.move(0.0f,-2.5f);
                    if(bullet[kl].shape.getPosition().y<0)
                    {
                        bullet.erase(bullet.begin()+kl);

                    }
                }
                gu=gou.getElapsedTime().asSeconds();
                if(gu>0.4f)
                {
                 bullet2.push_back(Bullet2(&bulleto,Vector2f(obs6.getPosition())));
                 gou.restart();
                 gu=0.0f;
                }
                for(int l=0;l<bullet2.size();l++)
                {
                  bullet2[l].shapeo.move(0.0f,3.5f);
                  if(bullet2[l].shapeo.getPosition().y<-130)
                  {
                     bullet2.erase(bullet2.begin()+l);
                  }
                }


                ///Check if accident happen
                if (((carX>=(Obs1X-70)) &&(carX<=(Obs1X+50)))&&((carY>=(Obs1Y-109)) &&(carY)<=(Obs1Y+109)))
                {
                    ///GameSound.stop();
                    gameover=true;
                    game=false;
                    menu=false;
                    CrashSound.play();
                };
                if (((carX>=(Obs2X-50)) &&(carX<=(Obs2X+50)))&&((carY>=(Obs2Y-80)) &&(carY)<=(Obs2Y+80)))
                {


                    ///GameSound.stop();
                    gameover=true;
                    game=false;
                    menu=false;
                    CrashSound.play();
                };
                if (((carX>=(Obs3X-45)) &&(carX<=(Obs3X+45)))&&((carY>=(Obs3Y-133)) &&(carY)<=(Obs3Y+133)))
                {
                    ///GameSound.stop();
                    gameover=true;
                    game=false;
                    menu=false;
                    CrashSound.play();
                };
                if (((carX>=(Obs4X-50)) &&(carX<=(Obs4X+50)))&&((carY>=(Obs4Y-109)) &&(carY)<=(Obs4Y+109)))
                {
                    ///GameSound.stop();
                    gameover=true;
                    game=false;
                    menu=false;
                    CrashSound.play();
                };
                if (((carX>=(Obs5X-50)) &&(carX<=(Obs5X+50)))&&((carY>=(Obs5Y-109)) &&(carY)<=(Obs5Y+109)))
                {
                    ///GameSound.stop();
                    gameover=true;
                    game=false;
                    menu=false;
                    CrashSound.play();
                };
                if (((carX>=(Obs6X-80)) &&(carX<=(Obs6X+80)))&&((carY>=(Obs6Y-140)) &&(carY)<=(Obs6Y+140)))
                {
                    ///GameSound.stop();
                    gameover=true;
                    game=false;
                    menu=false;
                    CrashSound.play();
                };
                for(int l=0;l<bullet2.size();l++)
                {
                  if(bullet2[l].shapeo.getGlobalBounds().intersects(car.getGlobalBounds()))
                      {
                         gameover=true;
                         game = false;
                         menu = false;
                         bullet2.erase(bullet2.begin()+l);
                         CrashSound.play();
                      }

                }

                for(int kl=0;kl<bullet.size();kl++)
                {
                    if(bullet[kl].shape.getGlobalBounds().intersects(obs1.getGlobalBounds()))
                    {
                        bullet.erase(bullet.begin()+kl);
                        Obs1X=getRandomNumber(borderLeft,borderRight);
                        Obs1Y=-200.f;

                        score++;
                    }
                    if(bullet[kl].shape.getGlobalBounds().intersects(obs2.getGlobalBounds()))
                    {
                        bullet.erase(bullet.begin()+kl);
                        Obs2X=getRandomNumber(borderLeft,borderRight);
                        Obs2Y=-400.f;

                        score++;
                    }
                    if(bullet[kl].shape.getGlobalBounds().intersects(obs3.getGlobalBounds()))
                    {
                        bullet.erase(bullet.begin()+kl);
                        Obs3X=getRandomNumber(borderLeft,borderRight);
                        Obs3Y=-600.f;

                        score++;
                    }
                    if(bullet[kl].shape.getGlobalBounds().intersects(obs4.getGlobalBounds()))
                    {
                        bullet.erase(bullet.begin()+kl);
                        Obs4X=getRandomNumber(borderLeft,borderRight);
                        Obs4Y=-800.f;

                        score++;

                    }

                    if(bullet[kl].shape.getGlobalBounds().intersects(obs6.getGlobalBounds()))
                    {
                        bullet.erase(bullet.begin()+kl);
                        Obs6X=getRandomNumber(borderLeft,borderRight);
                        Obs6Y=-1200.f;

                        score=score+5;

                    }
                    if(bullet[kl].shape.getGlobalBounds().intersects(obs5.getGlobalBounds()))
                    {
                        bullet.erase(bullet.begin()+kl);
                        Obs5X=getRandomNumber(borderLeft,borderRight);
                        Obs5Y=-1000.f;

                        gameover=true;
                        menu=false;
                        game=false;
                        CrashSound.play();
                    }
                         if(score>highscore)
                        {highscore=score;}

                }
                scoretxt.setString("Score: "+ std::to_string(score));

                window.clear();
                window.draw(background1);
                window.draw(background2);
                window.draw(scoretxt);
                window.draw(level1txt);
                window.draw(car);
                window.draw(obs1);
                window.draw(obs2);
                window.draw(obs3);
                window.draw(obs4);
                window.draw(obs5);
                window.draw(obs6);

                for(int kl=0;kl<bullet.size();kl++)
                {
                    window.draw(bullet[kl].shape);
                }

                for(int l=0;l<bullet2.size();l++)
                {
                  window.draw(bullet2[l].shapeo);
                }
                window.display();
            }
            if(gameover)
            {
                game=false;
                menu=false;

                GameSound.stop();


                gameovertxt.setPosition(13.f,2.f);
                scoretxt.setPosition(500.0f,500.f);
                highscoretxt.setPosition(400.0f,250.0f);
                scoretxt.setCharacterSize(50);
                window.draw(game_over);
                window.draw(gameovertxt);
                window.draw(scoretxt);
               highscoretxt.setString("Highscore: "+ std::to_string(highscore));
                window.draw(highscoretxt);
               window.display();
                window.display();

                /*
                tym=clock.getElapsedTime().asSeconds();
                if(tym>8.0f)
                {
                   ///CrashSound.play();
                   ///CrashSound.setLoop(true);
                   GameSound.play();
                   menu=true;
                    gameover=false;
                    game=false;
                    clock.restart();
                    tym=0.0;

                }*/
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {

                  gameover=false;
                  game=false;
                  menu=true;

                }

                if(Keyboard::isKeyPressed(Keyboard::Space))
                {
                    ///Set racer and Obs position
                    carX=SCREEN_WIDTH/2;
                    carY=SCREEN_HEIGH-carHeight;
                    Obs1X=getRandomNumber(borderLeft,borderRight);
                    Obs2X=getRandomNumber(borderLeft,borderRight);
                    Obs3X=getRandomNumber(borderLeft,borderRight);
                    Obs4X=getRandomNumber(borderLeft,borderRight);
                    Obs5X=getRandomNumber(borderLeft,borderRight);
                    Obs6X=getRandomNumber(borderLeft,borderRight);
                    Obs1Y=-100,Obs2Y=-300,Obs3Y=-500,Obs4Y=-700,Obs5Y=-900,Obs6Y=-1100;



                    gameSpeed=0.4;
                    score=0;
                    menu=true;
                    gameover=false;
                    game=false;
                    CrashSound.stop();
                    GameSound.play();
                }
                if(Keyboard::isKeyPressed(Keyboard::Escape))
               {
                gametxt.setPosition(20.f,3.f);
                newgametxt.setPosition(700.f,200.f);
                loadgametxt.setPosition(700.f,280.f);
                leveltxt.setPosition(700.f,360.f);
                helptxt.setPosition(700.f,440.f);
                exittxt.setPosition(700.f,520.f);
                note.setPosition(600.f,640.f);
                level1=1,i=1,j=0,m=7,score=0;

                    gameover==false;
                    game=false;
                    menu=true;
                     CrashSound.stop();

               }
            }
            if(help)
            {
                menu=false;
                game=false;
               helptext.setPosition(400.0f,160.0f);


               window.draw(game_front21);
               window.draw(helptext);
               window.display();
               if(Keyboard::isKeyPressed(Keyboard::Escape))
               {

                    menu=true;
                    help=false;
               }

            }

            if(highscoreg)
            {
                menu=false;
                game=false;

                highscoretxt.setString("Highscore: "+ std::to_string(highscore));
               window.draw(game_front21);
               window.draw(highscoretxt);
               window.display();
               if(Keyboard::isKeyPressed(Keyboard::Escape))
               {

                    menu=true;
                    highscoreg=false;
               }

            }
        }
        return 0;
    }
