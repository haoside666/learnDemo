#include <map>
#include <cmath>
#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

int flag;

void print() {
	if (flag) {
		putchar(' ');
	}
	flag = 1;

	return;
}
int main() {

	char str[110], p[110];

	cin >> str;
	int i, t, len;
	t = 0; 
	len = strlen(str);
	for (int i = 0; i < len; i++) {
		if ((str[i] == '+' || str[i] == '-') && (!i || str[i - 1] == '(') || (str[i] >= '0' && str[i] <= '9')) {
			print();

			if (str[i] != '+') {
				cout << str[i];
			}

			while (str[i + 1] == '.' || (str[i + 1] >= '0' && str[i + 1] <= '9')) {
				cout << str[++i];
			}
		}
		else {
			if (str[i] == ')') {
				while (t && p[t - 1] != '(') {
					print();
					cout << p[--t];
				}

				if (t) {
					--t;
				}
			}
			else {
				if (!t) {
					p[t++] = str[i];
					continue;
				}
				
				while (t && p[t - 1] != '(') {
					if (str[i] == '(' || ((str[i] == '*' || str[i] == '/') && (p[t - 1] == '-' || p[t - 1] == '+'))) {
						break;
					}

					print();
					cout << p[--t];
				}

				p[t++] = str[i];
			}
		}
	}
	while (t) {
		print();
		if (p[t - 1] != '(') {
			cout << p[t - 1];
		}
		t--;
	}

	//system("pause");

	return 0;
}
