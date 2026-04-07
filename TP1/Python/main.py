# -- coding: utf-8 --
import time
import sys

from analyzer import Analyzer

# Tableau dynamique.
a = []
# Analyse du temps pris par les operations.
time_analysis = Analyzer();
# Analyse de la mémoire gaspillée à un instant t.
memory_analysis = Analyzer();
# Analyse du nombre de copies effectuées.
copy_analysis = Analyzer();


# Taille supposée de l'en-tête d'une list en Python
__list_header_size__ = 64
# Taille supposée d'une entrée dans une list en Python
__list_entry_size__ = 8

wasted_memory = sys.getsizeof(a)-__list_header_size__
prev_sizeof_a = sys.getsizeof(a)

for i in range(1000000):
    before = time.time()
    a.append(i)
    after = time.time()

    # Enregistrement du temps pris par l'operation
    time_analysis.append((after - before)*10**9)
   
    # Enregistrement de l'espace mémoire gaspillé à un instant donné
    wasted_memory = sys.getsizeof(a)-__list_header_size__ - __list_entry_size__*(i+1)

    # Enregistrement du nombre de copie effectuées par l'opération
    # S'il n'y avait pas d'espace gaspillé à l'étape précédente, 
    # alors une réallocation a eu lieu à cette étape.
    if sys.getsizeof(a) > prev_sizeof_a: 
        copy_analysis.append(i+1)
    else:
        copy_analysis.append(1)
    prev_sizeof_a = sys.getsizeof(a)
    memory_analysis.append(wasted_memory)

# Affichage de quelques statistiques sur l'experience.
sys.stderr.write("Total cost : " + str(time_analysis.get_total_cost())+"\n")
sys.stderr.write("Average cost : " + str(time_analysis.get_average_cost())+"\n")
sys.stderr.write("Variance :" + str(time_analysis.get_variance())+"\n")
sys.stderr.write("Standard deviation :" + str(time_analysis.get_standard_deviation())+"\n")

# Sauvegarde les donnees de l'experience.
time_analysis.save_values("../plots/dynamic_array_time_python_alpha_2.plot")
memory_analysis.save_values("../plots/dynamic_array_memory_python_alpha_2.plot")
copy_analysis.save_values("../plots/dynamic_array_copy_python_alpha_2.plot")

