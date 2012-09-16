#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
	Input();
	virtual ~Input();
	bool clicked() const;
	bool pressed() const;
	void update();
	int getPointerX() const;
	int getPointerY() const;
};

#endif