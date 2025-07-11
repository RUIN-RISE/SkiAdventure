#define NOMINMAX 
#ifndef __PRE_COMP_H__
#define __PRE_COMP_H__

#include <cassert>
#include <vector>
#include <string>
#include <cstdint>
#include <functional>
#include <memory>
#include <ctime>
#include <cmath>
#include <utility>
#include <iostream>
#include <algorithm>
#include <chrono>

const double deltaTime = 1.0/60 ;
// const double deltaTime = 0.2 ;

//FLTK
#include <FL/Fl.H>
// #include <FL/Fl_Events.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include <FL/Fl_PNG_Image.H>

#include <FL/filename.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>

#include <FL/fl_ask.H>

//Stb
// #define STB_IMAGE_RESIZE2_IMPLEMENTATION

// #include <stb_image.h>
// #include <stb_image_resize2.h>

#endif
