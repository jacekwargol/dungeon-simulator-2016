#include "stdafx.h"
#include "Wall.h"


bool Wall::isLoaded_ = false;
Texture* Wall::wallTexture_ = NULL;

Wall::Wall(){
    displayListId_ = -1;
    vertices_[0] = (0.0, 0.0, 0.0);
    vertices_[1] = (0.0, 0.0, 0.0);
    vertices_[2] = (0.0, 0.0, 0.0);
    vertices_[3] = (0.0, 0.0, 0.0);
    normal_ = (0.0, 0.0, 0.0);
}

Wall::Wall(Vector3 a, Vector3 b, Vector3 c, Vector3 d){
    displayListId_ = -1;
    vertices_[0] = a;
    vertices_[1] = b;
    vertices_[2] = c;
    vertices_[3] = d;
    normal_.cross((c - b), (a - b));
    normal_.normalize();
}

Wall::~Wall(){
}

void Wall::initialize(){
    displayListId_ = glGenLists(1);

    glNewList(displayListId_, GL_COMPILE);
    glBegin(GL_QUADS);

    glNormal3f(normal_.x_, normal_.y_, normal_.z_);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(vertices_[0].x_, vertices_[0].y_, vertices_[0].z_);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(vertices_[1].x_, vertices_[1].y_, vertices_[1].z_);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(vertices_[2].x_, vertices_[2].y_, vertices_[2].z_);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(vertices_[3].x_, vertices_[3].y_, vertices_[3].z_);

    glEnd();
    glEndList();

    if (isLoaded_){
    return;
    }
    isLoaded_ = true;

    wallTexture_ = new Texture("Resources\\RockTex1.bmp");
    wallTexture_->load();
}

void Wall::render(){
    glPushMatrix();

    float mAmb[] = { 0.545f, 0.49f, 0.4823f };
    float mSpe[] = { 0.5f, 0.5f, 0.4f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mSpe);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTexture_->getId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glCallList(displayListId_);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}