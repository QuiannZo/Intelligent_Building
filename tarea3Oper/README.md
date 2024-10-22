# Compilación
```
g++ server.cpp -o server -lssl -lcrypto
```
luego
```
g++ client.cpp -o client
```
## Para la parte de autenticar
Se ejecuta en una terminal el ./server, y en otra terminal el ./client. En esa terminal de client, se debe poner la palabra autenticar, seguido de username y el password 
```
autenticar username02 password02
```

## Para guardar un Archivo
Se ejecuta en una terminal el ./server, y en otra terminal el ./client. En esa terminal de client, se debe poner la palabra guardarArchivo seguido del nombre del mismo.
```
guardarArchivo ./usersData.txt
```

## Para crear y eliminar un Archivo
Se ejecuta en una terminal el ./server, y en otra terminal el ./client. En esa terminal de client.
```
[comando] [nombreArchivo]

crearArchivo archivo.txt

eliminarArchivo archivo.txt
```
