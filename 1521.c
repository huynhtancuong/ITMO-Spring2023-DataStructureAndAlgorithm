#include <stdio.h>
#include <stdlib.h>

#define maxN 100000

typedef struct node {
    int data;
    int value;
} node;

node a[maxN];
node st[4 * maxN];

void build(int id, int l, int r) {
    // if this is a leaf
    if (l == r) {
        st[id] = a[l];
        return;
    }

    // build the 2 child
    int mid = (l+r) >> 1;
    build(2*id, l, mid);
    build(2*id+1, mid+1, r);

    // update the value of current node
    st[id].value = st[2*id].value + st[2*id+1].value;
}

int query(int pos, int id, int l, int r) {
    // if this is a leaf
    if (l == r) {
        return st[id].data;
    }

    // if pos belong to left child
    if (pos <= st[2*id].value) {
        int mid = (l+r) >> 1;
        return query(pos, 2*id, l, mid);
    }
    // if pos belong to right child
    else {
        int mid = (l+r) >> 1;
        return query(pos-st[2*id].value, 2*id+1, mid+1, r);
    }
}

void delete(int pos, int id, int l, int r) {
    // if this is a leaf
    if (l == r) {
        st[id].value = 0;
        return;
    }

    // if pos belong to left child
    if (pos <= st[2*id].value) {
        int mid = (l+r) >> 1;
        delete(pos, 2*id, l, mid);
    }
    // if pos belong to right child
    else {
        int mid = (l+r) >> 1;
        delete(pos-st[2*id].value, 2*id+1, mid+1, r);
    }

    // update the value of current node
    st[id].value = st[2*id].value + st[2*id+1].value;

}

int main() {

	int n, k;
	scanf("%d %d", &n, &k);
    for (int i = 1; i<=n; i++) {
        a[i].data = i;
        a[i].value = 1;
    }

    build(1, 1, n);

    int pos_to_remove = 1;
    for (int i = 1; i<=n; i++) {

        pos_to_remove = (pos_to_remove - 1 + k) % st[1].value;
        if (pos_to_remove == 0) pos_to_remove = st[1].value;
        printf("%d ", query(pos_to_remove, 1, 1, n));
        delete(pos_to_remove, 1, 1, n);

    }
	
	return 0;
}
