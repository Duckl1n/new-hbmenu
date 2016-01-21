#pragma once
#include "common.h"
#include "parsing/smdh.h"
#include "parsing/descriptor.h"

#define ENTRY_NAMELENGTH   (0x40*3)
#define ENTRY_DESCLENGTH   (0x80*3)
#define ENTRY_AUTHORLENGTH (0x40*3)
#define ENTRY_ARGBUFSIZE   0x400

typedef enum
{
	ENTRY_TYPE_FILE,
	ENTRY_TYPE_FOLDER,
} MenuEntryType;

typedef struct menuEntry_s_tag menuEntry_s;
typedef struct menu_s_tag menu_s;

struct menuEntry_s_tag
{
	menu_s* menu;
	menuEntry_s* next;
	MenuEntryType type;

	char path[PATH_MAX+1];
	int argc;
	u32 argbuffer[ENTRY_ARGBUFSIZE/sizeof(u32)];

	char name[ENTRY_NAMELENGTH+1];
	char description[ENTRY_DESCLENGTH+1];
	char author[ENTRY_AUTHORLENGTH+1];

	smdh_s smdh;
	descriptor_s descriptor;

	C3D_Tex* icon;
	C3D_Tex texture;
};

void menuEntryInit(menuEntry_s* me, MenuEntryType type);
void menuEntryFree(menuEntry_s* me);
bool menuEntryLoad(menuEntry_s* me, const char* name, bool shortcut);
void menuEntryParseSmdh(menuEntry_s* me);

struct menu_s_tag
{
	menuEntry_s *firstEntry, *lastEntry;
	int nEntries;
	int curEntry;

	char dirname[PATH_MAX+1];

	float scrollTarget;
	float scrollLocation;
	float scrollVelocity;

	touchPosition previousTouch, firstTouch;
	int touchTimer;
	bool atEquilibrium;
};

menu_s* menuGetCurrent(void);
int menuScan(const char* target);

static inline char* getExtension(const char* str)
{
	const char* p;
	for (p = str+strlen(str); p >= str && *p != '.'; p--);
	return (char*)p;
}

static inline char* getSlash(const char* str)
{
	const char* p;
	for (p = str+strlen(str); p >= str && *p != '/'; p--);
	return (char*)p;
}
