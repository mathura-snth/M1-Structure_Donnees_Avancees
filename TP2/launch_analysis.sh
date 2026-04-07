RED='\033[0;31m'
NC='\033[0m' # No Color


# Compilation et exécution en C:
echo "${RED} Compilation du code source en C ${NC}"
cd C/

make

echo "${RED} Exécution des benchmarks en C ${NC}"
./arraylist_analysis

echo "${RED} Nettoyage ${NC}"
make clean

cd ..

# Compilation et exécution en C++:
echo "${RED} Compilation du code source en C++ ${NC}"
cd CPP/

make

echo "${RED} Exécution des benchmarks en C++ ${NC}"
./arraylist_analysis

echo "${RED} Nettoyage ${NC}"
make clean

cd ..

# Compilation et exécution en Java:

echo "${RED} Compilation du code source en Java ${NC}"
cd Java

javac *

echo "${RED} Exécution des benchmarks en Java ${NC}"
java Main

echo "${RED} Nettoyage ${NC}"
rm *.class

cd ..

# Exécution en Python

echo "${RED} Compilation du code source en Python ${NC}"
cd Python

echo "${RED} Exécution des benchmarks en Python ${NC}"
python main.py

cd ..

# Observation des résultats
### Dans le répertoire plots, lisez le contenu du fichier plot_result

cd plots
more plot_result

### puis lancez ce script avec gnuplot

gnuplot plot_result


