import subprocess as sp
import json
import matplotlib.pyplot as plt

sort_type = 1

arrSize = []
arrTime = []
iterator = 0
color = ["blue", "green", "yellow", "red"]
array_type_list = {1: "random", 2: "random on the right half", 3: "random on the left half", 4: "revers sorted array"}
sort_type_list = {1: "selection sort", 2: "bubble sort", 3: "insertion sort", 4: "merge sort", 5: "quick sort",
                  6: "standard sort"}

plt.title(sort_type_list[sort_type].upper())
plt.ylabel("time")
plt.xlabel("size")

for array_type in range(1, 5):

    for N in [5, 10, 25, 50, 75, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000, 100000]:
        generate_command = f"D:\\ProgProjects\\CPP\\DifferentSorted\\x64\\Debug\\DifferentSorted.exe --generate-array" + \
                           f" --generate-array-type {array_type} --generate-array-size {N}" + \
                           f" --sort-type {sort_type} --output file.json"
        proc = sp.call(["powershell.exe", generate_command])

        with open('file.json') as f:
            file_content = f.read()
            json_data = json.loads(file_content)
        arrSize.append(json_data["sort-size"])
        print(arrSize)
        arrTime.append(json_data["sort-time"])
        print(arrTime)
    plt.plot(arrSize, arrTime, color=color[iterator], linestyle='-', marker='', label=array_type_list[array_type])
    iterator = iterator+1
    arrTime = []
    arrSize = []
plt.legend()
plt.savefig(f"./{sort_type}.png")
plt.show()

