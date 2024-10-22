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
