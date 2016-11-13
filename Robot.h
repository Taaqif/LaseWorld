//Robot.h
//Header file for Robot class
//class generates a robot model in 3d, generates hitboxes for it, has basic animation for it
//uses SOIL.h for textures
//CHANGES
//changed default value for RobotPosY, added std::string Texture to SetrobotPos

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "glut.h"
#include <map>
#include <SOIL.h>
//#include "main.cpp"
/// Ben Porter, class for creating Robot Objects
class Robot
{
public:
	Robot();
	int EnemyHP = 1;
	void SetRobotPos(GLuint xpos, GLuint ypos, GLuint zpos, char RobotSide, GLuint xwidth, GLuint zwidth, GLuint yheight, std::string Texture);
	void CreateRobotObject();
	void SetEnemyHP(int HP);
	void SetEnemyAlive(bool live);
	GLuint getBotX() { return RobotPosX; };
	GLuint getBotY() { return RobotPosY; };
	GLuint getBotZ() { return RobotPosZ; };
	GLint RobotPosX = 1000, RobotPosY = 0, RobotPosZ = 40000, RobotWidthX = 150, RobotWidthZ = 100, RobotHeight = 400;
	bool Alive = false;
private:

	char Side = 'f';
	int LoadCycle = 0;
	//std::map<std::string, GLuint> textures;
	std::string RobotTexture;
	std::map<std::string, GLuint> robottextures;
	void HitRobot();
	void LoadRobotTexture();
	
	void LoadRobot();
	void DrawRobot();
	void AliveRobot();
};