#include <stdio.h>


/// This is for outputing 
typedef struct {
	char buffer[10000];
	int pointer;
} BufferredOuput;

BufferredOuput BufferredOuput_init() {
	BufferredOuput bufferredOuput;
	bufferredOuput.pointer = 0;
	return bufferredOuput;
}

void BufferredOutput_write(BufferredOuput *bufferredOuput, char *str, size_t size) {
	for (size_t i = 0; i<size; i++) {
		bufferredOuput->buffer[bufferredOuput->pointer++] = str[i];
	}
	bufferredOuput->buffer[bufferredOuput->pointer] = '\0';
}

void BufferredOutput_print(BufferredOuput *bufferredOuput) {
	printf("%s", bufferredOuput->buffer);
}

void BufferredOutput_delete_newline(BufferredOuput *bufferredOuput) {
	if (bufferredOuput->buffer[bufferredOuput->pointer-1] == '\n') {
		bufferredOuput->buffer[--bufferredOuput->pointer] = '\0';
	}
}

void BufferredOutput_delete_space(BufferredOuput *bufferredOuput) {
	if (bufferredOuput->buffer[bufferredOuput->pointer-1] == ' ') {
		bufferredOuput->buffer[--bufferredOuput->pointer] = '\0';
	}
}
////////////////////////

typedef struct {
    char ch; // charater
    int w;	 // weight
} Vercites;

BufferredOuput bufferredOuput;

int connection[8][8] = {
//   A, B, C, D, E, F, G, H
	{0, 1, 0, 1, 1, 0, 0, 0},// A
	{1, 0, 1, 0, 0, 1, 0, 0},// B
	{0, 1, 0, 1, 0, 0, 1, 0},// C
	{1, 0, 1, 0, 0, 0, 0, 1},// D
	{1, 0, 0, 0, 0, 1, 0, 1},// E
	{0, 1, 0, 0, 1, 0, 1, 0},// F
	{0, 0, 1, 0, 0, 1, 0, 1},// G
	{0, 0, 0, 1, 1, 0, 1, 0} // H
};

void record(Vercites a, Vercites b, char sign) {
	char template[5] = "AB+ \n";
	template[0] = a.ch;
	template[1] = b.ch;
	template[2] = sign;
	BufferredOutput_write(&bufferredOuput, template, 5);
}

int isConnected(Vercites a, Vercites b) {
	return connection[a.ch-'A'][b.ch-'A'];
}

void move_weight(Vercites *target, Vercites *middle, Vercites *source) {
	while (source->w > 0) {
		record(*target, *middle, '+');
		record(*source, *middle, '-');
		source->w--;
		target->w++;
	}
}

void subtract_pair(Vercites *x, Vercites *y){
    while(x->w && y->w){
        record(*x,*y,'-');
        x->w--;
        y->w--;
    }
}

int main() {
	Vercites a = {'A', 0}, b = {'B', 0}, c = {'C', 0}, d = {'D', 0}, e = {'E', 0}, f = {'F', 0}, g = {'G', 0}, h = {'H', 0};
	scanf("%d %d %d %d %d %d %d %d", &a.w, &b.w, &c.w, &d.w, &e.w, &f.w, &g.w, &h.w);

	// check if it is possible
	if(a.w + f.w + c.w + h.w != b.w + d.w + e.w + g.w ){
        printf("IMPOSSIBLE");
        return 0;
    }

	Vercites cube[8] = {a, b, c, d, e, f, g, h};

	// minimize
	for(int i = 0; i < 8; i++){
        for(int j = 0;j < 8; j++){
            if(isConnected(cube[i],cube[j])){
                subtract_pair(&cube[i], &cube[j]);
            }
        }
    }

	// all -> A
    // F - B - A
    if(cube[5].w)	move_weight(&cube[0], &cube[1], &cube[5]); 
    // H - E - A
    if(cube[7].w) 	move_weight(&cube[0], &cube[4], &cube[7]);
    // C - B - A
    if(cube[2].w) 	move_weight(&cube[0], &cube[1], &cube[2]);

    // All -> B
    // D - C - B
    if(cube[3].w) 	move_weight(&cube[1], &cube[2], &cube[3]);
    // E - A - B
    if(cube[4].w) 	move_weight(&cube[1], &cube[0], &cube[4]); 
    // G - C - B
    if(cube[6].w) 	move_weight(&cube[1], &cube[2], &cube[6]);

	subtract_pair(&cube[0], &cube[1]);

	BufferredOutput_delete_newline(&bufferredOuput);

	BufferredOutput_delete_space(&bufferredOuput);

	BufferredOutput_print(&bufferredOuput);
	
	return 0;
}
