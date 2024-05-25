# By ralex2304 https://github.com/ralex2304

from sympy import false


file = open("README.md")

lines = file.readlines()

lines.pop(0) # pops the first line, which contains the main header

contents = "# Содержание\n\n"
counters = [0] * 4
level = 0

in_code_block = False; # "```" in markdown

for line in lines:
    if line.startswith("```"):
        in_code_block = not in_code_block
    
    if not line.startswith("#") or line == "# Содержание\n" or in_code_block:
        continue

    cur_level = 0
    while (cur_level + 1) < len(line) and line[cur_level + 1] == "#":
        cur_level += 1

    if cur_level >= len(counters):
        print("Error. More counters needed")

    if cur_level < level:
        for i in range(cur_level + 1, len(counters)):
            counters[i] = 0

    level = cur_level

    header = line[cur_level + 2:-1]

    link = "#" + header.lower().replace(" ", "-").replace("(", "").replace(")", "").replace(".", "").replace("`", "").replace(":","").replace("+", "")

    contents += "    " * cur_level + str(counters[cur_level] + 1) + ". [" + header + "](" + link + ")\n"
    counters[cur_level] += 1

print(contents)