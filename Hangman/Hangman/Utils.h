#pragma once

#ifndef __UTILS_H__
#define __UTILS_H__

char GetCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength);
char GetCharacter(const char * prompt, const char* error);
void ClearScreen();
void WaitForKeyPress();

#endif // !__UTILS_H__