# Etapa III PI

# Compilación
**Notar que la compilación se debe realizar desde la carpeta `etapa3PI`, los archivos que se encuentran afuera de esta carpeta son necesarios para el funcionamiento el proceso de compilación.**

# Nodo cliente3
```
g++ client3.cpp ClientNode.cpp Client.cpp Log.cpp FAT.cpp -o client -lssl -lcrypto
```

## Nodo intermediario
```
g++ main_intermediary.cpp Intermediary.cpp Node.cpp Client.cpp Log.cpp FAT.cpp -o intermediary
```

## Nodo autenticación de usuarios
```
g++ main_userNode.cpp Node.cpp Client.cpp FAT.cpp Log.cpp HashHandler.cpp -o userNode -lssl -lcrypto
```

## Nodo de datos
```
g++ main_dataNode.cpp DataNode.cpp Node.cpp Client.cpp Log.cpp FAT.cpp -o datanode
``` 

## Nodo Backup
```
g++ main_backup.cpp Backup.cpp Node.cpp Client.cpp Log.cpp FAT.cpp -o backup -pthread
``` 