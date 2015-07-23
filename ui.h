#ifndef UI_H
#define UI_H

typedef struct Ui Ui;
typedef struct UiWin UiWin; 

enum UiLayout {
	UI_LAYOUT_HORIZONTAL,
	UI_LAYOUT_VERTICAL,
};

enum UiOption {
	UI_OPTION_LINE_NUMBERS_NONE = 0,
	UI_OPTION_LINE_NUMBERS_ABSOLUTE = 1 << 0,
	UI_OPTION_LINE_NUMBERS_RELATIVE = 1 << 1,
};

typedef struct {
	char str[6]; /* UTF8 character or terminal escape code */
	int code;    /* curses KEY_* constant */
} Key;

#include <stdbool.h>
#include <stdarg.h>
#include "text.h"
#include "view.h"
#include "editor.h"

struct Ui {
	bool (*init)(Ui*, Editor*);
	void (*free)(Ui*);
	void (*resize)(Ui*);
	UiWin* (*window_new)(Ui*, View*, File*);
	void (*window_free)(UiWin*);
	void (*window_focus)(UiWin*);
	UiWin* (*prompt_new)(Ui*, View*, File*);
	void (*prompt)(Ui*, const char *title, const char *value);
	char* (*prompt_input)(Ui*);
	void (*prompt_hide)(Ui*);
	void (*info)(Ui*, const char *msg, va_list ap);
	void (*info_hide)(Ui*);
	void (*arrange)(Ui*, enum UiLayout);
	void (*draw)(Ui*);
	void (*update)(Ui*);
	void (*suspend)(Ui*);
	void (*resume)(Ui*);
	Key (*getkey)(Ui*);
	bool (*haskey)(Ui*);
	void (*terminal_save)(Ui*);
	void (*terminal_restore)(Ui*);
};

struct UiWin {
	void (*draw)(UiWin*);
	void (*draw_text)(UiWin*, const Line*);
	void (*draw_status)(UiWin*);
	void (*reload)(UiWin*, File*);
	void (*options)(UiWin*, enum UiOption);
};

#endif
