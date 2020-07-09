// ==================================================
// file: PK13_Camera.cpp
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#include "../include/PK13_Camera.h"

#include <stdint.h>

void PK13_Camera::Reset(int w, int h)
{
	cx     = w >> 1;
	cy     = h >> 1;
	x1     = 0;
	y1     = 0;
	x2     = w;
	y2     = h;
	vx     = 20;
	vy     = 10;
	scale  = 1.f;
	update = true;
}
void PK13_Camera::MoveR()
{
	if(x2 + vx < INT16_MAX)
	{
		cx += vx;
		x1 += vx;
		x2 += vx;
		update = true;
	}
}
void PK13_Camera::MoveL()
{
	if(x1 - vx > INT16_MIN)
	{
		cx -= vx;
		x1 -= vx;
		x2 -= vx;
		update = true;
	}
}
void PK13_Camera::MoveU()
{
	if(y1 - vy > INT16_MIN)
	{
		cy -= vy;
		y1 -= vy;
		y2 -= vy;
		update = true;
	}
}
void PK13_Camera::MoveD()
{
	if(y2 + vy < INT16_MAX)
	{
		cy += vy;
		y1 += vy;
		y2 += vy;
		update = true;
	}
}
void PK13_Camera::MoveX(short velx)
{
	if((x1 + velx > INT16_MIN) && (x2 + velx < INT16_MAX))
	{
		cx += velx;
		x1 += velx;
		x2 += velx;
		update = true;
	}
}
void PK13_Camera::MoveY(short vely)
{
	if((y1 + vely > INT16_MIN) && (y2 + vely < INT16_MAX))
	{
		cy += vely;
		y1 += vely;
		y2 += vely;
		update = true;
	}
}
void PK13_Camera::ZoomIn(int w, int h)
{
	if((scale += 0.1f) > 3.f) scale = 3.f;

	// todo: optimize it
	float temp = (w >> 1) * (1 / scale);
	x1         = cx - temp;
	x2         = cx + temp;
	temp       = (h >> 1) * (1 / scale);
	y1         = cy - temp;
	y2         = cy + temp;

	update = true;
}
void PK13_Camera::ZoomOut(int w, int h)
{
	if((scale -= 0.1f) < 0.5f) scale = 0.5f;

	// todo: optimize it
	float temp = (w >> 1) * (1 / scale);
	x1         = cx - temp;
	x2         = cx + temp;
	temp       = (h >> 1) * (1 / scale);
	y1         = cy - temp;
	y2         = cy + temp;

	update = true;
}