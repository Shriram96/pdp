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
    print("Dale")
    # exit()
    infile = sys.argv[1]
    # infile = "/user/shriramr/pdp/Project-1/A2/sample_input.txt"
    outdir = sys.argv[2]
    # outdir = "/user/shriramr/pdp/Project-1/A2/test-results/sample_output.txt"
    
    conf = SparkConf().setAppName("PointerJumper")
    sc = SparkContext(conf = conf)
    lines = sc.textFile(infile)
    edge_map = lines.flatMap(edge)
    edge_map.persist()
    datacollector = edge_map.collect()
    for row in datacollector:
        print("Edges Dale", row[0], ":", row[1])
    # edge_map.foreach(processRecord)
    # E = edge_map.reduceByKey(lambda a, b: a + b)
    # datacollector = E.collect()
    # for row in datacollector:
    #     print("Dale", row[0], ":", row[1])
    # E.foreach(processRecord)
    # E.saveAsTextFile(outdir)

    E1 = lines.flatMap(edge_reverse)
    # E1 = E.flatMap(sample)
    datacollector = E1.collect()
    for row in datacollector:
        print("Reverse Edges Dale", row[0], ":", row[1])

    E2 = edge_map.join(E1)
    datacollector = E2.collect()
    for row in datacollector:
        print("Join 1 Dale", row[0], ":", row[1])
    E2 = E2.map(joinmap)
    datacollector = E2.collect()
    for row in datacollector:
        print("Join 1 Dale", row[0], ":", row[1])

    E3 = edge_map.join(E2)
    datacollector = E3.collect()
    for row in datacollector:
        print("Join 2 Dale", row[0], ":", row[1])
    E3 = E3.map(joinmap)
    datacollector = E3.collect()
    for row in datacollector:
        print("Join 2 Dale", row[0], ":", row[1])

    E3 = edge_map.leftOuterJoin(E2)
    datacollector = E3.collect()
    for row in datacollector:
        print("Left Join Dale", row[0], ":", row[1])
    E3 = E3.map(joinmap)
    datacollector = E3.collect()
    for row in datacollector:
        print("Left Join Dale", row[0], ":", row[1])
    
    # E3 = E2.cartesian(E1).map(joinmap)
    # datacollector = E3.collect()
    # for row in datacollector:
    #     print("Cartesian Dale", row[0], ":", row[1])

    E3.saveAsTextFile(outdir)
    print("Dale", infile, outdir)
    sc.stop()