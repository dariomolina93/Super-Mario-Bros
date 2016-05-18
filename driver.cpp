#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include"Player.h"
#include"Coin.h"
#include "enemy.h"
#include<vector>
#include<iostream>
#include<cstdlib>
#include"Tile.h"
#include<string>
#include<fstream>
using namespace std;

void mainMenu(sf::RenderWindow& w, sf::Event& e, sf::Sprite& t);
//void restartGame();

int main()
{

	ifstream input;

	input.open("Text/tilePlacement.txt");

	if (input.fail())
		cout << "error loading file\n";
	vector<Tile>::iterator tileIterator;
	vector<Tile> tileVector;
	sf::SoundBuffer clear;
	sf::SoundBuffer coin1;
	sf::SoundBuffer jump1;
	sf::SoundBuffer flag2;
	sf::SoundBuffer dead;
	sf::Sound coinSound;
	sf::Sound jumpSound;
	sf::Sound downFlag;
	sf::Sound stageClear;
	sf::Sound deadMario;
	sf::Music music;
	sf::Vector2f screenDimensions(800, 450);// vector to store our screen dimensions
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "View Port");
	sf::Texture texture;// texture in order
	sf::Texture title;
	sf::Texture flag;
	sf::Sprite Flag1;
	sf::Sprite title1;
	sf::Sprite sprite;
	sf::View view;// we need to be able to move our screen along our game
	sf::Event event;// check for event
					//sf::Mouse mouse;
	Player Mario;// instance of our player
	Tile tiles;

	//Goomba Part
	int i = 0;//keeps track of how many steps the goomba has taken
	int counterDead = 12; //used to keep trak of how many dead so for loop do not run more than they need to
	Enemy e[5];// create an array for all of the enemy
	e[0].setPosition(500 , 395);
	e[1].setPosition(700 , 395);
	e[2].setPosition(800 , 395);
	e[3].setPosition(2550 , 395);
	e[4].setPosition(2950 , 395);
	/*e[5].setPosition(7632, 375);
	e[6].setPosition(1098 * 2, 375);
	e[7].setPosition(1574 * 2, 375);
	e[8].setPosition(1907 * 2, 375);
	e[9].setPosition(2096 * 2, 375);
	e[10].setPosition(2579 * 2, 375);
	e[11].setPosition(2700 * 2, 375);*/

	sf::Clock delta;
	double deltaTime;
	bool whileJump = false;


	Coin c[12];// create an array of all of our coins

			   //**********************

	sf::RectangleShape tempGridSpriteOutline;
	tempGridSpriteOutline.setOutlineColor(sf::Color::White);
	tempGridSpriteOutline.setOutlineThickness(0.5);
	tempGridSpriteOutline.setFillColor(sf::Color::Transparent);
	tempGridSpriteOutline.setSize(sf::Vector2f(16 * 2, 16 * 2));

	sf::Vector2i tempGridSize(378, 14);


	c[0].setPosition(257 * 2, 130 * 2);
	c[1].setPosition(354 * 2, 67 * 2);
	c[2].setPosition(339 * 2, 130 * 2);
	c[3].setPosition(370 * 2, 130 * 2);
	c[4].setPosition(1250 * 2, 130 * 2);
	c[5].setPosition(1505 * 2, 67 * 2);
	c[6].setPosition(1697 * 2, 130 * 2);
	c[7].setPosition(1746 * 2, 130 * 2);
	c[8].setPosition(1793 * 2, 130 * 2);
	c[9].setPosition(2066 * 2, 67 * 2);
	c[10].setPosition(2080 * 2, 67 * 2);
	c[11].setPosition(2722 * 2, 130 * 2);
	int counter25 = 0;

	if (!coin1.loadFromFile("images/coinSound.wav") || !jump1.loadFromFile("images/jumpSound.wav") || !dead.loadFromFile("images/MarioDies.wav") || !flag2.loadFromFile("images/downFlagpole.wav") || !clear.loadFromFile("images/stageClear.wav"))
		cout << "Could not load sound effects\n";

	if (!music.openFromFile("images/marioSong.ogg"))// import mario theme song
		cout << "Could not load file\n";

	if (!texture.loadFromFile("images/marioUniverse.png") || !title.loadFromFile("images/marioTitle6.png") || !flag.loadFromFile("images/marioFlag6.png"))// import our background and our main mario page
		cout << "Could not load file\n";

	coinSound.setBuffer(coin1);
	jumpSound.setBuffer(jump1);
	downFlag.setBuffer(flag2);
	stageClear.setBuffer(clear);
	deadMario.setBuffer(dead);
	int counter = 0;//this counter will take input from our text file

	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	title1.setTexture(title);
	title1.setScale(.6, .6);

	Flag1.setTexture(flag);
	Flag1.setScale(.5, .5);
	Flag1.setPosition(3157 * 2, 41 * 2);

	bool collides = true;//checking to see if Mario collides with a block


	sf::Vector2f position(0, 0);// this vector will keep track of the position of our screen

	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));// we are assigning our screen start at 0,0, with the same dimensions as our game screen

	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));// position our view at 0, 0, and 1 and 1 represent that we want to view the full screen vertically and horizontally.

	window.setVerticalSyncEnabled(true);


	//mainMenu(window, event, title1);

	cout << "After main screen\n";
	int counter2 = 0;//a counter that acts as our index to check our vector[counter2]

					 //*********************************************************
					 //This scope of code will read in from the file, and at the location x, y if there is a 1 we will place a block, else we will continue
	for (int i = 0; i < tempGridSize.x; i++)
	{
		for (int j = 0; j < tempGridSize.y; j++)
		{
			tempGridSpriteOutline.setPosition(i * tempGridSpriteOutline.getSize().x, j *  tempGridSpriteOutline.getSize().y);

			input >> counter;
			if (counter == 1)
			{
				tiles.setMainRectPosition(i * 32, j * 32);//we are multiplying by 32 because the size of the square is 16 by 16, but since we are scaling it by two we multiply 16 * 2
				tileVector.push_back(tiles);// for every tile that has been placed in our
			}

			else
				continue;


			//window.draw(tempGridSpriteOutline);
			cout << "Inside nester loop\n";

		}

	}

	//*********************************************************

	mainMenu(window, event, title1);// this is for our intro screen

	int score = 0;
	sf::Font MarioFont;
	if (!MarioFont.loadFromFile("images/emulogic.ttf"));
	{
		cout << "Cannot load font\n";
	}
	sf::String sentence1 = "World";
	sf::String sentence2 = "Grit";
	sf::String sentence = "Dario";
	sf::String sentence3 = "Ali";
	sf::String sentence4 = "Nicole";
	sf::Text text4(sentence1, MarioFont, 20);
	sf::Text text5(sentence2, MarioFont, 20);
	sf::Text text(sentence, MarioFont, 20);
	sf::Text text6(sentence3, MarioFont, 20);
	sf::Text text7(sentence4, MarioFont, 20);
	text4.setPosition(360, 0);
	text5.setPosition(360, 29);
	text6.setPosition(560, 0);
	text7.setPosition(560, 29);
	string n = "x0";
	sf::Text text3;
	sf::Text text2;
	text2.setCharacterSize(20);
	text3.setCharacterSize(20);
	text2.setFont(MarioFont);
	text3.setFont(MarioFont);
	text2.setPosition(61, 29);
	text3.setPosition(200, 29);
	text3.setColor(sf::Color::Yellow);

	music.play();// start game music as soon as game starts
	while (window.isOpen())// game loop
	{
		if (Mario.getCoinCount() > 9) {
			n = "x";
		}
		string newScore = to_string(score);
		string coinCount = to_string(Mario.getCoinCount());
		sf::String cCount = n + coinCount;
		sf::String totalScore = newScore;
		text2.setString(totalScore);
		text3.setString(cCount);
		window.draw(sprite);

		//************************************************************************

		/*counter2 = 0;// restart our index to zero
					 // this loop is to draw our tiles of color green into our  game
		for (tileIterator = tileVector.begin(); tileIterator != tileVector.end(); tileIterator++)
		{
			window.draw(tileVector[counter2].mainRect);
			counter2++;
		}*/

		//************************************************************************
		counter2 = 0;



		collides = false;// we have this boolean to see if Mario is colliding with a tile
		for (tileIterator = tileVector.begin(); tileIterator != tileVector.end(); tileIterator++)//go through all the tiles in our vector and check if there is collision
		{


			if (Mario.checkCollisionTile(tileVector[counter2]))// check to see if Mario is colliding with a tiles(block) if its true then
			{
				// cout << "Setting whileJump to false in collisition detections\n";
				// whileJump = false;
				collides = true;// set the collision to true so mario can jump when he intersects with a tile
				Mario.speedValue = 0;// speedValue to zero because Mario  is stanging on the block  so there is no speed Value
			}

			counter2++;// increment index so it goes through each of the tiles set up in the game

		}

		//************************************************************************

		counter2 = 0;//this for loop is to check if mario is not colliding with any tile(block) then set whileJump to true( this will set gravity to true and bring Mario down)
		for (tileIterator = tileVector.begin(); tileIterator != tileVector.end(); tileIterator++)
		{


			if (!Mario.checkCollisionTile(tileVector[counter2]))
			{
				whileJump = true;
			}

			counter2++;

			//************************************************************************
		}

		if (Mario.speedValue  <= 15)// when Mario jumps, and reaches this value in speed value, set while jump to true;
			whileJump = true;

		else
			whileJump = false;


		deltaTime = delta.restart().asSeconds();
		if (whileJump)// if mario is in the air
		{


			if (Mario.speedValue <= 0 && Mario.speedValue > -.03 && collides)// we check speed value to be within this range since speed value depends on the delta time, so when it hits the ground no matter how high Mario goes the speedvalue will always be between that range
																			  //in if statement above, we need to check that collide is true as well so mario is colliding with a block and that he can jump
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//if mario is on the ground
				{
					//Mario.changeJump();
					jumpSound.play();
					Mario.speedValue = Mario.getJumpValue() / Mario.getMarioMass();//mario is going to go up this amount of pixels
					whileJump = true;// set whileJump to true knowing its in the air
				}
			}
			Mario.jump(deltaTime);// start decreasing to bring mario back to ground
								  //cout << "Mario Jumped" << endl;


		}

		while (window.pollEvent(event))// check for events
		{
			if (event.type == sf::Event::Closed)// if you would like to close the window
				window.close();

		}

		//*********************************** Mario ***********************************
		if (Mario.getPositionX() >= 3167 * 2)// When Mario reaches the flag
		{
			music.stop();

			downFlag.play();

			while (Flag1.getPosition().y < 182 * 2)// if the position of the flag is less than the position of the floor
			{

				cout << "Inside while loop that brings the flag down\n";
				Flag1.move(0, 2);// move the flag down two pixels at a time

				if (Mario.getPositionY() < 168 * 2)// if the position of Mario is less than the position of the floor
					Mario.moveDown();// bring mario down


				window.draw(sprite);// display the background
				window.setView(view);// display the view
				Mario.draw(window);
				window.draw(Flag1);
				window.display();
				window.clear();

			}
			stageClear.play();// play the when he clears the stage
			while (Mario.getPositionX() == 3173 * 2 || Mario.getPositionX() <= 3275 * 2)// this loop will run as long as mario has reaches the flag, and the position of mario is less than the position of the entrance of the castle
			{
				cout << "Inside loop where mario moves by itselfs\n";


				//cout << "Here is the flag\n";
				Mario.moveRight();   
				counter25++;

				if (counter25 == 10)
					Mario.setPosition(Mario.getPositionX(), Mario.getPositionY() + 20);
								

				while (Mario.getPositionX() >= 3270 * 2)//once the position of mario is equal to the entrance of the castle then we will draw our terrain and everything except for Mario to simulate that he has gone inside the castle
				{
					while (window.pollEvent(event))// check for events
					{
						if (event.type == sf::Event::Closed)// if you would like to close the window
							window.close();

					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						return 0;

					cout << "Inside loop where Mario disapperas into castle\n";
					window.draw(sprite);// display the background
					window.setView(view);// display the view
					window.display();
					window.clear();


				}

				window.setView(view);// display the view
				window.draw(sprite);//the background
				Mario.draw(window);//rect
				window.display();
				window.clear();

			}

		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))// if right arrow is pressed
		{
			Mario.moveRight();//move mario to the right


			if (view.getCenter().x + screenDimensions.x / 2 >= (texture.getSize().x - 5) * 2)// this is to prevent the screen from moving once mario is at the end of our map
				cout << "Its at end of scree\n";

			else if (Mario.getPositionX() + 55 > view.getCenter().x)// if mario passes the center of the screen
			{
				text.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2), 0);
				text2.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2), 29);
				text3.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 200, 29);
				text4.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 360, 0);
				text5.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 360, 29);
				text6.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 560, 0);
				text7.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 560, 29);
				position.x = Mario.getPositionX() + 46 - (screenDimensions.x / 2);// we are goin to assign the position.x of our view to the difference of position of Mario and  the screen dimension;

				view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x, screenDimensions.y));// we are going to reset our view and since position.x is the only one that changed, it will allow our screen to move in the game
			}

			else//if the position of mario is less than the center of view, assign position.x to zero, that way Mario can go back and the view will not move.
			{
				position.x = 0;
			}


		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (Mario.getPositionX() <= (view.getCenter().x - screenDimensions.x / 2))// if the position of mario is less than left side of the screen; this is to prevent for the player to go back in the game past the screen
			{
				Mario.moveRight();// we are going to add by a speed of 2
				Mario.moveLeft();// we are going to subrtract by 2 which will allow for mario to stay in the same spot because (2 -2 ==
			}// and as soon as the if statement excutes

			Mario.moveLeft();// we are going to subrtract by 2 which will allow for mario to stay in the same spot because (2 -2 ==
		}

		else {
			Mario.idle();
		}



		for (int i = 0; i < 12; i++) {
			if (Mario.checkIfCoinIsTouched(c[i]) && c[i].getIsVisible()) {
				Mario.addCoinCount();
				coinSound.play();
				cout << "Number of Coins: " << Mario.getCoinCount() << endl;
				score += 200;
				c[i].setIsVisible(false);
			}
		}

		Mario.update();//this function is to check the coordinates

	//	cout << "Mario Speed Value: " << Mario.speedValue << endl;

	//***************************************** End Of Mario ***********************************************

	//******************************************** Goomba **************************************************
		for (int j = 0; j < 12; j++) {
			if ((e[j].isIntersectingX(Mario.getPositionX())) && (e[j].isIntersectingY(Mario.getPositionY()))) {
				//for Goomba to die, Mario has to hit it on top. y would always equal to zero while can be any value.
				//otherwise, Mario dies.
				e[j].setDead(window);
				e[j].setIsDead(true);
				for (int i = 0; i < 1; i++);//shows the dead goomba for a few seconds then it will disappear
				e[j].setIsVisible(false);
				score += 100;
			}
		}

		//****************************** Goomba 1 ************************************
		if ((e[0].getPositionX() - 478 < 10 && e[0].getPositionX() - 478>0))//Set the Left coundary
			e[0].moveRight();
		else if (611 - e[0].getPositionX() <10 && 611 - e[0].getPositionX() >0)//Sets the right boundary
			e[0].moveLeft();
		else {
			if (e[0].getDirection() == 0)//keeps the goomba moving in the direction it was until it meets one fo the conditions above.
				e[0].moveLeft();
			else
				e[0].moveRight();
		}

		//****************************** Goomba 2 ************************************
		if ((e[1].getPositionX() - 638 <10 && e[1].getPositionX() - 638>0))
			e[1].moveRight();
		else if (715 - e[1].getPositionX() <10 && 715- e[1].getPositionX() >0)
			e[1].moveLeft();
		else {
			if (e[1].getDirection() == 0)
				e[1].moveLeft();
			else
				e[1].moveRight();
		}

		//****************************** Goomba 3 ************************************
		if ((e[2].getPositionX() - 1059 <10 && e[2].getPositionX() - 1059>0))
			e[2].moveRight();
		else if (1400 - e[2].getPositionX() <20 && 1400 - e[2].getPositionX() >0)
			e[2].moveLeft();
		else {
			if (e[2].getDirection() == 0)
				e[2].moveLeft();
			else
				e[2].moveRight();
		}

		//****************************** Goomba 4 ************************************
		if ((e[3].getPositionX() - 2305 <10 && e[3].getPositionX() - 2305>0))
			e[3].moveRight();
		else if (2638 - e[3].getPositionX() <10 && 2338 - e[3].getPositionX() >0)
			e[3].moveLeft();
		else {
			if (e[3].getDirection() == 0)
				e[3].moveLeft();
			else
				e[3].moveRight();
		}

		//****************************** Goomba 5 ************************************
		if ((e[4].getPositionX() - 2867 <10 && e[4].getPositionX() - 2867>0))
			e[4].moveRight();
		else if (3059 - e[4].getPositionX() <10 && 3059 - e[4].getPositionX() >0)
			e[4].moveLeft();
		else {
			if (e[4].getDirection() == 0)
				e[4].moveLeft();
			else
				e[4].moveRight();
		}


		//***************************************** End Of Goomba ***********************************************





		// display our view and all of our things
		window.setView(view);
		//window.draw(sprite);
		Mario.draw(window);
		for (int i = 0; i < 12; i++)
			c[i].draw(window);
		for (int i = 0; i < 5; i++) {
			if (e[i].getIsVisible() == true)
				e[i].draw(window);
		}
		//window.draw(Mario.getMarioRect());
		Mario.draw(window);
		window.draw(text6);
		window.draw(text7);
		window.draw(text5);
		window.draw(text4);
		window.draw(text2);
		window.draw(text);
		window.draw(text3);
		/*window.draw(Mario.TopRect);
		window.draw(Mario.BottomRect);
		window.draw(Mario.LeftRect);
		window.draw(Mario.RightRect);*/
		window.draw(Flag1);
		window.display();
		window.clear();
	}//end of game loop

//	deltaTime = delta.restart().asSeconds();
	return 0;
}



void mainMenu(sf::RenderWindow& w, sf::Event& e, sf::Sprite& t)
{
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)))// intro screen
	{

		while (w.pollEvent(e))// check for events
		{
			if (e.type == sf::Event::Closed)// if you would like to close the window
				w.close();

		}
		w.draw(t);
		w.display();
		w.clear();

	}

}

