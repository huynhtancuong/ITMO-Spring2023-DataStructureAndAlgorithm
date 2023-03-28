#include <stdio.h>
#include <string.h>

// Time limit exceeded on test #9 :((

#define LOOKUP_SIZE 1000001

struct lookup_table {
	char arr[LOOKUP_SIZE];
	int num[LOOKUP_SIZE];
};

struct character {
	char ch;
	int num;
};


struct lookup_table last, first;
int n;

void fill_lookup_table_num(struct lookup_table *table) {
	int count_table[256];
	memset(count_table, 0, 256*sizeof(int));
	for (int i = 0; table->arr[i]; i++) {
		count_table[table->arr[i]]++;
		table->num[i] = count_table[table->arr[i]];
	}
}
// return the index
int find_index(struct lookup_table *table, char ch, int num) {
	for (int i = 0; i<LOOKUP_SIZE; i++) {
		if (((table->arr[i] == ch)) && (table->num[i] == num) )
			return i;
	}
	return -1;
}

int main() {

	int count_table[256];
	memset(count_table, 0, 256*sizeof(int));

	scanf("%d %s", &n, last.arr);
	for (int i = 0; last.arr[i]; i++) {
		count_table[last.arr[i]]++;
	}
	n--;

	// build the first table
	int k = 0;
	for (int i = 0; i<256; i++) {
		while (count_table[i]) {
			first.arr[k++] = i;
			count_table[i]--;
		}
	}
	
	fill_lookup_table_num(&first);
	fill_lookup_table_num(&last);
	
	char output[LOOKUP_SIZE];
	k = 0;
	memset(output, 0, LOOKUP_SIZE*sizeof(char));

	int string_length = strlen(first.arr);

	struct character begin_charater = { .ch=first.arr[n], .num=first.num[n] };
	struct character iterator = begin_charater;
	output[k++] = first.arr[n];
	for (int i = 1; i<string_length; i++) {
		int index = find_index(&last, iterator.ch, iterator.num);
		output[k++] = first.arr[index];
		iterator.ch = first.arr[index];
		iterator.num = first.num[index];
	}

	printf("%s", output);

	return 0;
}
