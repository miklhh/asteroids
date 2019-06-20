#include "StartFrame.h"
#include "SingleplayerFrame.h"
#include "MultiplayerFrame.h"

StartFrame::StartFrame(int const& xSize, int const& ySize)
  : WIDTH(xSize), HEIGHT(ySize)
{
  loadSprites();
  loadText();
  selected.setFillColor(color);
  loadShapes(singlePlayer.getLocalBounds().width,
             singlePlayer.getLocalBounds().height,
             singlePlayer.getPosition());
}

void StartFrame::loadSprites()
{
  loadBackground();
}

void StartFrame::loadBackground()
{
  if (!backgroundTexture.loadFromFile("Images/StartImages/background3.png"))
  {
    // TODO: Throw exception
  }
  if (!backgroundTexture2.loadFromFile("Images/StartImages/background4.png"))
  {
    // TODO: Throw exception
  }

  backgroundSprite.setTexture(backgroundTexture),
  backgroundSprite.setTextureRect(sf::IntRect(0, 0, 400, 400));
  backgroundSprite.setOrigin(200, 200);
  backgroundSprite.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/2));
  backgroundSprite.setScale(sf::Vector2f(6, 6));
  backgroundSprite2.setTexture(backgroundTexture2),
  backgroundSprite2.setTextureRect(sf::IntRect(0, 0, 400, 400));
  backgroundSprite2.setOrigin(200, 200);
  backgroundSprite2.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/2));
  backgroundSprite2.setScale(sf::Vector2f(6, 6));
}

void StartFrame::loadText()
{
  //if (!font.loadFromFile("Images/StartImages/Consolas.ttf"))
  if (!font.loadFromFile("Fonts/8bitfont.ttf"))
  {
    // TODO: Throw exception
  }

  loadTitle();
  loadSingle();
  loadMulti();
  loadQuit();
  loadStart();
  loadBack();
}

void StartFrame::loadTitle()
{
  title.setFont(font);
  title.setFillColor(sf::Color::White);
  title.setString("4STR01D-76");
  title.setCharacterSize(75); // In pixels, not points.
  sf::FloatRect r = title.getLocalBounds();
  title.setPosition(WIDTH/2 - r.width/2, HEIGHT/4 );
}

void StartFrame::loadSingle()
{
  singlePlayer.setFont(font);
  singlePlayer.setFillColor(sf::Color::White);
  singlePlayer.setString("SINGLEPLAYER");
  singlePlayer.setCharacterSize(40); // In pixels, not points.
  sf::FloatRect r = singlePlayer.getLocalBounds();
  singlePlayer.setPosition(WIDTH/2 - r.width/2, HEIGHT/2);
}

void StartFrame::loadMulti()
{
  multiPlayer.setFont(font);
  multiPlayer.setFillColor(sf::Color::White);
  multiPlayer.setString("MULTIPLAYER");
  multiPlayer.setCharacterSize(40); // In pixels, not points.
  sf::FloatRect r = multiPlayer.getLocalBounds();
  multiPlayer.setPosition(WIDTH/2 - r.width/2 ,HEIGHT/2 + (2 * r.height) );
}

void StartFrame::loadQuit()
{
  quit.setFont(font);
  quit.setFillColor(sf::Color::White);
  quit.setString("QUIT");
  quit.setCharacterSize(40);
  sf::FloatRect r1 = quit.getLocalBounds();
  sf::FloatRect r2 = multiPlayer.getLocalBounds(); // Uses multi since quit is larger than the others.
  quit.setPosition(WIDTH/2 - r1.width/2, HEIGHT/2 + (4 * r2.height));
}

void StartFrame::loadStart()
{
  start.setFont(font);
  start.setFillColor(sf::Color::White);
  start.setString("START");
  start.setCharacterSize(40);
  sf::FloatRect r = start.getLocalBounds();
  start.setPosition(WIDTH/2 - r.width/2, HEIGHT/2);
}

void StartFrame::loadBack()
{
  back.setFont(font);
  back.setFillColor(sf::Color::White);
  back.setString("BACK");
  back.setCharacterSize(40);
  sf::FloatRect r = back.getLocalBounds();
  back.setPosition(WIDTH/2 - r.width/2, HEIGHT/2 + (2 * r.height));
}

void StartFrame::loadShapes(float const & width, float const & height,
                            sf::Vector2f const pos)
{
  sf::Vector2f v1(width, 2 * height);
  selected.setSize(v1);
  selected.setPosition(pos);
}

void StartFrame::render(sf::RenderWindow &window) const
{
  window.draw(backgroundSprite);
  window.draw(backgroundSprite2);
  window.draw(title);
  window.draw(selected);

  switch(state){
      case 0: renderStart(window);
              break;
      case 1: renderSingle(window);
              break;
      case 2: renderMulti(window);
              break;
      case 3: window.close();
              break;
  window.draw(selected);

  }
}

void StartFrame::renderStart(sf::RenderWindow &window) const
{
  window.draw(singlePlayer);
  window.draw(multiPlayer);
  window.draw(quit);
}

void StartFrame::renderSingle(sf::RenderWindow &window) const
{
    window.draw(start);
    window.draw(back);
}

void StartFrame::renderMulti(sf::RenderWindow &window) const
{
  window.draw(start);
  window.draw(back);
}

Frame *StartFrame::iterate()
{
  backgroundSprite2.setRotation(backgroundAngle / 3);
  backgroundSprite.setRotation(backgroundAngle * 2);
  backgroundAngle -= backgroundAngleMomentum ;
  return nextFrame;
}

void StartFrame::increasePosition()
{
  if(state == 0)
  {

    if (position >= 2)
    {
      position = 0;
      return;
    }
    position++;
  }
  else if(state == 1)
  {
    if (position >= 1)
    {
      position = 0;
      return;
    }
    position++;
  }
  else if(state == 2)
  {
    if (position >= 1)
    {
      position = 0;
      return;
    }
    position++;
  }

}

void StartFrame::decreasePosition()
{

  if(state == 0)
  {

    if (position == 0)
    {
      position = 2;
      return;
    }
    position--;
  }
  else if(state == 1)
  {
    if (position == 0)
    {
      position = 1;
      return;
    }
    position--;
  }
  else if(state == 2)
  {
    if (position == 0)
    {
      position = 1;
      return;
    }
    position--;
  }
}

void StartFrame::selectPosition()
{
  switch(state)
  {
    case 0: titleSelectPosition();
            break;
    case 1: singleSelectPosition();
            break;
    case 2: multiSelectPosition();
            break;
  }
}

void StartFrame::titleSelectPosition()
{
  switch(position)
  {
    case 0: state = 1;
            position = 0;
            break;
    case 1: state = 2;
            position = 0;
            break;
    case 2: state = 3;
            position = 0;
            break;
  }
}

void StartFrame::singleSelectPosition()
{
  if (position == 0)
  {
    nextFrame = new SingleplayerFrame;
  }
  else if (position == 1)
  {
    state = 0;
    position = 0;
  }
}

void StartFrame::multiSelectPosition()
{
  if (position == 0)
  {
    nextFrame = new MultiplayerFrame;
  }
  else if (position == 1)
  {
    state = 0;
    position = 0;
  }
}

void StartFrame::handleEvent(const sf::Event &event)
{
    // Wait a tiny tiny amount of time before we handle the first event, so 
    // the user dont accidentaly selects something.
    if (waitTimer.getElapsedTime() < sf::milliseconds(300))
    {
        return;
    }
    else
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Down)
            {
                increasePosition();
            }
            else if(event.key.code == sf::Keyboard::Up)
            {
                decreasePosition();
            }
            else if(event.key.code == sf::Keyboard::Return)
            {
                selectPosition();
            }
        }

        if(state == 0)
        {
            if(position == 0)
            {
                loadShapes(singlePlayer.getLocalBounds().width,
                        singlePlayer.getLocalBounds().height,
                        singlePlayer.getPosition());
            }
            else if(position == 1)
            {
                loadShapes(multiPlayer.getLocalBounds().width,
                        multiPlayer.getLocalBounds().height,
                        multiPlayer.getPosition());
            }
            else if(position == 2)
            {
                loadShapes(quit.getLocalBounds().width,
                        multiPlayer.getLocalBounds().height,
                        quit.getPosition());
            }
        }
        else if(state == 1 || state == 2)
        {
            if(position == 0)
            {
                loadShapes(start.getLocalBounds().width,
                        start.getLocalBounds().height,
                        start.getPosition());
            }
            else if(position == 1)
            {
                loadShapes(back.getLocalBounds().width,
                        back.getLocalBounds().height,
                        back.getPosition());
            }
        }
    }
}
