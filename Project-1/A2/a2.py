#!/usr/bin/python3
from pyspark import SparkConf, SparkContext
import sys

def edge(line):
    l = line.split(" ")
    e = [int(x) for x in l]
    return [e[0], e[1]]

if __name__ == "__main__":
    print("Dale")
    infile = sys.argv[1]
    # infile = "/user/shriramr/pdp/Project-1/A2/sample_input.txt"
    outdir = sys.argv[2]
    # outdir = "/user/shriramr/pdp/Project-1/A2/sample_output.txt"
    
    conf = SparkConf().setAppName("PointerJumper")
    sc = SparkContext(conf = conf)
    lines = sc.textFile(infile)
    edge_map = lines.flatMap(edge)
    E = edge_map.reduceByKey(lambda a, b: [a] + [b])
    E.saveAsTextFile(outdir)
    print(sys.argv[1], sys.argv[2])
    sc.stop()