import os
from datetime import datetime, timedelta
from time import sleep
import json

def sub_strings(path, path0):
    return path[len(path0):]


def is_first_time():
    isf = False
    try:
        open(data_path, "r").read()
    except:
        isf = True
    return isf


def counter(path0):
    total_sum = 0
    lines_sum = 0
    non_blank_lines_num = 0
    output = {}
    tree = os.walk(path_0)
    all_files = []
    for d, dirs, files in tree:
        for f in files:
            path = os.path.join(d,f)
            all_files.append(path)


    for file in all_files:
        good_file = False
        for extension in code_file_extensions:
            if file[-len(extension):] == extension:
                good_file = True
                break
        if not good_file:
            continue
        s = open(file, "r").read()
        spl = s.split("\n")
        print(sub_strings(file, path_0), ":", len(s), "symbols, ", len(spl), "lines")
        total_sum += len(s)
        lines_sum += len(spl)
        for l in spl:
            if l != "":
                non_blank_lines_num += 1

    print("*********************")
    print("Total number of symbols in project:")
    print(total_sum)
    print("Total number of lines in project:")
    print(lines_sum)
    print("Average line length:")
    print(round(10 * total_sum / lines_sum) / 10)
    print("Average non-blank line length:")
    print(round(10 * total_sum / non_blank_lines_num) / 10)
    print("Percent of blank lines:")
    print(round(1000 * (1 - (non_blank_lines_num / lines_sum))) / 10, "%")
    
    output["Total number of symbols in project"] = total_sum
    output["Total number of lines in project"] = lines_sum
    output["Average line length"] = round(10 * total_sum / lines_sum) / 10
    return output


def delete_last_one_line(datpath):
    with open(datpath, "r+", encoding = "utf-8") as file:
        file.seek(0, os.SEEK_END)
        pos = file.tell() - 1
        
        while pos > 0 and file.read(1) != "\n":
            pos -= 1
            file.seek(pos, os.SEEK_SET)

        if pos > 0:
            file.seek(pos, os.SEEK_SET)
            file.truncate()


def delete_last_some_lines(p, n):
    for _ in range(n):
        delete_last_one_line(p)


def store_data(data):
    global first_time, delay_time
    now = datetime.now()
    if first_time:
        first_time = False
        delta = now - beginning_of_times
        data["time"] = 0
        json.dump({"reference point":delta.total_seconds(), "data":[data]}, open(data_path, "w"), indent=4, sort_keys=True)
    else:
        reading = open(data_path, "r")
        prev_data = json.load(reading)
        ref_point = prev_data["reference point"]
        delta = (now - beginning_of_times).total_seconds() - ref_point
        data["time"] = delta
        if prev_data["data"][-1]["Total number of symbols in project"] == data["Total number of symbols in project"]:
            delay_time = offset_delay_time
        prev_data["data"].append(data)
        json.dump(prev_data, open(data_path, "w"), indent = 4, sort_keys=True)


#######     For user:   ##############################################################################
code_file_extensions = [".cpp", ".h", "hpp", ".c"]                                            #
path_0 = "D:\\Projects\\Literature_analyzer\\"                                                                            #
data_path = "D:\\Projects\\Literature_analyzer\\src\\Python_support\\project_stat.json"              #
renewing_time = 10  # Seconds (2 min default)                                                        #
offset_delay_time = 1200                                                                             #
######################################################################################################

total_sum = 0
lines_sum = 0
non_blank_lines_num = 0
delay_time = renewing_time
first_time = is_first_time()
beginning_of_times = datetime.min


while True:
    count_data = counter(data_path)
    store_data(count_data)
    sleep(delay_time)

