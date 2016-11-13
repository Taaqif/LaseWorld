#include "Robot.h"

Robot::Robot()
{
}
//used for default actions all robot objects should do
void Robot::CreateRobotObject(){
	//LoadRobotTexture();
	DrawRobot();

}
//Loads in the textures for robots
void Robot::LoadRobotTexture(){
	
	robottextures["WarriorFrontStanding"] = SOIL_load_OGL_texture
		(
		"data/WarriorFront/Standing.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["WarriorFrontMoving1"] = SOIL_load_OGL_texture
		(
		"data/WarriorFront/Moving1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["WarriorFrontMoving2"] = SOIL_load_OGL_texture
		(
		"data/WarriorFront/Moving2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["WarriorFrontMoving3"] = SOIL_load_OGL_texture
		(
		"data/WarriorFront/Moving3.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["WarriorFrontHurt"] = SOIL_load_OGL_texture
		(
		"data/WarriorFront/Hurt.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["WarriorFrontFiring"] = SOIL_load_OGL_texture
		(
		"data/WarriorFront/Firing.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["TestTargetWarrior"] = SOIL_load_OGL_texture
		(
		"data/TestTargets/WarriorTestTarget.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["TestTargetObserver"] = SOIL_load_OGL_texture
		(
		"data/TestTargets/ObserverTestTarget.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["TestTargetObserver"] = SOIL_load_OGL_texture
		(
		"data/TestTargets/ObserverTestTarget.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["ControllerArm"] = SOIL_load_OGL_texture
		(
		"data/Controller/Arms/ControllerArmIdle.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["ControllerBody"] = SOIL_load_OGL_texture
		(
		"data/Controller/Body/Controlleridle.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["ControllerLegs"] = SOIL_load_OGL_texture
		(
		"data/Controller/Legs/ControllerLegsUnpacked.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["ControllerHorizontalArmConnector"] = SOIL_load_OGL_texture
		(
		"data/Controller/ControllerArmConnector.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	robottextures["ControllerVerticalArmConnector"] = SOIL_load_OGL_texture
		(
		"data/Controller/Legs/ControllerLegsUnpacked.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
}


//Draws the image of the robot using RobotPosX, RobotPosY, RobotPosZ, RobotWidthX, RobotWidth, RobotHeight, side and texture;
void Robot::DrawRobot(){
	//Draws a robot
	//TO DO: make a string for file name
	//glEnable(GL_COLOR_MATERIAL);
	if (LoadCycle == 0){
		LoadRobotTexture();
		LoadCycle = 1;
	}
	

	//x, y, z BL, BR, TR, TL

	// Front face 
	if (EnemyHP > 0){


		if (Side == 'f'){
			//LoadRobotTexture();
			//RobotHitBoxes();
			glColor4f(254 / 255.0f, 254 / 255.0f, 254 / 255.0f, 1.0f);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, robottextures[RobotTexture]);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(RobotPosX + RobotWidthX, RobotPosY + RobotHeight, RobotPosZ + RobotWidthZ);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(RobotPosX - RobotWidthX, RobotPosY + RobotHeight, RobotPosZ + RobotWidthZ);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(RobotPosX - RobotWidthX, RobotPosY - RobotHeight, RobotPosZ + RobotWidthZ);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(RobotPosX + RobotWidthX, RobotPosY - RobotHeight, RobotPosZ + RobotWidthZ);
			glEnd();
		}
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// Left face  
		if (Side == 'l'){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, robottextures[RobotTexture]);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(RobotPosX - RobotWidthX, RobotPosY + RobotHeight, RobotPosZ + RobotWidthZ);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(RobotPosX - RobotWidthX, RobotPosY + RobotHeight, RobotPosZ - RobotWidthZ);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(RobotPosX - RobotWidthX, RobotPosY - RobotHeight, RobotPosZ - RobotWidthZ);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(RobotPosX - RobotWidthX, RobotPosY - RobotHeight, RobotPosZ + RobotWidthZ);
			glEnd();
		}

		// Right face 
		if (Side == 'r'){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, robottextures[RobotTexture]);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(RobotPosX + RobotWidthX, RobotPosY + RobotHeight, RobotPosZ - RobotWidthZ);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(RobotPosX + RobotWidthX, RobotPosY + RobotHeight, RobotPosZ + RobotWidthZ);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(RobotPosX + RobotWidthX, RobotPosY - RobotHeight, RobotPosZ + RobotWidthZ);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(RobotPosX + RobotWidthX, RobotPosY - RobotHeight, RobotPosZ - RobotWidthZ);
			glEnd();
		}
	}

	AliveRobot();
}
//sets where the robot will be spawned and what texture it will have as well as direction of texture
void Robot::SetRobotPos(GLuint xpos, GLuint ypos, GLuint zpos, char RobotSide, GLuint xwidth, GLuint zwidth, GLuint yheight, std::string Texture){
	RobotPosX = xpos, RobotPosY = ypos, RobotPosZ = zpos, RobotWidthX = xwidth, RobotWidthZ = zwidth, RobotHeight = yheight;
	Side = RobotSide;
	RobotTexture = Texture;

}
void Robot::SetEnemyHP(int HP){
	EnemyHP = HP;

}

void Robot::SetEnemyAlive(bool Live){
	Alive = Live;
}

//makes the robot alive or dead according to it's hp
void Robot::AliveRobot(){
	if (EnemyHP == 0){
		Alive = false;
	}

}




