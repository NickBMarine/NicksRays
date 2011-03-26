#pragma once
#include "Matrix4x4.h"
#include "Vector.h"
#include "Keys.h"
#include <iostream>
using namespace std;

class Camera
{
	static unsigned short numCameras;

	//Matrix builders
	Matrix4x4 _cameraMat;
	Vector _rightView;
	Vector _upView;
	Vector _forwardView;

	//Camera positioning
	Vector _leftFac;
	Vector _upFac;
	Vector _forwardFac;
	float _cameraSpeed;

	Vector _pos;
	Vector _rot;
	
	HWND _hWnd;
	RECT _wBounds;
	RECT _oldClip;
	RECT _newClip;
	POINT _mousePos;
	POINT _wCenter;

	bool _speedTrig;
	bool _haveHandle;
	bool _isDirty;
	bool _isActive;
	bool _noClip;
public:

	Camera();
	Camera(Vector& leftView, Vector& upView, Vector& forwardView, bool noClip);
	Camera(Vector& leftView, Vector& upView, Vector& forwardView, Vector& pos, bool noClip);

	void GetWindow(const HWND & hWnd) {  _hWnd = hWnd; _haveHandle = true; SetWindow(); }
	void SetWindow() { 	GetWindowRect(_hWnd, &_newClip); ClipCursor(&_newClip); }
	void CalcWinCenter();
	void SetCameraSpeed(float speed) { _cameraSpeed = speed; };
	void SetCameraUp(Vector& upView) { _upView = upView; };
	void SetCameraRight(Vector& rightView) { _rightView = rightView; };
	void SetCameraForward(Vector& forwardView) { _forwardView = forwardView; };
	float ToRadians(float degrees);

	static unsigned short GetNumCameras() { return numCameras; };

	Vector GetPosition() { return _pos;};
	Vector GetRotation() { return _rot;};
	Vector GetLeftView() { return _rightView; };
	Vector GetUpView() { return _upView; };
	Vector GetForwardView() { return _forwardView; };

	void RotFac();

	
	//Flags Dirty
	//===========================
	void RotX(float x);
	void RotY(float y);
	void RotZ(float z);
	void TransX(float x);
	void TransY(float y);
	void TransZ(float z);
	void Rotate(Vector& rot);
	void Translate(Vector& trans);
	void SetPos(Vector& offset);
	//============================

	bool GetActivety() { return _isActive; };
	void BuildMatrix(Matrix4x4 & camMatrix);
	void GetCameraMatrix(Matrix4x4& camMatrix, Vector& vert);
	void Listen() { ListenKeys(); ListenMouse();};
	void ListenKeys();
	void ListenMouse();
	void CalcMouseRot(POINT & ptr);
	Matrix4x4 GetCameraMatrix();

	~Camera(void){};
};