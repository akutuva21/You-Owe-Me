import names
import random

generatedFile = open('./hugetransactions.txt', 'w')

names_list = []

def add():
    name = names.get_first_name()
    if name not in names_list:
        names_list.append(names.get_first_name())
    else:
        add()

for i in range(0, 1000):
    add()

for i in range(0, 100000):
    value = str(round(random.uniform(1, 100), 2))
    randomPerson1 = names_list[random.randint(0, 999)]
    randomPerson2 = names_list[random.randint(0, 999)]

    generatedFile.write(randomPerson1 + ' ' + randomPerson2 + ' ' + value + '\n')
