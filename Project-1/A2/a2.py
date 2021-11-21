#!/usr/bin/python3
from pyspark import SparkConf, SparkContext
import sys

def edge(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [(e[1], [e[0]])]

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
    datacollector = edge_map.collect()
    for row in datacollector:
        print("Dale", row[0], ":", row[1])
    edge_map.foreach(processRecord)
    E = edge_map.reduceByKey(lambda a, b: a + b)
    datacollector = E.collect()
    for row in datacollector:
        print("Dale", row[0], ":", row[1])
    E.foreach(processRecord)
    E.saveAsTextFile(outdir)

    E1 = E.flatMap(sample)
    datacollector = E1.collect()
    for row in datacollector:
        print("Dale", row[0], ":", row[1])
    print("Dale", infile, outdir)
    sc.stop()