#ifndef _Tile_H_
#define _Tile_H_

class Tile{
private:
	int value = 0;
	bool set = false;
public:
	void Set();
	void UnSet();
	bool CheckSet();
	int GetValue();
	void SetValue(int num);
	Tile();
	Tile(int value);
};

#endif