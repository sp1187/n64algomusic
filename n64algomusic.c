#include <stdio.h>
#include <stdint.h>
#include <libdragon.h>

inline uint8_t function(int t){
	//return ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6);
	return (t*9&t>>4|t*5&t>>7|t*3&t/1024)-1;
}

#define U8_TO_S8(x) ((x) ^ 0x80)

int main(){
	init_interrupts();
	audio_init(8000,1);
	console_init();
	
	printf("Algorithmic music demo");
	console_render();

	int buflen = audio_get_buffer_length();
	int16_t buffer[2 * buflen];

	int t = 0;
	for(;;){
		for(int i = 0; i < buflen; i++){
			int8_t val = U8_TO_S8(function(t++));
			buffer[i * 2] = buffer[i * 2 + 1] = (val << 8);
		}
		audio_write(buffer);
	}
}
