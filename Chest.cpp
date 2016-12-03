#include "stdafx.h"
#include "Chest.h"


Chest::Chest(int gridPosZ, int gridPosX, int gridDir){
    gridPos_[0] = gridPosZ;
    gridPos_[1] = gridPosX;
    gridDir_ = gridDir;
    float x = gridPos_[1] * GRID + GRID / 2;
    float z = gridPos_[0] * GRID + GRID / 2;
    pos_.set(x, 0.0f, z);
    dir_.set(1.0f, 0.0f, 0.0f);
    angle_ = 0.0;
    animSpeed_ = 0.5;
    isOpen_ = false;
    symbol_ = 'c';
}

Chest::~Chest(){}

void Chest::initialize(){
    displayListId_[0] = glGenLists(1);
    displayListId_[1] = glGenLists(2);

#pragma region Body
    // Front - Left - Back - Right - Bottom - Top(F, L, B, R)
    glNewList(displayListId_[0], GL_COMPILE);
    glBegin(GL_QUADS);

    // Front 
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.65f, 2.0f);
    glVertex3f(-0.5f, 0.0f, 2.0f);
    glVertex3f(0.5f, 0.0f, 2.0f);
    glVertex3f(0.5f, 0.65f, 2.0f);

    // Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.65f, 2.0f);
    glVertex3f(-0.5f, 0.65f, 1.5f);
    glVertex3f(-0.5f, 0.0f, 1.5f);
    glVertex3f(-0.5f, 0.0f, 2.0f);

    // Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.5f, 0.65f, 1.5f);
    glVertex3f(0.5f, 0.65f, 1.5f);
    glVertex3f(0.5f, 0.0f, 1.5f);
    glVertex3f(-0.5f, 0.0f, 1.5f);

    // Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.65f, 2.0f);
    glVertex3f(0.5f, 0.0f, 2.0f);
    glVertex3f(0.5f, 0.0f, 1.5f);
    glVertex3f(0.5f, 0.65f, 1.5f);

    // Bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 2.0f);
    glVertex3f(-0.5f, 0.0f, 1.5f);
    glVertex3f(0.5f, 0.0f, 1.5f);
    glVertex3f(0.5f, 0.0f, 2.0f);

    // Top Front
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.65f, 1.98f);
    glVertex3f(-0.5f, 0.65f, 2.0f);
    glVertex3f(0.5f, 0.65f, 2.0f);
    glVertex3f(0.5f, 0.65f, 1.98f);

    // Top Left
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.65f, 1.98f);
    glVertex3f(-0.48f, 0.65f, 1.98f);
    glVertex3f(-0.48f, 0.65f, 1.52f);
    glVertex3f(-0.5f, 0.65f, 1.52f);

    // Top Back
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.65f, 1.5f);
    glVertex3f(-0.5f, 0.65f, 1.52f);
    glVertex3f(0.5f, 0.65f, 1.52f);
    glVertex3f(0.5f, 0.65f, 1.5f);

    // Top Right
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.48f, 0.65f, 1.52f);
    glVertex3f(0.48f, 0.65f, 1.98f);
    glVertex3f(0.5f, 0.65f, 1.98f);
    glVertex3f(0.5f, 0.65f, 1.52f);
    //******************************
    // Inside
    // Front
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.48f, 0.65f, 1.98f);
    glVertex3f(0.48f, 0.65f, 1.98f);
    glVertex3f(0.48f, 0.0f, 1.98f);
    glVertex3f(-0.48f, 0.0f, 1.98f);

    // Left
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.48f, 0.65f, 1.98f);
    glVertex3f(-0.48f, 0.0f, 1.98f);
    glVertex3f(-0.48f, 0.0f, 1.52f);
    glVertex3f(-0.48f, 0.65f, 1.52f);

    // Back
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.48f, 0.65f, 1.52f);
    glVertex3f(-0.48f, 0.0f, 1.52f);
    glVertex3f(0.48f, 0.0f, 1.52f);
    glVertex3f(0.48f, 0.65f, 1.52f);

    // Right
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.48f, 0.65f, 1.98f);
    glVertex3f(0.48f, 0.65f, 1.52f);
    glVertex3f(0.48f, 0.0f, 1.52f);
    glVertex3f(0.48f, 0.0f, 1.98f);

    // Bottom
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.48f, 0.02f, 1.52f);
    glVertex3f(-0.48f, 0.02f, 1.98f);
    glVertex3f(0.48f, 0.02f, 1.98f);
    glVertex3f(0.48f, 0.02f, 1.52f);


    glEnd();
    glEndList();
#pragma endregion

#pragma region Cover
    glNewList(displayListId_[1], GL_COMPILE);

    // Left
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 24; ++i) {
        float y = sin(PI * ((float)i / 24));
        float z = cos(PI * ((float)i / 24));
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, y / 4, z / 4);
    }
    glEnd();
    glPopMatrix();

    // Right
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    for (int i = 24; i >= 0; --i) {
        float y = sin(PI * ((float)i / 24));
        float z = cos(PI * ((float)i / 24));
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, y / 4, z / 4);
    }
    glEnd();
    glPopMatrix();

    //Top
    glPushMatrix();
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 24; ++i) {
        float z = sin(PI * ((float)i / 24));
        float y = cos(PI * ((float)i / 24));
        glNormal3f(0.0f, y, z);
        glVertex3f(1.0f, y / 4, z / 4);
        glNormal3f(0.0f, y, z);
        glVertex3f(0.0f, y / 4, z / 4);
    }
    glEnd();
    glPopMatrix();

    // Bottom
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(0.0f, 0.0f, -0.25f);
    glVertex3f(1.0f, 0.0f, -0.25f);
    glVertex3f(1.0f, 0.0f, 0.25f);
    glEnd();
    glPopMatrix();

    glEndList();

}

void Chest::render(){
    // Cover
    glPushMatrix();
    glTranslatef(pos_.getX(), pos_.getY(), pos_.getZ());
    glRotatef(90.0 * gridDir_, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.5f, 0.65f, 1.75f);
    glTranslatef(0.0f, 0.0f, 0.25f);
    glRotatef(angle_, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.25f);
    glCallList(displayListId_[1]);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(pos_.getX(), pos_.getY(), pos_.getZ());
    glRotatef(90.0 * gridDir_, 0.0f, 1.0f, 0.0f);
    glCallList(displayListId_[0]);
    glPopMatrix();

    // Cover animation
    if (isOpen_ && angle_ < 45.0){
        angle_ += animSpeed_;
    }
    else if (!isOpen_ && angle_ > 0.0){
        angle_ -= animSpeed_;
    }
}