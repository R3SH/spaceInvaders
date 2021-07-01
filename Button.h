#pragma once
#include <SDL.h>


class Button
{
public:
	Button();
	Button(int x, int y, int w, int h);
	~Button();

	void setButtonPos(SDL_Rect tmpRect);
	void setButtonPos(int x, int y, int w, int h);
	SDL_Rect* getButtonChar();
	SDL_Rect* getButtonPos() { return &bPos; }

private:
	SDL_Rect bPos;

};