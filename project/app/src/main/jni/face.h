//
// Created by Toshiki Chizo on 2016/07/10.
//

#pragma once
#ifndef PROJECT_FACE_H
#define PROJECT_FACE_H

#include "Framework/Vector2D.h"

typedef unsigned char FACE_TYPE;
static const FACE_TYPE FACE_NORMAL = 0;
static const FACE_TYPE FACE_ANGRY = 1;
static const FACE_TYPE FACE_BAD = 2;
static const FACE_TYPE FACE_SMILE = 3;
static const FACE_TYPE FACE_MAX = 4;

static Vec2 g_FaceUV[FACE_MAX] = {
		Vec2(0.0f, 0.0f),
		Vec2(0.25f, 0.0f),
		Vec2(0.25f, 0.5f),
		Vec2(0.5f, 0.0f)
};

#endif //PROJECT_FACE_H
