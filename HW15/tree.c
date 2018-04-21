#include "tree.h"

#ifndef USIGN_TO_BIN
// function to create binary values from the input char values
char * UnSig2Bin(unsigned char value) {
    char *result = malloc(sizeof(char) * 9);
    unsigned char MASK = 0x80;
    for (int i = 0; i < 8; i++) {
      result[i] = (value & (MASK >> i)) > 0 ? '1' : '0';
    }
    result[8] = '\0';
    return result;
}

#endif

#ifndef WRITE_BINARY

// WriteInOrderBinary takes root and file * as input
// and creates binary representation of the tree as specified in the example
int WritePreOrderBinary(TreeNode * root, FILE *outptr){
  if (!root) return EXIT_SUCCESS;
  if (root -> leftChild == NULL && root -> rightChild == NULL) {
    fputc('1', outptr);
    printf("1");
    char *temp = UnSig2Bin(root -> data);
    fprintf(outptr, "%s", temp);
    printf("%s", temp);
    free(temp);
  } else {
      fputc('0', outptr);
      printf("0");
      WritePreOrderBinary(root -> leftChild, outptr);
      WritePreOrderBinary(root -> rightChild, outptr);
  }
  return 1;
}

int CreateBinaryFromTree(TreeNode * root, const char *outfile){
  FILE *tmp = tmpfile();
  WritePreOrderBinary(root, tmp);
  fputc('0', tmp);
  //int size = ftell(tmp) / sizeof(char);
  fseek(tmp, 0, SEEK_SET);

  return 1;
}

#endif





#ifndef CLEAN_TREE

void CleanTree(TreeNode * root){
  if(!root)  return;
  CleanTree(root -> leftChild);
  CleanTree(root -> rightChild);
  free(root);
}
#endif





#ifndef BINARY_SEARCH_TREE

int IntCompare(const void * val1, const void * val2){
  return (*(unsigned char*)val1 - *(unsigned char*)val2);
}

TreeNode * CreateBinarySearchTree(long randomSeed, long numNodes){
  unsigned char * binArray = malloc(sizeof(unsigned char)*numNodes);
  if(binArray == NULL){
    printf("Memory allocation to array failed\n" );
    return NULL;
  }
  srand(randomSeed);
  // allocate values to array
  for(int index = 0; index < numNodes ; index++){
    binArray[index] = rand() % 256;
  }
  // sort the array
  qsort(binArray, numNodes, sizeof(unsigned char), IntCompare);

  // create bst from the sorted array
  TreeNode * root = CreateBST(binArray, 0, numNodes-1);
  free(binArray);
  return root;

}
// TreeNode *CreateBSTHelper()
TreeNode* CreateTreeNode(unsigned char value){
  TreeNode *newNode = malloc(sizeof(TreeNode));
  newNode->data = value;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  return newNode;
}

TreeNode *CreateBST(unsigned char *sortedArray, int start , int end){
  // int len = sizeof(sortedArray)/sizeof(int);
  if(start > end) return NULL;
  int mid = (start+end)/2;
  TreeNode *newNode = CreateTreeNode(sortedArray[mid]);
  newNode->leftChild = CreateBST(sortedArray, start, mid -1);
  newNode->rightChild = CreateBST(sortedArray, mid +1, end);
  return newNode;

}
#endif
