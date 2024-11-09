/*
 * ANSI Lib
 *
 * https://github.com/Constantin-Alexandru/ansi-lib-c
 *
 * Ansi Lib is a multi-language library that allows the coloured printing of
 * text inside terminals.
 *
 * VERSION: 2.0
 *
 * Copyright 2024 Alexandru Constantin <dev.alexandru.constantin@gmail.com>
 */

#ifndef ANSI_LIB_H
#define ANSI_LIB_H

#include <stdio.h>

#if defined(_WIN32)

#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>

#if !defined(ENABLE_VIRTUAL_TERMINAL_PROCESSING)

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

#endif  // ENABLE_VIRTUAL_TERMINAL_PROCESSING

#define WIN_ERR exit(GetLastError())

static HANDLE stdOutputHandle;
static DWORD outputModeInitial;

static void setupConsole(void) {
  DWORD outputMode = 0;

  stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  if (stdOutputHandle == INVALID_HANDLE_VALUE) {
    WIN_ERR;
  }

  if (!GetConsoleMode(stdOutputHandle, &outputMode)) {
    WIN_ERR;
  }

  outputModeInitial = outputMode;

  outputMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  if (!SetConsoleMode(stdOutputHandle, outputMode)) {
    WIN_ERR;
  }
}

/// Initialises windows consoles to allow the use of coloring
#define ANSI_LIB_WINDOWS_INIT() setupConsole()

#endif  // _WIN32

#define ANSI_LIB_WINDOWS_INIT()

#define CONTROL_SEQUENCE "\x1b["

/**
 * Returns the escape code string for setting the color chosen. Accepts one of
 * the predefined 8 color values. Each color has a predefined MACRO that calls
 * the function with the corresponding value.
 */
#define COLOR(value) CONTROL_SEQUENCE #value "m"

/**
 * Returns the escape code string for setting the color of the text using the
 * 256 color mode.
 */
#define COLOR256(value) CONTROL_SEQUENCE "38;5;" #value "m"

/**
 * Returns the escape code string for setting the color of the background using
 * the 256 color mode.
 */
#define BKG_COLOR256(value) CONTROL_SEQUENCE "48;5;" #value "m"

/**
 * Returns the escape code string for setting the color of the text using rgb
 * values.
 */
#define COLORRGB(r, g, b) CONTROL_SEQUENCE "38;2;" #r #g #b "m"

/**
 * Returns the escape code string for setting the color of the background using
 * rgb values.
 */
#define BKG_COLORRGB(r, g, b) CONTROL_SEQUENCE "48;2;" #r #g #b "m"

#define BLACK COLOR(30)
#define RED COLOR(31)
#define GREEN COLOR(32)
#define YELLOW COLOR(33)
#define BLUE COLOR(34)
#define MAGENTA COLOR(35)
#define CYAN COLOR(36)
#define WHITE COLOR(37)

#define BKG_BLACK COLOR(40)
#define BKG_RED COLOR(41)
#define BKG_GREEN COLOR(42)
#define BKG_YELLOW COLOR(43)
#define BKG_BLUE COLOR(44)
#define BKG_MAGENTA COLOR(45)
#define BKG_CYAN COLOR(46)
#define BKG_WHITE COLOR(47)

/// Sets the color for any of the color functions above.
#define SET_COLOR(color) printf("%s", color)

/// Returns the string for a predefined effect.
#define EFFECT(value) COLOR(value)

#define BOLD EFFECT(1)
#define DIM EFFECT(2)
#define ITALIC EFFECT(3)
#define UNDERLINE EFFECT(4)
#define BLINKING EFFECT(5)
#define INVERSE EFFECT(6)
#define HIDDEN EFFECT(7)
#define STRIKETHROUGH EFFECT(9)
#define DOUBLE_UNDERLINE EFFECT(21)

#define BOLD_RESET EFFECT(22)
#define DIM_RESET EFFECT(22)
#define ITALIC_RESET EFFECT(23)
#define UNDERLINE_RESET EFFECT(24)
#define BLINKING_RESET EFFECT(25)
#define INVERSE_RESET EFFECT(27)
#define HIDDEN_RESET EFFECT(28)
#define STRIKETHROUGH_RESET EFFECT(29)
#define DOUBLE_UNDERLINE_RESET EFFECT(24)

/// Sets the effect for the effect functions above.
#define SET_EFFECT(effect) printf("%s", effect)

/// Resets both colors and effects.
#define RESET() SET_EFFECT(EFFECT(0))

/// Jumps to the correspondinc row and column
#define GOTOXY(x, y) printf("%s%d;%dH", CONTROL_SEQUENCE, x, y)

/// Goes up n lines
#define GoUpN(n) printf("%s%dA", CONTROL_SEQUENCE, n)

/// Goes up n lines, but the cursor jumps to the initial cursor.
#define GoUpNLines(n) printf("%s%dF", CONTROL_SEQUENCE, n)

#define GoDownN(n) printf("%s%dB", CONTROL_SEQUENCE, n)

#define GoDownNLines(n) printf("%s%dE", CONTROL_SEQUENCE, n)

#define GoRightN(n) printf("%s%dC", CONTROL_SEQUENCE, n)

#define GoLeftN(n) printf("%s%dD", CONTROL_SEQUENCE, n)

#define CLEAR_SCREEN() printf("%s2J", CONTROL_SEQUENCE)

#define CLEAR_SCREEN_BELOW() printf("%s0J", CONTROL_SEQUENCE)

#define CLEAR_SCREEN_ABOVE() printf("%s1J", CONTROL_SEQUENCE)

#define CLEAR_LINE() printf("%s2K", CONTROL_SEQUENCE)

#define CLEAR_LINE_RIGHT() printf("%s0K", CONTROL_SEQUENCE)

#define CLEAR_LINE_LEFT() printf("%s1K", CONTROL_SEQUENCE)

#endif  // ANSI_LIB_H
