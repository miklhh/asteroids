// Global settings for the asteroids game. These include default game settings
// and default keybindings.
#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

// Default game settings.
// -----------------------------------------------------------------------------
const unsigned              SCREEN_WIDTH                    = 1920;
const unsigned              SCREEN_HEIGHT                   = 1080;
const sf::Color             DEFAULT_CLEAR_COLOR             = sf::Color(10, 10, 13, 255);
const float                 DEFAULT_BLIND_SPOT              = 120.0f;
const float                 DEAFULT_PROJECTILE_SPEED        = 8.0f;
const float                 DEFAULT_SHIP_SPEED              = 1.0f;
const float                 DEFAULT_SHIP_ROTATE_SPEED       = 5.0f;
const float                 DEFAULT_SHIP_BREAK_COEFF        = 1.03f;
const float                 DEFAULT_SHIP_RECOIL             = 0.2f;
const float                 DEFAULT_SHIP_SCALE              = 0.07f;
const float                 DEFAULT_SHIP_FIRE_RATE          = 7.0f;
const int                   DEFAULT_SHIP_EXTRA_BARRELS      = 0;
const sf::Time              DEFAULT_POWER_UP_LIFE_TIME      = sf::seconds(10.0f);
const sf::Time              DEFAULT_POWER_UP_ACTIVE_TIME    = sf::seconds(5.0f);
const float                 DEFAULT_POWER_UP_SPAWN_RATE     = 0.1f;
const float                 INITIAL_ASTEROID_FREQUENCY      = 1.0f;
const float                 INITIAL_ASTEROID_SPEED          = 1.5f;
const sf::Time              DEFAULT_WAVETIME                = sf::seconds(10.0f);

// Default keybindings.
// -----------------------------------------------------------------------------
const sf::Keyboard::Key     DEFAULT_KEY_PLAY1_ACCELERATE    = sf::Keyboard::Up;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY1_LEFT          = sf::Keyboard::Left;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY1_RIGHT         = sf::Keyboard::Right;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY1_SHOOT         = sf::Keyboard::L;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY2_ACCELERATE    = sf::Keyboard::W;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY2_LEFT          = sf::Keyboard::A;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY2_RIGHT         = sf::Keyboard::D;
const sf::Keyboard::Key     DEFAULT_KEY_PLAY2_SHOOT         = sf::Keyboard::Q;

#endif
