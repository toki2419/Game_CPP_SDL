#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32; //screen pixel

const int COLOR_KEY_G = 167;
const int COLOR_KEY_R = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0XFF;
#endif