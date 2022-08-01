import json

exported_data = open('./exported_data.txt', 'r')
exported_json = open('./exported_data.json', 'w')
data = exported_data.readlines()

people = {}
count = 0

text = {
    "nodes": [],
    "links": []
}

for line in data:
    line = json.loads(line)

    if line[0] not in people.keys():
        people[line[0]] = count
        count += 1
        text["nodes"].append({
            "name": line[0],
            "group": people[line[0]]
        })
    if line[1] not in people.keys():
        people[line[1]] = count
        count += 1
        text["nodes"].append({
            "name": line[1],
            "group": people[line[1]]
        })

    text["links"].append({
        "source": people[line[0]],
        "target": people[line[1]],
        "value": line[2]
    })

exported_data.close()
exported_json.write(json.dumps(text))
exported_json.close()
