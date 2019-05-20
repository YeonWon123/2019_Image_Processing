#pragma once

typedef unsigned char BYTE;

class RGBBYTE
{
public:
	BYTE b;
	BYTE g;
	BYTE r;

public:
	RGBBYTE() : b(0), g(0), r(0) {}
	RGBBYTE(BYTE gray) : b(gray), g(gray), r(gray) {}
	RGBBYTE(const BYTE& _r, const BYTE& _g, const BYTE& _b) : b(_b), g(_g), r(_r) {}
};

