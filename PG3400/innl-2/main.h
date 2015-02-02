#ifndef _main_h
#define _main_h

/* enum declerations */
typedef enum { LIVING_ROOM, KITCHEN, BATH, BEDROOM, ENTRANCE } RoomNames;
typedef enum { N, W, S, E } Direction;

/* struct declerations */
typedef struct player { 
	double bodyTempLevel; 
	int wakefulnessLevel; } Player;

typedef struct room { 
	char* roomName; 
	char* description;
	int entriesCount; //is 1 by default
	struct room* entries[4]; } Room;


/* method declerations */
void introduction(void);
Room* triangulate(void); 
void initRooms(void);
void initRoomStrings(void);
void initRoomEntries(void);
Room* mlcRoom(char* name, char* desc);
void update(void);
void draw(void);

#endif