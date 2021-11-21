#!/usr/bin/python3
from pyspark import SparkConf, SparkContext
import sys

def edge(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[1], e[0])]

def edge_reverse(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[0], e[1])]

def reverser(record):
    return record[1], record[0]

def joinmap(record):
    return record[1][0], record[1][1]

def sample(record):
    rand = []
    for i in record[1]:
        rand.append((i, record[0]))
    return rand

def processRecord(record):
    print("Dale", record)

if __name__ == "__main__":
    infile = sys.argv[1]
    outdir = sys.argv[2]
    
    conf = SparkConf().setAppName("PointerJumper")
    sc = SparkContext(conf = conf)

    lines = sc.textFile(infile)

    edge_map = lines.flatMap(edge)
    edge_map.persist()
    datacollector = edge_map.collect()
    for row in datacollector:
        print("Edges Dale", row[0], ":", row[1])

    count = edge_map.reduceByKey(lambda a, b: [a] + [b]).count()
    print("Initial Count Dale: ", count)

    E1 = lines.flatMap(edge_reverse)
    datacollector = E1.collect()
    for row in datacollector:
        print("Reverse Edges Dale", row[0], ":", row[1])

    looper = 5
    while(looper):
        E1 = edge_map.join(E1).map(joinmap)
        datacollector = E1.collect()
        for row in datacollector:
            print("Join 1 Dale", row[0], ":", row[1])
        distinct_items = E1.countByValue().items()
        print("Each Count Dale", distinct_items, " ", len(distinct_items))

        looper -= 1
        

    E1.saveAsTextFile(outdir)
    print("Dale", infile, outdir)
    sc.stop()