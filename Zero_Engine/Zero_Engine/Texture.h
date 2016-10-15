#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Texture
{
public:
	Texture()
	{}
	~Texture()
	{
		id = 0;
		width = 0;
		height = 0;
	}

public:
	uint id = 0;
	int width = 0;
	int height = 0;
};

#endif // __TEXTURE_H__