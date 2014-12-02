# Build

The proposed way of build (out-of-tree build)
1. create build directory
2. Run cmake from this directory pointing to root CMakeLists.txt
3. Run make

# Graph generator

Usage:

./graph-generator <amount-of-vertexes> <amount-of-edges>

for e.g. : ./graph-generator 10 20

Generator will save graphs (if succeeded) to files named

graph<amount-of-vertexes>v_<amount-of-edges>e.txt

for e.g. : graph10v_20e.txt
