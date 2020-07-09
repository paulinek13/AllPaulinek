// ==================================================
// file: PK13_Camera.h
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#ifndef PK13_CAMERA_H
#define PK13_CAMERA_H

// represents just a camera object;
// it has its positions, width,
// height and scale;
struct PK13_Camera
{
	int   cx    = 0;   // center x position
	int   cy    = 0;   // center y position
	int   x1    = 0;   // most left x position
	int   y1    = 0;   // most up y position
	int   x2    = 0;   // most right x position
	int   y2    = 0;   // most down x position
	int   vx    = 0;   // velocity x
	int   vy    = 0;   // velocity y
	float scale = 1.f; // zoom

	bool update = false; // if needed to update camera transformation

	// back to normal position and scale
	void Reset(int w, int h);

	// move right with set velocity vx
	void MoveR();

	// move left with set velocity vx
	void MoveL();

	// move up with set velocity vy
	void MoveU();

	// move down with set velocity vy
	void MoveD();

	// move horizontally with given velocity
	void MoveX(short velx);

	// move vertically with given velocity
	void MoveY(short vely);

	// bigger scale (more detailed)
	void ZoomIn(int w, int h);

	// smaller scale (less detailed)
	void ZoomOut(int w, int h);
};

#endif // !PK13_CAMERA_H