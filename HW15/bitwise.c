#include <stdio.h>
#include <stdlib.h>

typedef struct _tn {
	struct _tn *left;
	struct _tn *right;
	unsigned char data;
} TreeNode;

void printB(unsigned char byte) {
	fprintf(stdout, "%c%c%c%c\t%c%c%c%c\t", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0'));
}

void bitwise(TreeNode *tn, int *offset, unsigned char *current) {
	const unsigned char MASK = 0xFF;
	if (tn) {
		if (tn -> left || tn -> right) {
			(*current) <<= 1;
			(*offset)++;
			if ((*offset) == 8) {
				printB(*current);
				*current = 0x0;
				*offset = 0;
			}
			bitwise(tn -> left, offset, current);
			bitwise(tn -> right, offset, current);
		} else {
			(*current) <<= 1;
			(*current) = (*current) | 0x1;
			(*offset)++;
			if ((*offset) == 8) {
				printB(*current);
				printB(tn -> data);
				*current = 0x0;
				*offset = 0;
			} else {
				(*current) = (*current << 8 - (*offset)) | (tn -> data >> (*offset));
				printB(*current);
				(*current) = tn -> data << (8 - (*offset));
				(*current) = (*current) >> (8 - (*offset));
			}
		}
	}
}

static void preorder(TreeNode *tn) {
	if (tn) {
		if (tn -> left || tn -> right) {
			fprintf(stdout, "0");
			preorder(tn -> left);
			preorder(tn -> right);
		} else {
			fprintf(stdout, "%c", tn -> data);
		}
	}
}

int main(int argc, char *argv[]) {
	TreeNode *tn = malloc(sizeof(TreeNode));
	tn -> left = malloc(sizeof(TreeNode));
	tn -> left -> left = malloc(sizeof(TreeNode));
	tn -> left -> left -> data = '6';
	tn -> left -> left -> left = NULL;
	tn -> left -> left -> right = NULL;
	tn -> left -> right = malloc(sizeof(TreeNode));
	tn -> left -> right -> left = malloc(sizeof(TreeNode));
	tn -> left -> right -> left -> data = '\\';
	tn -> left -> right -> left -> left = NULL;
	tn -> left -> right -> left -> right = NULL;
	tn -> left -> right -> right = NULL;
	
	tn -> right = malloc(sizeof(TreeNode));
	tn -> right -> left = malloc(sizeof(TreeNode));
	tn -> right -> left -> data = 'n';
	tn -> right -> left -> left = NULL;
	tn -> right -> left -> right = NULL;
	tn -> right -> right = malloc(sizeof(TreeNode));
	tn -> right -> right -> left = malloc(sizeof(TreeNode));
	tn -> right -> right -> left -> data = '{';
	tn -> right -> right -> left -> left = NULL;
	tn -> right -> right -> left -> right = NULL;
	
	tn -> right -> right -> right = NULL;
	
	unsigned char current = 0x0;
	int offset = 0;
	bitwise(tn, &offset, &current);
	if (offset != 0) {
		printB(current << 8 - offset);
	}
}

//0010 0110
//1100 1010
//1110 0010
//1101 1100
//1011 1101
//10 000000