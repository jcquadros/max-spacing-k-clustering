import os
import random
import string

def generate_random_name(length):
    return ''.join(random.choices(string.ascii_uppercase, k=length))

def generate_random_double(min_value, max_value):
    return round(random.uniform(0.0, 10.0), 1)

def generate_vertices_file(name_length, dimension, num_vertices):
    folder_name = "./instancias/geradas"
    
    filename = f"vertices_{name_length}_{dimension}_{num_vertices}.txt"
    filepath = os.path.join(folder_name, filename)

    with open(filepath, 'w') as f:
        for _ in range(num_vertices):
            name = generate_random_name(name_length)
            position = [generate_random_double(0.0, 10.0) for _ in range(dimension)]
            f.write(f"{name}," + ','.join(map(str, position)) + "\n")

    print(f"Arquivo {filepath} gerado com sucesso.")

if __name__ == "__main__":
    name_length = 30
    dimension = 5
    num_vertices = 25000
    
    generate_vertices_file(name_length, dimension, num_vertices)
