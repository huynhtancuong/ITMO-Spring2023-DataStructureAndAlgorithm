#include <stdio.h>

typedef struct {
	char buffer[100];
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

int main() {

	BufferredOuput bufferredOuput = BufferredOuput_init();

	BufferredOutput_write(&bufferredOuput, "20 \n", 4);
	
	BufferredOutput_delete_newline(&bufferredOuput);

	BufferredOutput_delete_space(&bufferredOuput);

	BufferredOutput_write(&bufferredOuput, "30\n", 3);

	BufferredOutput_print(&bufferredOuput);
	
	return 0;
}
