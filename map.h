#pragma once

#pragma once

static const int HEIGHT = 19;
static const int WIDTH = 70;


static const char w = '#'; //wall      
static const char b = '&'; // breadcrumbw

char map[HEIGHT][WIDTH] =
{ {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w},
 {w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w},
 {w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w},
 {w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w},
 {w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w},
 {w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, b, w, w, w, w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, w, w, w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, b, w},
 {w, b, w, w, w, w, b, w, w, w, w, w, w, b, w, w, w, w, b, w, w, w, w, b, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w},
 {w, b, w, w, w, w, b, w, w, w, w, w, w, b, w, w, w, w, b, w, w, w, w, b, w, w, w, b, w, b, b, b, b, b, b, b, b, b, b, b, b, w, b, w, w, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w},
 {w, b, w, w, w, w, b, w, w, w, w, w, w, b, w, w, w, w, b, w, w, w, w, b, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w},
 {b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, w, w, b, w, b, b, b, b, b, b, b, b, b, b, w, b, w, b, w, w, w, b, b, b, b, b, b, w, w, b, b, b, b, b, b, b, b, b, b, w, w, w, w, b, b},
 {w, b, w, w, w, w, b, w, w, w, w, w, w, b, w, w, w, w, b, w, w, w, w, b, w, w, w, b, w, b, w, w, w, w, w, w, w, w, b, w, b, w, b, w, w, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w},
 {w, b, w, w, w, w, b, w, w, w, w, w, w, b, w, w, w, w, b, w, w, w, w, b, w, w, w, b, w, b, b, b, b, b, b, b, b, b, b, w, b, w, b, w, w, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w},
 {w, b, w, w, w, w, b, w, w, w, w, w, w, b, w, w, w, w, b, w, w, w, w, b, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w},
 {w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, b, b, b, b, b, b, b, b, b, b, b, b, w, b, b, b, b, b, w, b, b, b, b, b, w, w, w, w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, b, w},
 {w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w},
 {w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w},
 {w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, b, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, b, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w},
 {w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, w},
 {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, b, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w} };