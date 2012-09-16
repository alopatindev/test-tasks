#ifndef GAMESDK_INPUT_H
#define GAMESDK_INPUT_H

class Input
{
public:
	Input();
	virtual ~Input();
	bool Clicked() const;
	void Update();
	float GetMouseX() const;
	float GetMouseY() const;
};

#endif