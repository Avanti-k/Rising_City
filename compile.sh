echo "Running script"
g++ -I include/ -c main.cpp
g++ -I include/ -c src/Building.cpp
g++ -I include/ -c src/MinHeap.cpp
g++ -I include/ -c src/RBTree.cpp
g++ -o main main.o Building.o RBTree.o MinHeap.o 
./main > op.txt

echo "Ended script"

