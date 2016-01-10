#ifndef UI_H
#define UI_H

void initUI();

void drawString(const char* str);

void selectFont(int size, int charset, const char* face);

void showGameUI();

void showAim();

void showHP();

void showScore();

int LoadBitMap(const char *file);

void showWelcomePage();
#endif
