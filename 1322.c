#include <stdio.h>
#include <string.h>

// Passed all the tests

#define LOOKUP_SIZE 100001

struct character {
	int ch;
	int num;
};


struct character last[LOOKUP_SIZE], first[LOOKUP_SIZE];
int n;

void fill_lookup_table_num(struct character table[]) {
	int count_table[256];
	memset(count_table, 0, 256*sizeof(int));
	for (int i = 0; table[i].ch; i++) {
		count_table[(int)table[i].ch]++;
		table[i].num = count_table[(int)table[i].ch];
	}
}

int character_cmp(struct character a, struct character b) {
	if (a.ch == b.ch && a.num == b.num) return 0;
	if (a.ch > b.ch) return 1;
	if (b.ch > a.ch) return -1;
	if (a.ch == b.ch) {
		if (a.num > b.num) return 1;
		return -1;
	}
	return -1;
}

int find_index_binary_search(struct character table[], struct character ch, int l, int r) {
	if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (character_cmp(table[mid], ch) == 0)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (character_cmp(table[mid], ch) == 1)
            return find_index_binary_search(table, ch, l, mid - 1);
 
        // Else the element can only be present
        // in right subarray
        return find_index_binary_search(table, ch, mid + 1, r);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}

int main() {

	int count_table[256];
	memset(count_table, 0, 256*sizeof(int));

	char tmp[LOOKUP_SIZE];
	scanf("%d %s", &n, tmp);
	for (int i = 0; tmp[i]; i++) {
		last[i].ch = tmp[i];
		count_table[(int)tmp[i]]++;
	}
	n--;

	// build the first table
	int k = 0;
	for (int i = 0; i<256; i++) {
		while (count_table[i]) {
			first[k++].ch = i;
			count_table[i]--;
		}
	}
	
	fill_lookup_table_num(first);
	fill_lookup_table_num(last);
	
	char output[LOOKUP_SIZE];
	k = 0;
	memset(output, 0, LOOKUP_SIZE*sizeof(char));

	int string_length = strlen(tmp);

	output[k++] = last[n].ch;
	struct character iterator = last[n];
	for (int i = 1; i<string_length; i++) {
		int index = find_index_binary_search(first, iterator, 0, string_length-1);
		output[k++] = last[index].ch;
		iterator = last[index];
	}

	for (int i = string_length-1; i>=0; i--) {
		printf("%c", output[i]);
	}

	return 0;
}
