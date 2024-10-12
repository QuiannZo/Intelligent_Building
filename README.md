# FileSystem_Oper

This program is in C++ and it applies a File Allocation Table.

# Authors
Ximena Marín Sánchez C14448
Aron Hidalgo Gómez C23880
Quiann Zolfaghari Calderón C18723
Nathalie Alfaro Quesada B90221
José Pablo Mora Cubillo B75044

# How to execute
First, install `openssl`:
```
sudo apt install libssl-dev
```

To compile and execute this program the Compiler is C++, and you can use the Compiler of your preference, for example GCC.

```
g++ main.cpp FAT.cpp Usuario.cpp Authenticator.cpp HashHandler.cpp -o main -lssl -lcrypto
```

```
./main
```