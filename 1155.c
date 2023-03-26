#include <stdio.h>


// The program seem to be ok, but I don't know why it can't pass test 1 :((

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


/////////////////////


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

char subset1[] = {'A', 'C', 'F', 'H'};
char subset2[] = {'B', 'D', 'E', 'G'};

int cameras[8];

BufferredOuput bufferredOuput;


void subtract(char a, int n) {
	cameras[a-'A']-=n;
}

void add(char a, int n) {
	cameras[a-'A']+=n;
}

int isIn(char c, char arr[]) {
	size_t size = 4;
	for (size_t i = 0; i<size; i++) {
		if (c == arr[i]) return 1;
	}
	return 0;
}

int isConnected(char a, char b) {
	return connection[a-'A'][b-'A'];
}

int isSameSubSet(char a, char b) {
	if (isIn(a, subset1) && isIn(b, subset1)) return 1;
	if (isIn(a, subset2) && isIn(b, subset2)) return 1;
	return 0;
}

void print_instruction(char a, char b, int sign) {
	char tmp[5] = "AB+ \n";
	tmp[0] = a;
	tmp[1] = b;
	if (sign) {
		// printf("%c%c+ \n", a, b);
		tmp[2] = '+';
		BufferredOutput_write(&bufferredOuput, tmp, 5);
	}
	else {
		// printf("%c%c- \n", a, b);
		tmp[2] = '-';
		BufferredOutput_write(&bufferredOuput, tmp, 5);
	}
}

void move(char source, char destination, char middle) {

	if (!isSameSubSet(source, destination)) return;
	if (!(isConnected(source, middle) && isConnected(destination, middle))) return;

	print_instruction(destination, middle, 1);
	print_instruction(source, middle, 0);
	add(destination, 1);
	subtract(source, 1);
}

void moveInSameSubset(char source, char destination, int n) {
	if (!isSameSubSet(source, destination)) return;
	char middle;
	// find the middle
	for (middle = 'A'; middle<='H'; middle++) {
		if (isConnected(source, middle) && isConnected(destination, middle)) {
			break;
		}
	}
	// move
	for (int i = 0; i< n; i++)
		move(source, destination, middle);
}


void substract_pair(char a, char b, int n) {
	if (isConnected(a, b)) {
		for (int i = 0; i<n; i++) {
			print_instruction(a, b, 0);
		}
		cameras[a-'A']--;
		cameras[b-'A']--;
	}
}

void readInput() {
	for (size_t i = 0; i<8; i++) scanf("%d", &cameras[i]);
}

int getValue(char a) {
	return cameras[a-'A'];
}


void minimize() {
	for (char i = 'A'; i<='H'; i++) {
		for (char j = 'A'; j<='H'; j++) {
			if ((getValue(i) > 0) && (getValue(j) > 0) && isConnected(i, j)) {
				int n = getValue(i) < getValue(j) ? getValue(i) : getValue(j); // get the min value
				substract_pair(i, j, n);
			}
		}
	}
}

// move all to the first element (A) of subset1
void movetoA() {
	for (size_t i = 1; i<4; i++) {
		moveInSameSubset(subset1[i], subset1[0], getValue(subset1[i]));
	}
}

// move all to the first element (B) of subset2
void movetoB() {
	for (size_t i = 1; i<4; i++) {
		moveInSameSubset(subset2[i], subset2[0], getValue(subset2[i]));
	}
}

int isPossible() {
	if (getValue('A') + getValue('C') + getValue('F') + getValue('H') == getValue('B') + getValue('D') + getValue('E') + getValue('G'))
		return 1;
	return 0;
}

int main() {
	// printf("%d", isConnected('E', 'A'));
	// printf("%d", isIn('E', subset1));
	// move('H', 'A', 'F');
	// substract('A', 'C', 5);

	bufferredOuput = BufferredOuput_init();


	readInput();
	if (!isPossible()) {
		printf("IMPOSSIBLE");
		return 0;
	}

	minimize();
	// for (size_t i = 0; i<8; i++) printf("%d ", cameras[i]);
	// printf("\n");

	movetoA();
	// for (size_t i = 0; i<8; i++) printf("%d ", cameras[i]);
	// printf("\n");

	movetoB();
	// for (size_t i = 0; i<8; i++) printf("%d ", cameras[i]);
	// printf("\n");

	minimize();
	// for (size_t i = 0; i<8; i++) printf("%d ", cameras[i]);

	// for (size_t i = 0; i<8; i++) printf("%d ", cameras[i]);

	BufferredOutput_delete_newline(&bufferredOuput);

	BufferredOutput_delete_space(&bufferredOuput);

	BufferredOutput_print(&bufferredOuput);

	return 0;
}
