//===============================================
// App.cpp
//
//Note: You are programming for an iPhone (UNIX variant), 
//Windows-specific header files will not compile. 
//You can include standard C libraries such as <stdio.h>.
//For more information: http://dragonfiresdk.com/faq.htm
//===============================================

/******************************************
 * Final Project, Breakout
 * This is a simple version of the classic
 * game breakout for the iPhone
 *
 * By Dylan Wilson
 * April 11, 2010
 *****************************************/

#include "DragonFireSDK.h"
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#include "Rectangle.h"
#include "Brick.h"

int BallImage;
int BallView;
Rectangle BallRec;

//int BrickImage;
//int BrickView;
//Rectangle BrickRec;

vector<Brick*> BrickList;

int BounceY = 5; //These are the directions the ball will be moving in.
int BounceX = -5;

int KickSound;
int SnareSound;

bool Landscape; //This is used to tell my code what view mode it's in and how it should react. Although it works it is not tested in this program.

int Area[15][10];

int OnClick(int id, int event, int x, int y);     //event: 1=down, 2=move, 3=up

void MakeLevel(); //Makes the brick level.
void RemakeList(); //Remakes the brick level.

int PaddleImage; //Info on the paddle
int PaddleView;
Rectangle PaddleRec;

int StartImage; //Info on the start screen
int StartView;
bool StartBool;

int LoseImage; //Info on the lose screen
int LoseView;
bool LoseBool;

int WinImage; //Info on the win screen
int WinView;
bool WinBool;

bool GameOn; //If the game is on
bool GameStart; //If the game has started

int PauseTheGame(int id); //Used to pause
bool Paused;

void AppMain()
{  
	Paused = false;
	Landscape = false;
	GameOn = false;
	GameStart = false;
	KickSound=SoundAdd("Sounds/Kick.wav");	 // load a sound file
	SnareSound=SoundAdd("Sounds/Snare.wav");  // load a sound file

	ViewAdd("Images/BackgroundTest.png",0,0,OnClick,0);

	

	PaddleImage = ImageAdd("Images/Paddle.png"); //Makes the paddle
	PaddleView = ViewAdd(PaddleImage, 0, 320-15);
	PaddleRec.SetHeight(12.0f);
	PaddleRec.SetWidth(64.0f);
	PaddleRec.UpdateRec(ViewGetx(PaddleView),ViewGety(PaddleView));
	
	BallImage = ImageAdd("Images/OddBall.png"); //Makes the ball
	BallView = ViewAdd(BallImage, PaddleRec.GetX()+PaddleRec.GetWidth()/2-13, 320-15-26);
	BallRec.SetHeight(26.0f);
	BallRec.SetWidth(26.0f);
	BallRec.UpdateRec(ViewGetx(BallView),ViewGety(BallView));

	

	Landscape = true; //This is set so my program can switch between landscape and not landscape BEFORE THE PROGRAM HAS STARTED. If done partway through it will not work and cause glitches
	LandscapeMode();

	MakeLevel(); //sets up the level.

	StartImage = ImageAdd("Images/Instruct2.png");//Makes the instructions
	StartView = ViewAdd(StartImage,0,0);
	StartBool = true;

	LoseImage = ImageAdd("Images/Lose2.png"); //Makes the lose screen
	LoseView = ViewAdd(LoseImage,0,0);
	LoseBool = false;
	ViewSetVisible(LoseView,false);

	WinImage = ImageAdd("Images/Win2.png"); //Makes the win screen
	WinView = ViewAdd(WinImage,0,0);
	WinBool = false;
	ViewSetVisible(WinView,false);

	PushButtonAdd("Images/Pausebtn",0,0,PauseTheGame,0); //Makes the pause button.
}
//====================================================

void OnTimer()
{
  int BallX, BallY;
  bool Won = true; //This is used to test if the game is won or not.
 
	if(GameStart && GameOn && !Paused) //If the game is a go!
	{
	  // Update the ball's next X and Y values.
	   BallX = ViewGetx(BallView) + BounceX;
	   BallY = ViewGety(BallView) + BounceY;

	  // Don't let the ball go off the screen:
	   if ((BallX >= 320-BallRec.GetWidth() && !Landscape))
	  {
		   BallX = 320-BallRec.GetWidth();
		   BounceX = -5;
	  }
	   else if(Landscape && BallX >=480-BallRec.GetWidth())
	  {
		  BallX = 480-BallRec.GetWidth();
		  BounceX = -5;
	  }

	  if (BallX <= 0)
	  {
		   BallX = 0;
		   BounceX = 5;
	  }

	  if (BallY >= 480 - BallRec.GetHeight() && !Landscape)
	  {
		  //BallY = 480 - BallRec.GetHeight();
		  //BounceY = -5;
		  LoseBool = true;
		  GameOn = false;
		  ViewSetVisible(LoseView,true);
	  }
	  else if(Landscape && BallY >= 320 - BallRec.GetWidth())
	  {
		  //BallY = 320 - BallRec.GetHeight();
		  //BounceY = -5;

		  LoseBool = true;
		  GameOn = false;
		  ViewSetVisible(LoseView,true);
	  }

	  if (BallY <= 0)
	  {
		   BallY = 0;
		   BounceY = 5;
	  }

	  
	  // Update the ball's position:
	   ViewSetxy(BallView, BallX, BallY);
	   BallRec.UpdateRec(ViewGetx(BallView),ViewGety(BallView));

	   if(PaddleRec.Collision(BallRec) && PaddleRec.CircleCollision(BallRec)) //Tests for collision with the paddle. First uses square collision cause it's fast, than circle for to be more exact.
	   {
		    Won = false;
			int * DirectionP =  PaddleRec.SideCollision(BallRec); //This creates an array with the direction that the second rectangle is compared to the first.

			int Direction[2];
			Direction[0]= DirectionP[0];
			Direction[1] = DirectionP[1];

			if(Direction[0] == 0 && Direction[1] == 0)
			{
				BounceX *=-1;
				BounceY *=-1;
			}

			if(Direction[0] == 1)
			{
				BounceX = 5;
			}
			else if(Direction[0] == -1)
			{
				BounceX = -5;
			}

			if(Direction[1] == 1)
			{
				BounceY = 5;
			}
			else if(Direction[1] == -1)
			{
				BounceY = -5;
			}
			SoundPlay(KickSound);  // play a loaded sound
	   }
	   else
	   {
		   
		   for(int i = BrickList.size()-1; i>= 0; i--) //Used to test for collision
		   {
			   if(!BrickList[i]->Dead) //So long as the brick isn't dead (Bricks aren't removed, but just MOVED because I reuse the views instead of remake)
			   {
				   Won = false; //If there is a break and it isn't dead it means you haven't won.
				   if(BrickList[i]->BrickRec.Collision(BallRec) && BrickList[i]->BrickRec.CircleCollision(BallRec)) //Tests for a square collision for speed than a circle one for better results.
					{
						int * DirectionP =  BrickList[i]->BrickRec.SideCollision(BallRec); //returns an arrayof where the second rectangle is compared to the first.

						int OldBounceX = BounceX; //These are used to prevent a rare glitch in which the ball doesn't hit the break but does break it.
						int OldBounceY = BounceY;

						int Direction[2];
						Direction[0]= DirectionP[0];
						Direction[1] = DirectionP[1];

						if(Direction[0] != 0 && Direction[1] != 0) //This is used to make lines of bricks react like lines instead of individual bricks.
						{
							int XLoc = BrickList[i]->BrickRec.GetX()/BrickList[i]->BrickRec.GetWidth();
							int YLoc = BrickList[i]->BrickRec.GetY()/BrickList[i]->BrickRec.GetHeight();

							if(!Landscape)
							{
								if(Area[YLoc][XLoc + Direction[0]] == 1)
								{
									BounceY *=-1;
								}
								else if(Area[YLoc + Direction[1]][XLoc] == 1)
								{
									BounceX *=-1;
								}
							}
							else
							{
								if(Area[XLoc + Direction[0]][YLoc] == 1 )
								{
									Direction[0] = 0;
								}
								else if(Area[XLoc][YLoc + Direction[1]] == 1)
								{
									Direction[1] = 0;
								}
							}
						}

						if(Direction[0] == 1 )
						{
							BounceX = 5;
						}
						else if(Direction[0] == -1 )
						{
							BounceX = -5;
						}

						if(Direction[1] == 1 )
						{
							BounceY = 5;
						}
						else if(Direction[1] == -1 )
						{
							BounceY = -5;
						}

						if(!(Direction[0] == 0 && Direction[1] == 0) && !(OldBounceX ==BounceX && OldBounceY == BounceY)) //If there was a collision but the ball doesn't bounce it was a rare glitch, so ignore it.
						{
							SoundPlay(KickSound);  // play a loaded sound

							BrickList[i]->BrickRec.UpdateRec(5000,0); //This moves the brick so they can be reused.
							ViewSetxy(BrickList[i]->BrickView,5000,0);

							BrickList[i]->Dead = true;
						}
				   }
			   }
		   }
	   }

	   if(Won) //If we got through all that and won is still true we must have won.
	   {
			WinBool = true;
			GameOn = false;
			ViewSetVisible(WinView,true);
	   }
	}
}
int OnClick(int id, int event, int x, int y)     //event: 1=down, 2=move, 3=up
{
	if(!Paused && GameOn) //If the game is on and not paused.
	{
	   if (event == 2 || event == 1)
	   {

		   //ViewSetxy(BallView, x-BallRec.GetWidth(), y-BallRec.GetHeight()); //UNCOMMENT THIS LINE TO MAKE THE BALL MOVE TO THE MOUSE LOCATION FOR DEBUGGING.

		   if(GameStart) //If the game has started
		   {
				ViewSetxy(PaddleView,x-PaddleRec.GetWidth()/2, ViewGety(PaddleView));//,y-BallRec.GetHeight()/2);
				PaddleRec.SetX(x-PaddleRec.GetWidth()/2);
		   }
		   else //Else it means the ball is moving too.
		   {
				ViewSetxy(PaddleView,x-PaddleRec.GetWidth()/2, ViewGety(PaddleView));//,y-BallRec.GetHeight()/2);
				PaddleRec.SetX(x-PaddleRec.GetWidth()/2);
				ViewSetxy(BallView, PaddleRec.GetX() + PaddleRec.GetWidth()/2 - BallRec.GetWidth()/2 , ViewGety(BallView));
				BallRec.SetX(PaddleRec.GetX() + PaddleRec.GetWidth()/2 - BallRec.GetWidth()/2);
		   }
	   }
	   else if (event == 3)
	   {   
		   if(BallRec.Collision(x,y)) //Tests a point collision on the ball.
		  {
			GameStart = true;
		  }
	   }
	}
	if(StartBool && event == 1) //These are used to change the game state depending on what is going on.
	{
		StartBool = false;
		ViewSetVisible(StartView,false);
		RemakeList();
		GameOn = true;
	}
	else if(LoseBool && event == 1)
	{
		LoseBool = false;
		ViewSetVisible(LoseView,false);
		RemakeList();
		GameOn = true;
	}
	else if(WinBool && event == 1)
	{
		WinBool = false;
		ViewSetVisible(WinView,false);
		RemakeList();
		GameOn = true;
	}
  return 0;
}

void MakeLevel() //This is used to make my level nice and easy.
{
	int Level [15][10]={1,0,1,1,1,0,0,0,0,0, //This is used to easily modify my level as I see fit.
						1,1,0,0,1,0,0,0,0,0,
						1,0,1,1,1,0,0,0,0,0,
						1,1,0,0,0,0,0,0,0,0,
						1,0,1,1,1,0,0,0,0,0,
						1,1,0,0,1,0,0,0,0,0,
						1,0,1,1,1,0,0,0,0,0,
						1,1,0,0,0,0,0,0,0,0,
						1,0,1,1,1,0,0,0,0,0,
						1,1,0,0,1,0,0,0,0,0, 
						1,0,1,1,1,0,0,0,0,0,
						1,1,0,0,0,0,0,0,0,0,
						1,0,1,1,1,0,0,0,0,0,
						1,1,0,0,1,0,0,0,0,0,
						1,0,1,1,1,0,0,0,0,0};

	for(int i = 0; i<10; i++)
	{
		for(int k = 0; k<15; k++)
		{
			Area[k][i] = Level[k][i];
			if(Level[k][i] == 1)
			{
				if(!Landscape) //Deals with landscape
				{
					BrickList.push_back( new Brick(i*32,k*32,32,32)); //Deals with placing the brick
				}
				else
				{
					BrickList.push_back( new Brick(k*32,i*32,32,32)); //Deals with placing the brick
				}
			}
		}
	}
	
}
void RemakeList() //This is used to remake a level and restart the game.
{
	int counter = 0;
	for(int i = 0; i<10; i++)
	{
		for(int k = 0; k<15; k++)
		{
			if(Area[k][i] == 1)
			{
				if(!Landscape) //Deals with landscape or not
				{
					ViewSetxy(BrickList[counter]->BrickView,i*32,k*32);
					BrickList[counter]->Dead = false;
					BrickList[counter]->BrickRec.UpdateRec(ViewGetx(BrickList[counter]->BrickView),ViewGety(BrickList[counter]->BrickView));
					counter++;
				}
				else
				{
					ViewSetxy(BrickList[counter]->BrickView,k*32,i*32);
					BrickList[counter]->Dead = false;
					BrickList[counter]->BrickRec.UpdateRec(ViewGetx(BrickList[counter]->BrickView),ViewGety(BrickList[counter]->BrickView));
					counter++;
				}
			}
		}

		GameStart = false;
		ViewSetxy(PaddleView,0, ViewGety(PaddleView));//,y-BallRec.GetHeight()/2);
		PaddleRec.SetX(0);
		ViewSetxy(BallView, PaddleRec.GetX() + PaddleRec.GetWidth()/2 - BallRec.GetWidth()/2 , 320-15-26);
		BallRec.SetX(PaddleRec.GetX() + PaddleRec.GetWidth()/2 - BallRec.GetWidth()/2);
		BallRec.SetY(320-15-26);
		BounceX = -5;
		BounceY = 5;
	}
}
int PauseTheGame(int id)
{
	if(GameOn) //If the game is on
	{
		if(Paused) //If already paused
		{
			Paused = false;
		}
		else
		{
			Paused = true;
		}
	}
	return 0;
}