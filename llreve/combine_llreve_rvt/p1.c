void __CPROVER_assume(_Bool);
int a[25];

void bubble_sort(int *a, int sz) {
    for (int i = sz - 1; i > 0;) {
        for (int j = 0; j < i;) {
            if (*(a + j) < *(a + j + 1)) {
                int t = *(a + j);
                *(a + j) = *(a + j + 1);
                *(a + j + 1) = t;
            }
            j = j + 1;
        }
        i = i - 1;
    }
}

int shitty_function(int *a, int n) {
    int i = n;
    int j = 0;
    while ((i >= 0)) {
        bubble_sort(a + 5 * j, 5);
        i = i - 1;
        j++;
    }
    return j;
}

int main() {
    shitty_function(a, 25);
    return 0;
}
