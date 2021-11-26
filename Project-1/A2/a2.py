#!/usr/bin/python3
from pyspark import SparkConf, SparkContext
import sys
import time

def edge(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[1], e[0]), (e[0], str(e[1]))]

def edge_reverse(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[0], e[1])]

def edge_count(record):
    return [(record[1], 1)]

def reverser(record):
    return record[1], record[0]

def joinmap(record):
    return record[1][0], record[1][1]

def sample(record):
    rand = []
    for i in record[1]:
        rand.append((i, record[0]))
    return rand

def record_printer(map, info):
    datacollector = map.collect()
    print("##################################################")
    for row in datacollector:
        print(info, "Dale", row[0], ":", row[1])
    print("##################################################")

def rootnodes(record):
    if record[0] == record[1]:
        return record[0], record[1]

def unveil(record):
    answer = 0
    return_records = []
    for i in record[1]:
        if type(i) == str:
            answer = i
    for i in record[1]:
        if type(i) != str:
            return_records.append((i, answer))
            return_records.append((int(answer), i))
    return return_records

def finalmap(record):
    return_records = []
    for i in record[1]:
        if type(i) != str:
            return_records.append((i, record[0]))
    return return_records

if __name__ == "__main__":
    infile = sys.argv[1]
    outdir = sys.argv[2]
    
    start = time.time()
    conf = SparkConf().setAppName("PointerJumper")
    sc = SparkContext(conf = conf)
    # sc.setLogLevel("ERROR")

    lines = sc.textFile(infile)

    M = lines.flatMap(edge)
    R = None

    count = 0
    looper = 0

    while(True):
        looper += 1
        R = M.groupByKey().mapValues(list).filter(lambda a: len(a[1]) > 1)
        # record_printer(R, "Reduce"+str(looper))
        step_count = R.count()
        # print("Step: ", looper, "RDD count: ", step_count)
        if count == step_count:
            break
        else:
            count = step_count
        M = R.flatMap(unveil).filter(lambda a: a is not None)
        # record_printer(M2, "Map"+str(looper))
    # record_printer(R.flatMap(finalmap).filter(lambda a: a is not None), "Last Reduced")
    print("Looper count: ", looper)

    R.flatMap(finalmap).filter(lambda a: a is not None).saveAsTextFile(outdir)
    sc.stop()
    end = time.time()
    print("Dale", end - start)