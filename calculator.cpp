#include<stdio.h>
#include<ctype.h>
int add_token(char start[100], int tok, int len) {
	start[len] = '\0';
	printf("%s %d %d\n", start, tok, len);
	return 0;
}


int calculator(char *src) {
	int i = 0;
	char temp[100] = "";
	int j = 0;
	int comment_state = 0;
	int star = 0;
	int num = 0;
	char op[100];

	for (i = 0;; ++i) {
		if (comment_state == 1) {
			if (src[i] == '\n') {
				comment_state = 0;
			}

		}
		else if (comment_state == 2) {
			if (src[i] == '*') {
				star = 1;
			}
			else if (star == 1 && src[i] == '/') {
				star = 0;
				comment_state = 0;
			}
		}
		else if (comment_state == 0) {
			if (isalnum(src[i]) != 0) {
				temp[j] = src[i];
				j++;
			}
			else if (isdigit(temp[0]) != 0) {
				if (j != 0) {
					add_token(temp, 2, j);
					num++;
					//printf("%d\n",num);
				}
				j = 0;
				//for(int x=0;x<j;x++){
				//printf("%c",temp[x]);
				//}if(j!=0){
				//printf(" 2 %d\r\n",j);
				//num++;
				//}
				//j=0;
			}
			else if (isalpha(temp[0]) != 0) {
				if (j != 0) {
					add_token(temp, 1, j);
					num++;
					//printf("%d\n",num);
				}
				j = 0;
				//for(int y=0;y<j;y++){
				//printf("%c",temp[y]);
				//}if(j!=0){
				//printf(" 1 %d\r\n",j);
				//num++;
				//}
				//j=0;
			}
			if (src[i] == '/') {
				if (src[i + 1] == '/') {
					comment_state = 1;
					i = i + 1;
				}
				else if (src[i + 1] == '*') {
					comment_state = 2;
					i = i + 1;
				}
				else {//printf("/ 3 1\r\n");
					temp[0] = '/';
					add_token(temp, 3, 1);
					num++;
					//printf("%d\n",num);
				}
			}
			else if (src[i] == '|') {
				if (src[i + 1] == '|') {
					//printf("|| 3 2\r\n");
					temp[0] = '|';
					temp[1] = '|';
					add_token(temp, 3, 2);
					num++;
					//printf("%dn",num);
					i = i + 1;
				}
				else {
					temp[0] = '|';
					add_token(temp, 3, 1);
					//printf("| 3 1\r\n");
					num++;
					//printf("%d\n",num);
				}
			}
			else if (src[i] == '&') {
				if (src[i + 1] == '&') {
					//printf("&& 3 2\r\n");
					temp[0] = '&';
					temp[1] = '&';
					add_token(temp, 3, 2);
					num++;
					//printf("%d\n",num);
					i = i + 1;
				}
				else {//printf("& 3 1\r\n");
					temp[0] = '&';
					add_token(temp, 3, 1);
					num++;
					//printf("%d\n",num);
				}
			}
			else if (src[i] == '=') {
				if (src[i + 1] == '=') {
					//printf("== 3 2\r\n");
					temp[0] = '=';
					temp[1] = '=';
					add_token(temp, 3, 2);
					num++;
					//printf("%d\n",num);
					i = i + 1;
				}
				else {//printf("= 4 1\r\n");
					temp[0] = '=';
					add_token(temp, 4, 1);
					num++;
					//printf("%d\n",num);
				}
			}
			else if (src[i] == '>') {
				if (src[i + 1] == '=') {
					//printf(">= 3 2\r\n");
					temp[0] = '>';
					temp[1] = '=';
					add_token(temp, 3, 2);
					num++;
					//printf("%d\n",num);
					i = i + 1;
				}
				else {//printf("> 3 1\r\n");
					temp[0] = '>';
					add_token(temp, 3, 1);
					num++;
					//printf("%d\n",num);
				}
			}
			else if (src[i] == '<') {
				if (src[i + 1] == '=') {
					//printf("<= 3 2\r\n");
					temp[0] = '<';
					temp[1] = '=';
					add_token(temp, 3, 2);
					num++;
					//printf("%d\n",num);
					i = i + 1;
				}
				else {//printf("< 3 1\r\n");
					temp[0] = '<';
					add_token(temp, 3, 1);
					num++;
					//printf("%d\n",num);
				}
			}
			else if (src[i] == '+' || src[i] == '-' || src[i] == '^' ||
				src[i] == '(' || src[i] == ')' || src[i] == '*' ||
				src[i] == '%') {
				op[0] = src[i];
				add_token(op, 3, 1);
				//printf("%c 3 1\r\n",src[i]);
				num++;
				//printf("%d\n",num);
			}
			else if (src[i] == '\0') {
				//printf("%d\n",num);
				break;
			}
			else continue;

		}
	}
	return num;
}

int main() {
	char *tst1 = "a = 3+3 *588 foo";
	int tst1_n_tokens = calculator(tst1);
}
