/*
 * Exception used in the asteroids game. Acts more or less like the a slimed 
 * down version of the standard library exceptions.
 */

#ifndef _ASTEROID_EXCEPTION_H
#define _ASTEROID_EXCEPTION_H

#include <exception>

class AsteroidException : public std::exception
{
public:
    AsteroidException(std::string msg) : msg(msg) { }
    const char *what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

#endif
