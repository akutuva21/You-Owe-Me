import names
import random

generatedFile = open('./hugetransactions.txt', 'w')

names_list = []
people_totals = {}

def add():
    name = names.get_first_name()
    if name not in names_list:
        names_list.append(name)
        people_totals[name] = 0
    else:
        add()

for i in range(0, 1000):
    add()

for i in range(0, 100000):
    value = str(round(random.uniform(1, 100), 2))
    randomPerson1 = names_list[random.randint(0, 999)]
    randomPerson2 = names_list[random.randint(0, 999)]
    people_totals[randomPerson1] = round(people_totals[randomPerson1] - float(value), 2)
    people_totals[randomPerson2] = round(people_totals[randomPerson2] + float(value), 2)

    generatedFile.write(randomPerson1 + ' ' + randomPerson2 + ' ' + value + '\n')

print(people_totals)
