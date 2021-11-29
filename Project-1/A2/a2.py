#!/usr/bin/python3
from pyspark import SparkConf, SparkContext
import sys
import time

def edge(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[1], e[0]), (e[0], str(e[1]))]

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
    M.persist()
    R = None

    count = 0
    looper = 0

    while(True):
        looper += 1
        R = M.groupByKey().mapValues(list).filter(lambda a: len(a[1]) > 1)
        step_count = R.count()
        if count == step_count:
            break
        else:
            count = step_count
        M = R.flatMap(unveil).filter(lambda a: a is not None)
        M.persist()
    print("Looper count: ", looper)

    R.flatMap(finalmap).filter(lambda a: a is not None).saveAsTextFile(outdir)
    sc.stop()
    end = time.time()
    print("Dale", end - start)