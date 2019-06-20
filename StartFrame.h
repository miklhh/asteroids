/*
 * The start frame is the first frame to be launched in the asteroids game. It 
 * provides a menu for selection of game mode, and provides the user with an 
 * exit button to terminate the game.
 */

#ifndef _TEST_H
#define _TEST_H

#include "Frame.h"
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StartFrame : public Frame
{
public:

  // Constructor with size of window as parameters
  StartFrame(int const& xSize, int const& ySize);

  // No copying of startframe allowed.
  StartFrame(const StartFrame &other) = delete;
  StartFrame &operator=(const StartFrame &other) = delete;


  // This function handels all the drawing to the window
  void render(sf::RenderWindow &window) const override;

  // This function updates objects that move.
  // If it is time to change Frame, this function returns a pointer to another
  // Frame, otherwise it returns a nullpointer.
  Frame *iterate() override;

  // This function handles Events, more specifically keyboard buttons being
  // pressed
  void handleEvent(const sf::Event &event) override;
private:

  // To make the code more modular render calls these 3 functions handle the
  // rendering for the three diffrent states of the StartFrame..
  void renderStart(sf::RenderWindow &window) const;
  void renderSingle(sf::RenderWindow &window) const;
  void renderMulti(sf::RenderWindow &window) const;

  // These are help functions that update the int position. They get called upon
  // by the handleEvent function. They handle the case when the user presses
  // up or down arrow on the keyboard.
  void increasePosition();
  void decreasePosition();

  // This function gets called upon by the handleEvent function and handles
  // the case when the Enter key is pressed. This function updates int state,
  // nextFrame and can close the window.
  void selectPosition();

  // To make the code more modullar selectPosition calls upon one of three
  // functions depending on the value of int state
  void titleSelectPosition();
  void singleSelectPosition();
  void multiSelectPosition();

  // This functions loads all the sprites and textures. It also change the
  // settings one these sprites. LoadSprites calls upon functions that loads
  // specific sprites seperatly, one in this case............
  void loadSprites();

  // loads the background sprite and change the settings of it.
  void loadBackground();

  // loads all the Text objects
  void loadText();

  // All the Text objects gets loaded seperatly. They get font position, size,
  // etc
  void loadTitle();
  void loadSingle();
  void loadMulti();
  void loadQuit();
  void loadStart();
  void loadBack();

  // loads shapes. In this implementation one rectangle.
  void loadShapes(float const & width, float const & height,
                  sf::Vector2f const pos);

  // Member fields

  // Position of the "selectbar" where 0 is the Text highest up on the screen.
  int position{};

  // Start, singleplayer, multiplayer or quit? [0, 1, 2, 3]
  int state{};

  //Dimensions of the Window at start.
  const int WIDTH {};
  const int HEIGHT {};

  // variables for making the background spinn.
  float backgroundAngle {};
  float backgroundAngleMomentum {0.01};

  // Images and textures.
  sf::Sprite backgroundSprite{};
  sf::Sprite backgroundSprite2{};
  sf::Texture backgroundTexture{};
  sf::Texture backgroundTexture2{};

  //text and fonts
  sf::Font font{};
  sf::Text title{};
  sf::Text singlePlayer{};
  sf::Text multiPlayer{};
  sf::Text quit{};
  sf::Text start{};
  sf::Text back{};

  // rectangle and its color
  sf::RectangleShape selected{};
  sf::Color color {0, 255, 175, 130};

  //music
  sf::Music music{};

  //Frame pointer.
  Frame *nextFrame{nullptr};

  // Wait timer.
  sf::Clock waitTimer{};
};

#endif
