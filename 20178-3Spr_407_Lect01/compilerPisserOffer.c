void compilerPisserOffer(const int* ciPtr)
{
  int* iPtr = ciPtr; // Happy or sad?
  int array[5] = {1,2,3,4,5};

  ciPtr = array; // Happy or sad?
  ciPtr++; // Happy or sad?
  (*ciPtr)++; // Happy or sad?
}
