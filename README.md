Files:

1. Dictionary.h:
    header file which is used to declare functions and construct the ADTs Node and Dictionary
2. Dictionary.cpp:
    C++ source file which is used to define the declared functions and incoporates the Dictionary and Node ADT
3. DictionaryTest.cpp 
    C++ source file which is used to determine if defined functions in Dictionary.cpp are working as expected
4. Order.cpp:
    C++ source file which takes two command line arguments (input file and output file). The input file determines the composition of the dictionary where each line is a key and the corresponding line number is the value. Keys and values are represented in outfile file first inorder and secondly pre-order. 
5. Makefile:
    makefile which compiles code and creates executables DictionaryTest and Order. Can also check for memory errors in Order and DictionaryTest with command make DictionaryCheck and make OrderCheck. 
