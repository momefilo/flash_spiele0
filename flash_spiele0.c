// momefilo Desing
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "./ili9341/ili9341.h"
#include "./graphics/entry0.h"

uint8_t *Entry_FlashContent;
uint SectorSum = 19;
uint Flashoffset = 256 * 1024;
uint8_t *getEntry(){ return &Entry_FlashContent[0]; }

char *text = "Start";
uint16_t pos[] = {0,0};

void paintHeader(){
	uint8_t *fl = getEntry();
	int fehlersum = 0;
	for(int i=0; i<ENTRY0_LEN; i++) if(ENTRY0[i] != fl[i]) fehlersum++;
	char text[15];
	sprintf(text,"Fehler: %d\n",fehlersum);
	uint16_t pos[] = {0,20};
	writeText16x16(pos,text,15,false,false);
	sleep_ms(3000);
	uint16_t area[] = {0, 0, 239, 159};
//	drawRect(area, ENTRY0);
	drawRect(area, getEntry());
}


void entry_flashInit(){
	pos[1] = 20;
	int pagesum = ENTRY0_LEN / 256;
	SectorSum = 19;
	uint offset = 0;
	Entry_FlashContent = (uint8_t *) (XIP_BASE + Flashoffset);
	uint32_t flags = save_and_disable_interrupts();

	flash_range_erase(Flashoffset + offset, SectorSum * FLASH_SECTOR_SIZE);
	writeText16x16(pos, text, 5 ,false,false);
	flash_range_program(Flashoffset + offset, ENTRY0, pagesum * FLASH_PAGE_SIZE);
	restore_interrupts(flags);
}

int main(){
	stdio_init_all();
	sleep_ms(100);
	ili9341_init();
	setOrientation(VERTICAL);
	writeText16x16(pos, text, 5 ,false,false);
	entry_flashInit();
	pos[1] = 40;
	text = "Ende";
	writeText16x16(pos, text, 5 ,false,false);
	//debug
	paintHeader();
	//end debug
}
