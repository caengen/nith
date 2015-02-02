#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

const double MAX_BODY_TEMP_LEVEL	= 37.4;
const int MAX_WAKEFULNESS_LEVEL		= 5;

Room* rooms[5];
const int ROOMS_SIZE = 5;

int currentRoom = LIVING_ROOM;
Room* currentRoomPntr;
Player bob;

bool cold = true;

int main(void) {
	system("clear");

	//Initiate rooms
	initRooms();


	//Initiate player bob
	bob = (Player) {
		.bodyTempLevel = 36.6,
		.wakefulnessLevel = 0
	};

	//Introduce the player to the game story
	introduction();

	//Game loop
	while(cold) {
		//update room description
		currentRoomPntr = triangulate();

		//update stats
		//update options
		//draw screen
		draw();
		cold = !cold;
	}

	//free 
	for (int i = 1; i < ROOMS_SIZE; ++i) {
		free(rooms[i]->entries[0]);
		free(rooms[i]);
	}

	//free living room
	for (int i = 0; i < rooms[LIVING_ROOM]->entriesCount; ++i)
	{
		free(rooms[LIVING_ROOM]->entries[i]);
	}
	free(rooms[LIVING_ROOM]);

	free(currentRoomPntr);

	return EXIT_SUCCESS;
}

void introduction(void) {
	printf("%-5s\n", "Du våkner en søndags morgen etter en sen kveld med after-ski og dårlig");
	printf("%-5s\n", "musikk. Det er kaldt i hytta, og ikke har du sovet stort heller. Klokken");
	printf("%-5s\n", "begynner å bli mye og skal du få brukt heiskortet ditt før det går ut må");
	printf("%-5s\n", "du skynde deg ut i bakken, men før den tid må du bli klar.");
}

void update(void) {

}

void draw(void) {
	//prints the room description
	printf("\n%s\n\t%s\n", currentRoomPntr->roomName, currentRoomPntr->description);
	//prints the options available
	printf("-------\nOPTIONS\n-------\n");

}


Room* triangulate(void) {
	Room* trpntr;
	switch(currentRoom) {
		case LIVING_ROOM:
			trpntr = rooms[LIVING_ROOM];
			break;
		case KITCHEN:
			trpntr = rooms[KITCHEN];
			break;
		case BATH:
			trpntr = rooms[BATH];
			break;
		case BEDROOM:
			trpntr = rooms[BEDROOM];
			break;
		case ENTRANCE:
			trpntr = rooms[ENTRANCE];
			break;
	}

	return trpntr;
}

void initRooms(void) {
	initRoomStrings();
	initRoomEntries();
	currentRoomPntr = rooms[LIVING_ROOM];
}

void initRoomStrings(void) {
	rooms[LIVING_ROOM] = mlcRoom("LIVING ROOM",
		"This room is very large. You are feeling agoraphobic.");
	rooms[KITCHEN] = mlcRoom("KITCHEN",
		"You stand amidst a pile of rubbish.\n Dirty dishes, pots and cullinary decorate the floor.\n You feel dirty just by standing here.");
	rooms[BATH] = mlcRoom("BATH",
		"The bath is roman styled. Next to you there is a pot filled");
	rooms[BEDROOM] = mlcRoom("BEDROOM", "The bed is Queen Sized, niiiice.");
	rooms[ENTRANCE] ) mlcRoom("ENTRANCE", "The door going outside is here. You feel way to cold to go outside though.");
}	

void initRoomEntries(void) {
	rooms[LIVING_ROOM]->entriesCount = 4;

	//init living room
	for(int i = 0; i < rooms[LIVING_ROOM]->entriesCount; ++i) {
		rooms[LIVING_ROOM]->entries[i] = rooms[i+1];
	}
}

Room* mlcRoom(char* name, char* desc) {
	Room *r = malloc(sizeof(Room));
	r->roomName = name;
	r->description = desc;

	return r;
}