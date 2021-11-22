#!/usr/bin/python3
from pyspark import SparkConf, SparkContext
import sys
import time

def edge(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[1], e[0])]

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


if __name__ == "__main__":
    infile = sys.argv[1]
    outdir = sys.argv[2]
    
    start = time.time()
    conf = SparkConf().setAppName("PointerJumper")
    sc = SparkContext(conf = conf)

    lines = sc.textFile(infile)

    edge_map = lines.flatMap(edge)
    edge_map.persist()
    # datacollector = edge_map.collect()
    # for row in datacollector:
    #     print("Edges Dale", row[0], ":", row[1])

    count = edge_map.flatMap(edge_count).reduceByKey(lambda a, b: a + b).count()
    # print("Initial Count Dale: ", count)

    E1 = edge_map.map(reverser)
    E1.persist()
    # datacollector = E1.collect()
    # for row in datacollector:
    #     print("Reverse Edges Dale", row[0], ":", row[1])

    looper = 0
    while(True):
        looper += 1

        E1 = edge_map.join(E1).map(joinmap)
        E1.persist()
        edge_map = E1.map(reverser)
        edge_map.persist()
        # datacollector = E1.collect()
        # for row in datacollector:
        #     print("Join step Dale", row[0], ":", row[1])
        # datacollector = edge_map.collect()
        # for row in datacollector:
        #     print("Edge list step Dale", row[0], ":", row[1])
        # distinct_items = E1.countByValue().items()
        # print("Each Count Dale", distinct_items, " ", len(distinct_items))
        distinct_root = E1.flatMap(edge_count).reduceByKey(lambda a, b: a + b)
        # datacollector = distinct_root.collect()
        # for row in datacollector:
        #     print("Join 1 Dale", row[0], ":", row[1])
        distinct_root_count = distinct_root.count()
        # print("Each distinct Count Dale: ", distinct_root_count)
        
        if count == distinct_root_count:
            print("Dale Connected Components Count: ", distinct_root_count)
            print("Dale Looper total runs: ", looper)
            break
        else:
            count = distinct_root_count
        

    E1.saveAsTextFile(outdir)
    # print("Dale", infile, outdir)
    sc.stop()
    end = time.time()
    print("Dale", end - start)