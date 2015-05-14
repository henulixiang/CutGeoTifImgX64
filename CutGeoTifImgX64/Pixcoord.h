#pragma once
class Pixcoord
{
public:
	Pixcoord(void);
	Pixcoord(int width, int height);
	~Pixcoord(void);
	int getWidth()
	{
		return width_;
	}
	int getHeight()
	{
		return height_;
	}
	void setWidth(int width)
	{
		this->width_ = width;
	}
	void setHeight(int height)
	{
		this->height_ = height;
	}
	Pixcoord& operator = (const Pixcoord &other)
	{
		if(this == &other)
		{
			return *this;
		}
		this->width_ = other.width_;
		this->height_ = other.height_;
		return *this;
	}
private:
	int width_;
	int height_;
};

