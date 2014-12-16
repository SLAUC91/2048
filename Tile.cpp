#include "Tile.h"

void Tile::Set(){
	set = true;
}

void Tile::UnSet(){
	set = false;
}

bool Tile::CheckSet(){
	return set;
}

int Tile::GetValue(){
	return value;
}

void Tile::SetValue(int num){
	value = num;
}

Tile::Tile(){
	value = 0;
	set = false;
}

Tile::Tile(int value){
	this->value = value;
	set = true;
}