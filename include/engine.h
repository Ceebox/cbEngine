#ifndef ENGINE_H
#define ENGINE_H

#include "core.h"
#include "renderer.h"
#include "input.h"
#include "pixel.h"

//Engine functions

void InitWindow(StartFn start, UpdateFn update, FinishFn finish);
void SetTitle(std::string windowTitle);
void SetWindowSize(int size);
void SetVsync(bool enabled);
void CloseWindow();

//Other functions

double GetTime();
std::string ReadFromFile(const char *pathToFile);

#endif
