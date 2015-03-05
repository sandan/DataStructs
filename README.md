# DataStructs


things learned:
-if a header file t has
   include "path/to/header.h" 
 then the header file for the implementation (.c) files just needs 
 to include the t header file and not the "header.h" one.

-there must be some orderly naming convention in header files or else
 their declaration clobbers each other and you get multiple definition
 errors on compilation... There must be some way to define an interface in C
 and have multiple implementations with diffrent underlying structs
